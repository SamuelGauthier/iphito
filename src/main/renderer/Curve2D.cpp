/**
 * @file Curve2D.cpp
 * @brief Implements a 2D parametric curve
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2018-12-10
 */

#include "Curve2D.h"

#include "utils/Utils.h"

inline std::atomic<unsigned long long> Curve2D::nextID = 0;

Curve2D::Curve2D(std::unique_ptr<Curve> curve, Eigen::Vector3d curveColor,
                 double curveWidth) :
    curve{std::move(curve)}, curveColor{curveColor}, curveWidth{curveWidth},
    isDirty{false}, id{this->nextID.fetch_add(1)} {

    if(!Utils::isGlfwInitialized())
        throw std::runtime_error("Please initialize GLFW.");

    if(!Utils::isGlewInitialized())
        throw std::runtime_error("Please initialize Glew.");

    this->shader.reset(new Shader("../src/shaders/basic.vert",
                                  "../src/shaders/basic.frag"));
    glUseProgram(this->shader->getProgramID());

    glGenVertexArrays(1, &this->vertexArrayObjectID);
    glBindVertexArray(this->vertexArrayObjectID);

    glGenBuffers(1, &this->vertexBufferID);
    glGenBuffers(1, &this->indexBufferID);
}

void Curve2D::recomputeVerticesAndIndices() {

    std::vector<Eigen::Vector3d> samplePoints;

    this->vertices = {0.0f, 0.0f, 0.0f, 1.0f,
                      0.25f, 0.5, 0.0f, 1.0f,
                      0.5f, 0.0f, 0.0f, 1.0f};
    this->indices = {0, 1, 2};

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(GLfloat),
                 &this->vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
            &this->indices[0], GL_STATIC_DRAW);
}

unsigned long long Curve2D::getID() {
    
    return this->id;
}

void sampleCurve(std::vector<Eigen::Vector3d> samplePoints) {

}
