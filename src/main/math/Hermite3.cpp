/**
 * @file Hermite.cpp
 * @brief Implements the cubic Hermite curve
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-01
 */
#include <vector>
#include <sstream>
#include <eigen3/Eigen/Core>
#include <GL/glew.h>

#include "Hermite3.h"

#include "renderer/Shader.h"
#include "utils/Logger.h"

const Eigen::Matrix4d Hermite3::C = (Eigen::Matrix4d() << 
                                      2.0, -3.0,  0.0,  1.0,
                                      1.0, -2.0,  1.0,  0.0,
                                      1.0, -1.0,  0.0,  0.0,
                                     -2.0,  3.0,  0.0,  0.0).finished();

Hermite3::Hermite3(Eigen::Vector2d startPoint,
                   Eigen::Vector2d startTangentVector,
                   Eigen::Vector2d endPoint,
                   Eigen::Vector2d endTangentVector) :
    startPoint{startPoint}, startTangentVector{startTangentVector},
    endPoint{endPoint}, endTangentVector{endTangentVector},
    id{Curve::getNextID()},
    B{(Eigen::Matrix2Xd(2, 4) << startPoint, startTangentVector,
                                 endTangentVector, endPoint
      ).finished() * this->C} {} //, logger{Logger::Instance()} {}

Hermite3::~Hermite3() {}

unsigned long long Hermite3::getID() {

    return this->id;
}

Eigen::Vector2d Hermite3::evaluateAt(double t) {

    if(t < 0.0) t = 0.0;
    if(t > 1.0) t = 1.0;

    Eigen::Vector4d v(t*t*t, t*t, t, 1.0);

    return this->B*v;
}

void Hermite3::render() {

    static std::vector<GLfloat> vertices = {0.0f, 0.0f, 0.0f, 1.0f,
                                            0.25f, 0.5, 0.0f, 1.0f,
                                            0.5f, 0.0f, 0.0f, 1.0f};
    static std::vector<GLuint> indices = {0, 1, 2};

    /* if(vertices.size() == 0) { */

    /*     vertices = {0.0f, 0.0f, 0.0f, 1.0f, */
    /*                 0.25f, 0.5, 0.0f, 1.0f, */
    /*                 0.5f, 0.0f, 0.0f, 1.0f}; */
    /* } */

    /* if(indices.size() == 0) { */

    /*     indices = {0, 1, 2}; */
    /* } */

    static Shader t = Shader("../src/shaders/basic.vert", "../src/shaders/basic.frag");
    glUseProgram(t.getProgramID());

    // Check if needed to recompute the vertices and indices
    /* CurveRenderer::sampleCurve(vertices, indices, this); */

    static GLuint vertexArrayObjectID = -1;
    static GLuint vertexBufferID = -1;
    static GLuint indexBufferID = -1;

    /* std::stringstream m; */
    /* m << "vertexArrayObjectID = " << vertexArrayObjectID; */
    /* this->logger->debug(m.str()); */

    if(vertexArrayObjectID == -1) {
        glGenVertexArrays(1, &vertexArrayObjectID);
        glBindVertexArray(vertexArrayObjectID);
    }

    if(vertexBufferID == -1) {
        glGenBuffers(1, &vertexBufferID);
        /* glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID); */
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat),
                &vertices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
        /* glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat), NULL); */
        glEnableVertexAttribArray(0);
    }

    //glBufferSubData updates a subset of a buffer object's data store
    /* static bool test = true; */

    /* if(test) { */
    /*     this->logger->debug(std::to_string(vertices.size() * sizeof(GLfloat))); */
    /*     this->logger->debug(std::to_string(sizeof(vertices))); */
    /*     test = false; */
    /* } */

    if(indexBufferID == -1) {
        glGenBuffers(1, &indexBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
                &indices[0], GL_STATIC_DRAW);
    }

    glBindVertexArray(vertexArrayObjectID);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);
}

void Hermite3::setStartControlPoint(Eigen::Vector2d p) {

    this->startPoint = p;
    this->B = (Eigen::Matrix2Xd(2, 4) << this->startPoint,
                                         this->startTangentVector,
                                         this->endTangentVector,
                                         this->endPoint).finished() * this->C;
}

void Hermite3::setEndControlPoint(Eigen::Vector2d p) {

    this->endPoint = p;
    this->B = (Eigen::Matrix2Xd(2, 4) << this->startPoint,
                                         this->startTangentVector,
                                         this->endTangentVector,
                                         this->endPoint).finished() * this->C;
}

void Hermite3::setControlPoints(Eigen::Vector2d startPoint,
                                Eigen::Vector2d endPoint) {

    this->startPoint = startPoint;
    this->endPoint = endPoint;
    this->B = (Eigen::Matrix2Xd(2, 4) << this->startPoint,
                                         this->startTangentVector,
                                         this->endTangentVector,
                                         this->endPoint).finished() * this->C;
}

void Hermite3::setStartTangentVector(Eigen::Vector2d t) {

    this->startTangentVector = t;
    this->B = (Eigen::Matrix2Xd(2, 4) << this->startPoint,
                                         this->startTangentVector,
                                         this->endTangentVector,
                                         this->endPoint).finished() * this->C;
}

void Hermite3::setEndTangentVector(Eigen::Vector2d t) {

    this->endTangentVector = t;
    this->B = (Eigen::Matrix2Xd(2, 4) << this->startPoint,
                                         this->startTangentVector,
                                         this->endTangentVector,
                                         this->endPoint).finished() * this->C;
}

void Hermite3::setTangentVectors(Eigen::Vector2d startTangentVector,
                                 Eigen::Vector2d endTangentVector) {

    this->startTangentVector = startTangentVector;
    this->endTangentVector = endTangentVector;
    this->B = (Eigen::Matrix2Xd(2, 4) << this->startPoint,
                                         this->startTangentVector,
                                         this->endTangentVector,
                                         this->endPoint).finished() * this->C;
}

void Hermite3::setCurveDescription(Eigen::Vector2d startPoint,
                                   Eigen::Vector2d startTangentVector,
                                   Eigen::Vector2d endPoint,
                                   Eigen::Vector2d endTangentVector) {
    this->startPoint = startPoint;
    this->endPoint = endPoint;
    this->startTangentVector = startTangentVector;
    this->endTangentVector = endTangentVector;

    this->B = (Eigen::Matrix2Xd(2, 4) << this->startPoint,
                                         this->startTangentVector,
                                         this->endTangentVector,
                                         this->endPoint).finished() * this->C;
}

Eigen::Vector2d Hermite3::getStartControlPoint() {
    return this->startPoint;
}

Eigen::Vector2d Hermite3::getEndControlPoint() {
    return this->endPoint;
}

Eigen::Vector2d Hermite3::getStartTangentVector() {
    return this->startTangentVector;
}

Eigen::Vector2d Hermite3::getEndTangentVector() {
    return this->endTangentVector;
}

Eigen::Matrix2Xd Hermite3::getCurveMatrix() {
    return this->B;
}
