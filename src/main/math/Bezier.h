/**
 * @file Bezier.h
 * @brief Describes a Bézier curve
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-16
 */
#ifndef BEZIER_H
#define BEZIER_H

#include <vector>
#include <utility>
#include <map>
#include <memory>
#include <eigen3/Eigen/Core>

#include "Curve.h"

namespace iphito::math {

class Bezier : public Curve {

public:
    Bezier(std::vector<Eigen::Vector2d> points);
    ~Bezier();
    
    Eigen::Vector2d evaluateAt(double t) override;
    std::unique_ptr<Curve> offsetBy(double amount) override;

    void setPoints(std::vector<Eigen::Vector2d>& points);
    std::vector<Eigen::Vector2d> getPoints();
    std::map<int, std::pair<Eigen::Vector2d, double>> getPointsAndBernstein();

private:
    std::map<int, std::pair<Eigen::Vector2d, double>> pointsAndBernstein;
    int degree;
};

} /* namespace iphito::math */

#endif /* ifndef BEZIER_H */
