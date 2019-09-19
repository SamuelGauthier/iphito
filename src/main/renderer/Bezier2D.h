/**
 * @file Bezier2D.h
 * @brief Describes a 2D Bezier curve to be rendered
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2019-02-23
 */
#ifndef BEZIER2D_H
#define BEZIER2D_H

#include <memory>
#include <eigen3/Eigen/Core>

#include "math/Bezier.h"
#include "Curve2D.h"
#include "Arrow2D.h"
#include "Point2D.h"
#include "Line2D.h"

class Bezier2D : public Curve2D {

public:
    Bezier2D() = delete;
    Bezier2D(std::shared_ptr<Bezier> curve, double curveWidth,
             Eigen::Vector3d curveColor, Eigen::Vector3d controlPointsColor,
             Eigen::Vector3d controlPolygonColor);
    ~Bezier2D();
    
    void render();
    bool hasToBeRedrawn();

private:
    std::shared_ptr<Bezier> curve;
    Eigen::Vector3d controlPointsColor;
    Eigen::Vector3d controlPolygonColor;
    std::vector<std::unique_ptr<Point2D>> controlPoints;
    std::vector<std::unique_ptr<Line2D>> controlPolygon;
};


#endif /* ifndef BEZIER2D_H */
