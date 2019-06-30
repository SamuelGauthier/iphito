/**
 * @file Hermite52D.h
 * @brief Describes a 2D quintic Hermite curve to be rendered
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2019-03-16
 */
#ifndef HERMITE52D

#include <memory>
#include <eigen3/Eigen/Core>

#include "math/Hermite5.h"
#include "Curve2D.h"
#include "Arrow2D.h"
#include "Point2D.h"

class Hermite52D : public Curve2D {

public:
    Hermite52D() = delete;
    Hermite52D(std::shared_ptr<Hermite5> curve, double curveWidth,
               Eigen::Vector3d curveColor, Eigen::Vector3d tangentColor,
               Eigen::Vector3d secondDerivativeColor,
               Eigen::Vector3d controlPointsColor);
    ~Hermite52D();
    
    void render();
    bool hasToBeRedrawn();
    void updateTransform(Eigen::Matrix3d& transform);    

private:
    std::shared_ptr<Hermite5> curve;
    Eigen::Vector3d tangentColor;
    Eigen::Vector3d secondDerivativeColor;
    Eigen::Vector3d controlPointsColor;
    std::unique_ptr<Arrow2D> startTangent;
    std::unique_ptr<Arrow2D> endTangent;
    std::unique_ptr<Arrow2D> startSecondDerivative;
    std::unique_ptr<Arrow2D> endSecondDerivative;
    std::shared_ptr<Point2D> startControlPoint;
    std::shared_ptr<Point2D> endControlPoint;
};

#define HERMITE52D
#endif /* ifndef HERMITE52D */
