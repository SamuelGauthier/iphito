#include <iostream>
#include "Grid.h"

#include "src/main/utils/Utils.h"
#include "src/main/utils/Logger.h"

namespace iphito::renderer {

using namespace iphito::utils;

Grid::Grid(const Eigen::Vector3d& color) : color{color},
    model{Eigen::Matrix4d::Identity()}, view{Eigen::Matrix4d::Identity()},
    projection{Eigen::Matrix4d::Identity()},
    viewAabb{AABB(Eigen::Vector2d(), Eigen::Vector2d())} {

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

    Eigen::Vector2d min = Eigen::Vector2d(-2, -2);
    Eigen::Vector2d max = Eigen::Vector2d(2, 2);
    this->viewAabb = AABB(min, max);

    recomputeGrid();
}
void Grid::render() {

    this->shader->useProgram();
    this->shader->setMatrix4("model", this->model);
    this->shader->setMatrix4("view", this->view);
    this->shader->setMatrix4("projection", this->projection);

    glBindVertexArray(this->vertexArrayObjectID);
    glDrawElements(GL_LINES, this->indices.size(), GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}

void Grid::updateModelMatrix(const Eigen::Matrix4d& model) {
    this->model = model;
}

void Grid::updateViewMatrix(const Eigen::Matrix4d& view) {
    this->view = view;
}

void Grid::updateProjectionMatrix(const Eigen::Matrix4d& projection) {
    this->projection = projection;
}

void Grid::setViewAABB(const AABB& aabb) {
    this->viewAabb = aabb;
    recomputeGrid();
}

void Grid::recomputeGrid() {
    this->vertices = std::vector<GLfloat>();
    this->indices = std::vector<GLuint>();

    Eigen::Vector2d min = this->viewAabb.getMin();
    Eigen::Vector2d max = this->viewAabb.getMax();

    double deltaX = log10(max[0] - min[0]);
    deltaX = floor(deltaX - 1);
    deltaX = pow(10, deltaX);

    double deltaY = log10(max[1] - min[1]);
    deltaY = floor(deltaY - 1);
    deltaY = pow(10, deltaY);

    double maxDelta = std::max(deltaX, deltaY);

    double startX = (floor(min[0] / maxDelta) - 1) * maxDelta;
    for (double i = startX; i <= max[0]; i += maxDelta) {
        this->vertices.push_back(i);
        this->vertices.push_back(max[1]);
        this->vertices.push_back(i);
        this->vertices.push_back(min[1]);
    }

    double startY = (floor(min[1] / maxDelta) - 1 ) * maxDelta;
    for (double i = startY; i <= max[1]; i += maxDelta) {
        this->vertices.push_back(min[0]);
        this->vertices.push_back(i);
        this->vertices.push_back(max[0]);
        this->vertices.push_back(i);
    }

    for (int i = 0; i < this->vertices.size()/2; i++) {
        this->indices.push_back(i);
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
}

} /* namespace iphito::renderer */
