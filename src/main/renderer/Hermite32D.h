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

#include "Curve2D.h"
#include "math/Hermite3.h"

class Hermite32D : public Curve2D {

public:
    Hermite32D() = delete;
    Hermite32D(std::unique_ptr<Hermite3> curve, Eigen::Vector3d curveColor,
               double curveWidth, Eigen::Vector3d tangentColor,
               Eigen::Vector3d controlPointsColor);
    ~Hermite32D();
    
    void render();
    bool hasToBeRedrawn();

private:
    Eigen::Vector3d tangentColor;
    Eigen::Vector3d controlPointsColor;
};

#endif /* ifndef HERMITE32D_H */
