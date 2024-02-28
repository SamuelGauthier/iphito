/**
 * @file Axes2D.h
 * @brief Describes an 2D axes system
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2019-09-19
 */
#ifndef AXES2D_H
#define AXES2D_H

#include <Eigen/Core>
#include <memory>
#include "Arrow2D.h"

namespace iphito::renderer {

class Axes2D {

public:
    Axes2D() = delete;
    Axes2D(const Eigen::Vector2d& position, const Eigen::Vector2d& xDirection,
           const Eigen::Vector2d& yDirection, const Eigen::Vector3d& color,
           double axisLength, double axisWidth);
    ~Axes2D();
    
    void render();
    void updateModelMatrix(const Eigen::Matrix4d& model);
    void updateViewMatrix(const Eigen::Matrix4d& view);
    void updateProjectionMatrix(const Eigen::Matrix4d& projection);

private:
    Eigen::Vector2d position;
    Eigen::Vector2d xDirection;
    Eigen::Vector2d yDirection;
    Eigen::Vector3d color;
    double axisLength;
    double axisWidth;

    std::unique_ptr<Arrow2D> xAxis;
    std::unique_ptr<Arrow2D> yAxis;
};

} /* namespace iphito::renderer */

#endif /* ifndef AXES2D_H */
