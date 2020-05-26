/**
 * @file Axes2D.cpp
 * @brief Implements the 2D axis system
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2019-09-19
 */
#include "Axes2D.h"

namespace iphito::renderer {

Axes2D::Axes2D(Eigen::Vector2d position, Eigen::Vector2d xDirection,
               Eigen::Vector2d yDirection, Eigen::Vector3d color,
               double axisLength, double axisWidth) :
    xDirection{xDirection}, yDirection{yDirection}, color{color},
    axisLength{axisLength}, axisWidth{axisWidth} {

    this->xAxis.reset(new Arrow2D(position, xDirection, axisLength, axisWidth,
                                  color));
    this->yAxis.reset(new Arrow2D(position, yDirection, axisLength, axisWidth,
                                  color));
}

Axes2D::~Axes2D() {
    // TODO: properly destroy buffers
}

void Axes2D::render() {

    this->xAxis->render();
    this->yAxis->render();
}

void Axes2D::updateModelMatrix(Eigen::Matrix4d model) {

    this->xAxis->updateModelMatrix(model);
    this->yAxis->updateModelMatrix(model);
}

void Axes2D::updateViewMatrix(Eigen::Matrix4d view) {

    this->xAxis->updateViewMatrix(view);
    this->yAxis->updateViewMatrix(view);
}

void Axes2D::updateProjectionMatrix(Eigen::Matrix4d projection) {

    this->xAxis->updateProjectionMatrix(projection);
    this->yAxis->updateProjectionMatrix(projection);
}

} /* namespace iphito::renderer */
