/**
 * @file Line2D.cpp
 * @brief Implements a 2d line
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2019-02-23
 */
#include "Line2D.h"

#include "utils/Utils.h"
#include "utils/Logger.h"

Line2D::Line2D(Eigen::Vector2d startPoint, Eigen::Vector2d endPoint, double width,
               Eigen::Vector3d color) :
    startPoint{startPoint}, endPoint{endPoint}, width{width}, color{color} {

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

    Eigen::Vector2d d = this->endPoint - this->startPoint;
    std::swap(d[0], d[1]);
    d[0] *= -1;
    d.normalize();

    Eigen::Vector2d v1 = this->startPoint + (this->width * d);
    Eigen::Vector2d v2 = this->startPoint - (this->width * d);
    Eigen::Vector2d v3 = this->endPoint + (this->width * d);
    Eigen::Vector2d v4 = this->endPoint - (this->width * d);

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

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(GLfloat),
                 &this->vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
                 &this->indices[0], GL_STATIC_DRAW);
}

void Line2D::render() {

    glUseProgram(this->shader->getProgramID());
    glBindVertexArray(this->vertexArrayObjectID);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, NULL);
}
