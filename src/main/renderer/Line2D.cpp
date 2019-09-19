/**
 * @file Line2D.cpp
 * @brief Implements a 2d line
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2019-02-23
 */
#include <iostream>

#include "Line2D.h"

#include "utils/Utils.h"
#include "utils/Logger.h"

Line2D::Line2D(Eigen::Vector2d startPoint, Eigen::Vector2d endPoint, double width,
               Eigen::Vector3d color) :
    startPoint{startPoint}, endPoint{endPoint}, width{width}, color{color},
    transform{Eigen::Matrix3d::Identity()},
    model{Eigen::Matrix4d::Identity()}, view{Eigen::Matrix4d::Identity()},
    projection{Eigen::Matrix4d::Identity()} {

    if(!Utils::isGlfwInitialized())
        throw std::runtime_error("Please initialize GLFW.");

    if(!Utils::isGlewInitialized())
        throw std::runtime_error("Please initialize Glew.");

    this->shader.reset(new Shader("../src/shaders/basic.vert",
                                  "../src/shaders/basic.frag"));

    glUseProgram(this->shader->getProgramID());

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

Line2D::~Line2D() {

    // TODO: Correctly destroy all the stuff
}

void Line2D::recomputeVerticesAndIndices() {

    this->vertices = std::vector<GLfloat>();
    this->indices = std::vector<GLuint>();

    Eigen::Vector2d d = this->endPoint - this->startPoint;
    std::swap(d[0], d[1]);
    d[0] *= -1;
    d.normalize();

    Eigen::Vector3d v13D;
    Eigen::Vector3d v23D;
    Eigen::Vector3d v33D;
    Eigen::Vector3d v43D;

    v13D << this->startPoint + (this->width * d), 1.0;
    v23D << this->startPoint - (this->width * d), 1.0;
    v33D << this->endPoint + (this->width * d), 1.0;
    v43D << this->endPoint - (this->width * d), 1.0;

    v13D = this->transform * v13D;
    v23D = this->transform * v23D;
    v33D = this->transform * v33D;
    v43D = this->transform * v43D;

    Eigen::Vector2d v1;
    Eigen::Vector2d v2;
    Eigen::Vector2d v3;
    Eigen::Vector2d v4;

    v1 << v13D[0], v13D[1];
    v2 << v23D[0], v23D[1];
    v3 << v33D[0], v33D[1];
    v4 << v43D[0], v43D[1];

    this->vertices.push_back(v1[0]);
    this->vertices.push_back(v1[1]);
    this->vertices.push_back(v2[0]);
    this->vertices.push_back(v2[1]);
    this->vertices.push_back(v3[0]);
    this->vertices.push_back(v3[1]);
    this->vertices.push_back(v4[0]);
    this->vertices.push_back(v4[1]);

    this->indices.push_back(0);
    this->indices.push_back(1);
    this->indices.push_back(3);

    this->indices.push_back(0);
    this->indices.push_back(3);
    this->indices.push_back(2);

    glBindVertexArray(this->vertexArrayObjectID);

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(GLfloat),
                 &this->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
                 &this->indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

}

void Line2D::render() {

    this->shader->useProgram();
    this->shader->setMatrix4("model", this->model);
    this->shader->setMatrix4("view", this->view);
    this->shader->setMatrix4("projection", this->projection);

    glBindVertexArray(this->vertexArrayObjectID);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}

void Line2D::updateModelMatrix(Eigen::Matrix4d model) {

    this->model = model;
}

void Line2D::updateViewMatrix(Eigen::Matrix4d view) {

    this->view = view;
}

void Line2D::updateProjectionMatrix(Eigen::Matrix4d projection) {

    this->projection = projection;
}
