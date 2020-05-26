/**
 * @file Point2D.cpp
 * @brief Implements a 2D point
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2018-12-29
 */
#include "Point2D.h"

#include <iostream>

#include "utils/Utils.h"
#include "utils/Logger.h"

namespace iphito::renderer {

using namespace iphito::utils;

inline std::mt19937_64 Point2D::engine = std::mt19937_64();
inline std::uniform_real_distribution<double> Point2D::distribution(0.0, 1.0);

Point2D::Point2D(Eigen::Vector2d center, Eigen::Vector3d color, double radius,
                 double width) :
    center{(Eigen::Vector3d() << center, 1.0).finished()}, color{color},
    radius{radius}, width{width}, model{Eigen::Matrix4d::Identity()},
    view{Eigen::Matrix4d::Identity()}, projection{Eigen::Matrix4d::Identity()},
    isDirty{true} {

    if(!Utils::isGlfwInitialized())
        throw std::runtime_error("Please initialize GLFW.");

    if(!Utils::isGlewInitialized())
        throw std::runtime_error("Please initialize Glew.");

    this->shader.reset(new Shader("../src/shaders/basic.vert",
                                  "../src/shaders/basic.frag"));

    this->shader->useProgram();

    int colorLocation = glGetUniformLocation(this->shader->getProgramID(),
                                             "color");
    glUniform3f(colorLocation, this->color[0], this->color[1],
                this->color[2]);

    glGenVertexArrays(1, &this->vertexArrayObjectID);
    glBindVertexArray(this->vertexArrayObjectID);

    glGenBuffers(1, &this->vertexBufferID);
    glGenBuffers(1, &this->indexBufferID);

    recomputeVerticesAndIndices();
}

Point2D::~Point2D() {

    // TODO: Make proper destructor
}

void Point2D::recomputeVerticesAndIndices() {

    this->samplePoints = std::vector<Eigen::Vector2d>();
    sampleCurve(0.0, M_PI);

    Eigen::Vector2d center2D;
    center2D << this->center[0], this->center[1];

    for (int i = this->samplePoints.size() - 2; i > 0; i--) {
        
        Eigen::Vector2d p = this->samplePoints[i];
        p -= center2D;
        p[1] *= -1;
        p += center2D;
        this->samplePoints.push_back(p);
    }

    this->samplePoints.push_back((Eigen::Vector2d() << center2D[0],
                                  center2D[1]).finished());

    // reset vertices and indices
    this->vertices = std::vector<GLfloat>();
    this->indices = std::vector<GLuint>();

    if(this->width == 0.0) {
        // We don't need a special float comparison in this case, as 0.0 is the
        // default value.
        // Plain circle case.

        for (auto& i : this->samplePoints) {
            
            this->vertices.push_back(i[0]);
            this->vertices.push_back(i[1]);
        }

        for (int i = 0; i < this->samplePoints.size() - 2; i++) {
            
            this->indices.push_back(this->samplePoints.size() - 1);
            this->indices.push_back(i);
            this->indices.push_back(i + 1);
        }

        this->indices.push_back(this->samplePoints.size() - 1);
        this->indices.push_back(this->samplePoints.size() - 2);
        this->indices.push_back(0);
    }
    else {
        // TODO: Hollow circle case.
    }

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

bool Point2D::isFlat(Eigen::Vector2d a, Eigen::Vector2d b, Eigen::Vector2d m) {

    Eigen::Vector2d ma = a - m;
    Eigen::Vector2d mb = b - m;

    return std::abs(ma.dot(mb) / (ma.norm() * mb.norm())) > 0.99; // 0.999
}

void Point2D::sampleCurve(double a, double b) {

    double t = 0.45 + 0.1 * Point2D::distribution(Point2D::engine);
    /* double m = a + t * (b - a); */
    double m = a + 0.5 * (b - a);

    Eigen::Vector4d pa3D;
    Eigen::Vector4d pb3D;
    Eigen::Vector4d pm3D;
    pa3D << this->evaluateCircleAt(a), 1.0, 0.0;
    pb3D << this->evaluateCircleAt(b), 1.0, 0.0;
    pm3D << this->evaluateCircleAt(m), 1.0, 0.0;

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

Eigen::Vector2d Point2D::evaluateCircleAt(double t) {

    Eigen::Vector2d p(cos(t), sin(t));
    p *= this->radius;
    p += (Eigen::Vector2d() << this->center[0], this->center[1]).finished();

    return p;
}

void Point2D::render() {

    if (this->hasToBeRedrawn()) {
        this->recomputeVerticesAndIndices();
    }

    this->shader->useProgram();
    this->shader->setMatrix4("model", this->model);
    this->shader->setMatrix4("view", this->view);
    this->shader->setMatrix4("projection", this->projection);
        
    glBindVertexArray(this->vertexArrayObjectID);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}

bool Point2D::hasToBeRedrawn() { return this->isDirty; }

void Point2D::updateModelMatrix(Eigen::Matrix4d model) {
    
    this->model = model;
}

void Point2D::updateViewMatrix(Eigen::Matrix4d view) {
    
    this->view = view;
}

void Point2D::updateProjectionMatrix(Eigen::Matrix4d projection) {

    this->projection = projection;
    this->isDirty = true;
}

} /* namespace iphito::renderer */

