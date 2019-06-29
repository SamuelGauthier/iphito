/**
 * @file Canvas.cpp
 * @brief Canvas implementation
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-09-14
 */

#include "Canvas.h"

#include "utils/Utils.h"

Canvas::Canvas(unsigned int width, unsigned int height) : width{width},
    height{height}, rootLayer{new Layer()},
    transform{Eigen::Matrix3d::Identity()} {
        
        if(!Utils::isGlfwInitialized())
            throw std::runtime_error("Please initialize GLFW."); 

        if(!Utils::isGlewInitialized())
            throw std::runtime_error("Please initialize Glew.");
        
        glGenVertexArrays(1, &this->vertexArrayObjectID);
}

Canvas::~Canvas() {}

unsigned int Canvas::getWidth() {
    return this->width;
}

unsigned int Canvas::getHeight() {
    return this->height;
}

void Canvas::setRootLayer(std::shared_ptr<Layer> rootLayer) {
    this->rootLayer = rootLayer;
}

void Canvas::render() {
    glBindVertexArray(this->vertexArrayObjectID);
    this->rootLayer->render();
}

void Canvas::updateTransform(Eigen::Matrix3d transform) {
    
    if (this->transform.isApprox(transform))
        return;

    this->rootLayer->updateCurveTransform(transform);
    this->transform = transform;
}
