/**
 * @file Arrow2D.cpp
 * @brief Implements a 2d arrow
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2018-12-26
 */
#include "Arrow2D.h"

#include "src/main/utils/Utils.h"
#include "src/main/utils/Logger.h"

namespace iphito::renderer {

using namespace iphito::utils;

Arrow2D::Arrow2D(const Eigen::Vector2d& position,
                 const Eigen::Vector2d& direction, double length, double width,
                 const Eigen::Vector3d& color) :
    position{position}, direction{direction}, length{length}, width{width/2.0},
    color{color}, model{Eigen::Matrix4d::Identity()},
    view{Eigen::Matrix4d::Identity()}, projection{Eigen::Matrix4d::Identity()} {
    
    this->direction.normalize();
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

Arrow2D::~Arrow2D() {

    // TODO: Correctly destroy buffers
}

void Arrow2D::recomputeVerticesAndIndices() {

    // reset vertices and indices
    this->vertices = std::vector<GLfloat>();
    this->indices = std::vector<GLuint>();

    Eigen::Vector2d position = this->position;

    Eigen::Vector2d d = this->direction;
    std::swap(d[0], d[1]);
    d[0] *= -1;
    d.normalize();

    Eigen::Vector2d v1 = position + (this->width * d);
    Eigen::Vector2d v2 = position - (this->width * d);

    Eigen::Vector2d frontAnchor = position + (this->direction * this->length);

    Eigen::Vector2d v3 = frontAnchor + (this->width * d);
    Eigen::Vector2d v4 = frontAnchor - (this->width * d);

    Eigen::Vector2d v5 = v3 + (this->width * 2 * d);
    Eigen::Vector2d v6 = v4 - (this->width * 2 * d);

    double l = std::sqrt(3.0) * this->width * 4;
    Eigen::Vector2d v7 = frontAnchor + (l * this->direction);

    this->vertices.push_back(v1[0]);
    this->vertices.push_back(v1[1]);
    this->vertices.push_back(v2[0]);
    this->vertices.push_back(v2[1]);
    this->vertices.push_back(v3[0]);
    this->vertices.push_back(v3[1]);
    this->vertices.push_back(v4[0]);
    this->vertices.push_back(v4[1]);
    this->vertices.push_back(v5[0]);
    this->vertices.push_back(v5[1]);
    this->vertices.push_back(v6[0]);
    this->vertices.push_back(v6[1]);
    this->vertices.push_back(v7[0]);
    this->vertices.push_back(v7[1]);

    this->indices.push_back(0);
    this->indices.push_back(1);
    this->indices.push_back(3);

    this->indices.push_back(0);
    this->indices.push_back(3);
    this->indices.push_back(2);

    this->indices.push_back(4);
    this->indices.push_back(2);
    this->indices.push_back(6);

    this->indices.push_back(2);
    this->indices.push_back(3);
    this->indices.push_back(6);

    this->indices.push_back(3);
    this->indices.push_back(5);
    this->indices.push_back(6);

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

void Arrow2D::render() {

    this->shader->useProgram();
    this->shader->setMatrix4("model", this->model);
    this->shader->setMatrix4("view", this->view);
    this->shader->setMatrix4("projection", this->projection);

    glBindVertexArray(this->vertexArrayObjectID);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}

void Arrow2D::updateModelMatrix(const Eigen::Matrix4d& model) {
    
    this->model = model;
}

void Arrow2D::updateViewMatrix(const Eigen::Matrix4d& view) {
    
    this->view = view;
}

void Arrow2D::updateProjectionMatrix(const Eigen::Matrix4d& projection) {

    this->projection = projection;
}

} /* namespace iphito::renderer */
