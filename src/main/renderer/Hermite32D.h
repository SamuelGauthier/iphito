/**
 * @file 2DHermite3.h
 * @brief Describes a 2D cubic Hermite curve to be rendered
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2018-12-01
 */
#ifndef HERMITE32D_H
#define HERMITE32D_H

#include <memory>
#include <eigen3/Eigen/Core>

#include "math/Hermite3.h"
#include "Curve2D.h"
#include "Arrow2D.h"
#include "Point2D.h"

class Hermite32D : public Curve2D {

public:
    Hermite32D() = delete;
    Hermite32D(std::shared_ptr<Hermite3> curve, Eigen::Vector3d curveColor,
               double curveWidth, Eigen::Vector3d tangentColor,
               Eigen::Vector3d controlPointsColor);
    ~Hermite32D();
    
    void render();
    bool hasToBeRedrawn();

private:
    std::shared_ptr<Hermite3> curve;
    Eigen::Vector3d tangentColor;
    Eigen::Vector3d controlPointsColor;
    std::unique_ptr<Arrow2D> startTangent;
    std::unique_ptr<Arrow2D> endTangent;
    std::unique_ptr<Point2D> startControlPoint;
    std::unique_ptr<Point2D> endControlPoint;
    
};

#endif /* ifndef HERMITE32D_H */
