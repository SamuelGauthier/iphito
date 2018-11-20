/**
 * @file Canvas.cpp
 * @brief Canvas implementation
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-09-14
 */

#include "Canvas.h"

Canvas::Canvas(unsigned int width, unsigned int height) : width{width},
    height{height}, rootLayer{new Layer()} {
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
    this->rootLayer->render();
}
