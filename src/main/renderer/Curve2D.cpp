/**
 * @file Curve2D.cpp
 * @brief Implements a 2D parametric curve
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2018-12-10
 */
#include <iostream>
#include <sstream>
#include "Curve2D.h"

#include "utils/Logger.h"
#include "utils/Utils.h"

namespace iphito::renderer {

using namespace iphito::math;
using namespace iphito::utils;

inline std::atomic<unsigned long long> Curve2D::nextID = 0;
inline std::mt19937_64 Curve2D::engine = std::mt19937_64();
inline std::uniform_real_distribution<double> Curve2D::distribution(0.0, 1.0);

Curve2D::Curve2D(std::shared_ptr<Curve> curve, double curveWidth,
                 Eigen::Vector3d curveColor, Eigen::Matrix3d transform) :
    curve{curve}, curveWidth{curveWidth/2.0}, curveColor{curveColor}, 
    isDirty{true}, viewMatrixUpdate{true}, projectionMatrixUpdate{true}, 
    id{this->nextID.fetch_add(1)}, samplePoints{std::vector<Eigen::Vector2d>()},
    model{Eigen::Matrix4d::Identity()}, view{Eigen::Matrix4d::Identity()},
    projection{Eigen::Matrix4d::Identity()} {

    if(!Utils::isGlfwInitialized())
        throw std::runtime_error("Please initialize GLFW.");

    if(!Utils::isGlewInitialized())
        throw std::runtime_error("Please initialize Glew.");

    this->shader.reset(new Shader("../src/shaders/basic.vert",
                                  "../src/shaders/basic.frag"));
    this->shader->useProgram();

    int curveColorLocation = glGetUniformLocation(this->shader->getProgramID(),
            "color");
    glUniform3f(curveColorLocation, this->curveColor[0], this->curveColor[1],
            this->curveColor[2]);

    glGenVertexArrays(1, &this->vertexArrayObjectID);
    glBindVertexArray(this->vertexArrayObjectID);

    glGenBuffers(1, &this->vertexBufferID);
    glGenBuffers(1, &this->indexBufferID);
}

void Curve2D::recomputeVerticesAndIndices() {

    this->vertices = std::vector<GLfloat>();
    this->indices = std::vector<GLuint>();
    this->samplePoints = std::vector<Eigen::Vector2d>();
    sampleCurve(0.0, 1.0);

    verticesFromSamplePoints(this->samplePoints);
    indicesFromVertices();

    glBindVertexArray(this->vertexArrayObjectID);

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(GLfloat),
                 &this->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
                 &this->indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    this->isDirty = false;
}

unsigned long long Curve2D::getID() {
    
    return this->id;
}

void Curve2D::sampleCurve(double a, double b) {

    double t = 0.45 + 0.1 * Curve2D::distribution(Curve2D::engine);
    double m = a + t * (b - a);

    Eigen::Vector4d pa3D;
    Eigen::Vector4d pb3D;
    Eigen::Vector4d pm3D;
    pa3D << this->curve->evaluateAt(a), 1.0, 0.0;
    pb3D << this->curve->evaluateAt(b), 1.0, 0.0;
    pm3D << this->curve->evaluateAt(m), 1.0, 0.0;

    Eigen::Vector2d pa;
    Eigen::Vector2d pb;
    Eigen::Vector2d pm;
    pa << pa3D[0], pa3D[1];
    pb << pb3D[0], pb3D[1];
    pm << pm3D[0], pm3D[1];

    pa3D = this->projection * this->view * this->model * pa3D;
    pb3D = this->projection * this->view * this->model * pb3D;
    pm3D = this->projection * this->view * this->model * pm3D;
    Eigen::Vector2d paScreen;
    Eigen::Vector2d pbScreen;
    Eigen::Vector2d pmScreen;
    paScreen << pa3D[0], pa3D[1];
    pbScreen << pb3D[0], pb3D[1];
    pmScreen << pm3D[0], pm3D[1];


    if(isFlat(paScreen, pbScreen, pmScreen)) {
        if(!samplePoints.empty()) {
            Eigen::Vector2d back = this->samplePoints.back();
            if(!(Utils::nearlyEqual(back[0], pa[0]) && 
                 Utils::nearlyEqual(back[1], pa[1]))) {

                this->samplePoints.push_back(pa);
                this->samplePoints.push_back(pb);
            }
            else {
                this->samplePoints.push_back(pb);
            }
        }
        else {
            this->samplePoints.push_back(pa);
            this->samplePoints.push_back(pb);
        }
    }
    else{
        sampleCurve(a, m);
        sampleCurve(m, b);
    }
}

bool Curve2D::isFlat(Eigen::Vector2d a, Eigen::Vector2d b, Eigen::Vector2d m) {

    Eigen::Vector2d ma = a - m;
    Eigen::Vector2d mb = b - m;

    if (ma.isApprox(Eigen::Vector2d::Zero()) ||
        mb.isApprox(Eigen::Vector2d::Zero())) {
        return true;
    }

    return std::abs(ma.dot(mb) / (ma.norm() * mb.norm())) > 0.999;
}

void Curve2D::verticesFromSamplePoints(std::vector<Eigen::Vector2d>&
        samplePoints) {

    if(samplePoints.size() == 0 ) return;

    Eigen::Vector2d a = samplePoints[0];
    Eigen::Vector2d b = samplePoints[1];

    Eigen::Vector2d d = b-a;
    std::swap(d[0], d[1]);
    d[0] *= -1;
    d.normalize();
    Eigen::Vector2d a1 = a + (this->curveWidth * d);
    Eigen::Vector2d a2 = a - (this->curveWidth * d);
    this->vertices.push_back(a1[0]);
    this->vertices.push_back(a1[1]);
    this->vertices.push_back(a2[0]);
    this->vertices.push_back(a2[1]);

    for (int i = 0; i < samplePoints.size() - 2; i++) {
        Eigen::Vector2d a = samplePoints[i];
        Eigen::Vector2d b = samplePoints[i+1];
        Eigen::Vector2d c = samplePoints[i+2];

        Eigen::Vector2d v1 = (b-a);
        Eigen::Vector2d v2 = (c-b);
        v1.normalize();
        v2.normalize();

        Eigen::Vector2d d1 = v1;
        std::swap(d1[0], d1[1]);
        d1[0] *= -1;
        d1.normalize();

        Eigen::Vector2d d2 = v2;
        std::swap(d2[0], d2[1]);
        d2[0] *= -1;
        d2.normalize();

        Eigen::Vector2d b1 = b + (this->curveWidth * d1);
        Eigen::Vector2d b2 = b - (this->curveWidth * d1);
        Eigen::Vector2d c1 = b + (this->curveWidth * d2);
        Eigen::Vector2d c2 = b - (this->curveWidth * d2);

        double det1 = v1[0]*v2[1] - v1[1]*v2[0];
        double det2 = v1[0]*b1[1] - v1[1]*b1[0];
        double det3 = c1[0]*v1[1] - c1[1]*v1[0];

        Eigen::Vector2d i1;
        if(det1 > 0.00001 || det1 < -0.00001)
            i1 = c1 + (det2 + det3) / det1 * v1;
        else i1 = b1;

        det1 = v1[0]*v2[1] - v1[1]*v2[0];
        det2 = v1[0]*b2[1] - v1[1]*b2[0];
        det3 = c2[0]*v1[1] - c2[1]*v1[0];

        Eigen::Vector2d i2;
        if(det1 > 0.00001 || det1 < -0.00001)
            i2 = c2 + (det2 + det3) / det1 * v1;
        else i2 = b2;

        this->vertices.push_back(i1[0]);
        this->vertices.push_back(i1[1]);
        this->vertices.push_back(i2[0]);
        this->vertices.push_back(i2[1]);
    }

    a = samplePoints[samplePoints.size() - 2];
    b = samplePoints[samplePoints.size() - 1];

    d = b-a;
    std::swap(d[0], d[1]);
    d[0] *= -1;
    d.normalize();
    Eigen::Vector2d b1 = b + (this->curveWidth * d);
    Eigen::Vector2d b2 = b - (this->curveWidth * d);
    this->vertices.push_back(b1[0]);
    this->vertices.push_back(b1[1]);
    this->vertices.push_back(b2[0]);
    this->vertices.push_back(b2[1]);
}

void Curve2D::indicesFromVertices() {

    int size = this->vertices.size()/4;

    for (int i = 0, j = 0; j < size - 1; i += 2, j++) {
        this->indices.push_back(i);
        this->indices.push_back(i+1);
        this->indices.push_back(i+2);

        this->indices.push_back(i+1);
        this->indices.push_back(i+3);
        this->indices.push_back(i+2);
    }
}


void Curve2D::updateSamplePoints(Eigen::Matrix3d& transform) {

    for (int i = 0; i < this->samplePoints.size(); i++) {
        Eigen::Vector2d originalPoint = this->samplePoints[i];
    }
}

void Curve2D::updateModelMatrix(Eigen::Matrix4d model) {
    
    this->model = model;
}

void Curve2D::updateViewMatrix(Eigen::Matrix4d view) {
    
    this->view = view;
    this->viewMatrixUpdate = true;
}

void Curve2D::updateProjectionMatrix(Eigen::Matrix4d projection) {

    this->projection = projection;
    this->projectionMatrixUpdate = true;
    this->isDirty = true;
}

} /* namespace iphito::renderer */
