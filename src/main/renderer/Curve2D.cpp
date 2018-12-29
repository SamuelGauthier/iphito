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

inline std::atomic<unsigned long long> Curve2D::nextID = 0;
inline std::mt19937_64 Curve2D::engine = std::mt19937_64();
inline std::uniform_real_distribution<double> Curve2D::distribution(0.0, 1.0);

Curve2D::Curve2D(std::unique_ptr<Curve> curve, Eigen::Vector3d curveColor,
                 double curveWidth) :
    curve{std::move(curve)}, curveColor{curveColor}, curveWidth{curveWidth},
    isDirty{false}, id{this->nextID.fetch_add(1)},
    samplePoints{std::vector<Eigen::Vector2d>()} {

    if(!Utils::isGlfwInitialized())
        throw std::runtime_error("Please initialize GLFW.");

    if(!Utils::isGlewInitialized())
        throw std::runtime_error("Please initialize Glew.");

    this->shader.reset(new Shader("../src/shaders/basic.vert",
                                  "../src/shaders/basic.frag"));
    glUseProgram(this->shader->getProgramID());

    int curveColorLocation = glGetUniformLocation(this->shader->getProgramID(),
            "curveColor");
    glUniform3f(curveColorLocation, this->curveColor[0], this->curveColor[1],
            this->curveColor[2]);

    glGenVertexArrays(1, &this->vertexArrayObjectID);
    glBindVertexArray(this->vertexArrayObjectID);

    glGenBuffers(1, &this->vertexBufferID);
    glGenBuffers(1, &this->indexBufferID);
}

void Curve2D::recomputeVerticesAndIndices() {

    sampleCurve(0.0, 1.0);
    verticesFromSamplePoints(this->samplePoints);
    indicesFromVertices();

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(GLfloat),
                 &this->vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
            &this->indices[0], GL_STATIC_DRAW);
}

unsigned long long Curve2D::getID() {
    
    return this->id;
}

void Curve2D::sampleCurve(double a, double b) {

    double t = 0.45 + 0.1 * Curve2D::distribution(Curve2D::engine);
    double m = a + t * (b - a);
    /* double m = a + 0.5 * (b - a); */

    Eigen::Vector2d pa = this->curve->evaluateAt(a);
    Eigen::Vector2d pb = this->curve->evaluateAt(b);
    Eigen::Vector2d pm = this->curve->evaluateAt(m);

    if(isFlat(pa, pb, pm)) {
        this->samplePoints.push_back(pa);
        this->samplePoints.push_back(pb);
    }
    else{
        sampleCurve(a, m);
        sampleCurve(m, b);
    }
}
bool Curve2D::isFlat(Eigen::Vector2d a, Eigen::Vector2d b, Eigen::Vector2d m) {

    Eigen::Vector2d ma = a - m;
    Eigen::Vector2d mb = b - m;

    return std::abs(ma.dot(mb) / (ma.norm() * mb.norm())) > 0.999;
}

void Curve2D::verticesFromSamplePoints(std::vector<Eigen::Vector2d>&
        samplePoints) {

    Logger::Instance()->debug("Sample size = " +
                              std::to_string(samplePoints.size()));
    if(samplePoints.size() == 0 ) return;
    for (int i = 0; i < samplePoints.size() - 1; i++) {
        Eigen::Vector2d a = samplePoints[i];
        Eigen::Vector2d b = samplePoints[i+1];

        Eigen::Vector2d d = (b-a);
        std::swap(d[0], d[1]);
        d[0] = -d[0];
        d.normalize();

        Eigen::Vector2d a1 = a + (this->curveWidth * d);
        Eigen::Vector2d a2 = a - (this->curveWidth * d);
        Eigen::Vector2d b1 = b + (this->curveWidth * d);
        Eigen::Vector2d b2 = b - (this->curveWidth * d);

        this->vertices.push_back(a1[0]);
        this->vertices.push_back(a1[1]);
        this->vertices.push_back(a2[0]);
        this->vertices.push_back(a2[1]);
        this->vertices.push_back(b1[0]);
        this->vertices.push_back(b1[1]);
        this->vertices.push_back(b2[0]);
        this->vertices.push_back(b2[1]);

    }
}

void Curve2D::indicesFromVertices() {

    int size = this->vertices.size()/2;

    for (int i = 0; i < size; i += 4) {
        this->indices.push_back(i+1);
        this->indices.push_back(i+2);
        this->indices.push_back(i);

        this->indices.push_back(i+1);
        this->indices.push_back(i+3);
        this->indices.push_back(i+2);
    }
}

