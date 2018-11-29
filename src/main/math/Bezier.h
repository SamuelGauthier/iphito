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
#include <eigen3/Eigen/Core>

#include "Curve.h"

class Bezier : public Curve {

public:
    Bezier(std::vector<Eigen::Vector2d> points);
    ~Bezier();
    
    unsigned long long getID();
    Eigen::Vector2d evaluateAt(double t);
    void render();

    void setPoints(std::vector<Eigen::Vector2d>& points);

private:
    unsigned long long id;
    std::map<int, std::pair<Eigen::Vector2d, double>> pointsAndBernstein;
    int degree;
};

#endif /* ifndef BEZIER_H */
