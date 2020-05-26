/**
 * @file Bezier.cpp
 * @brief Implements a Bézier curve
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-16
 */
#include <stdexcept>

#include "Bezier.h"
#include "utils/Utils.h"

namespace iphito::math {

using namespace iphito::utils;

Bezier::Bezier(std::vector<Eigen::Vector2d> points) : degree{0} {

    if(points.size() <= 1) {
        throw std::length_error("A Bézier curve has to have at least two"
                                "points.");
    }

    this->degree = points.size() - 1;

    for (int i = 0; i < points.size(); i++) {
        double bernsteinCoefficient = Utils::factorial(this->degree) /
                                      (Utils::factorial(i) *
                                       Utils::factorial(this->degree - i));

        this->pointsAndBernstein[i] = {points[i], bernsteinCoefficient};
    }
}

Bezier::~Bezier() {}


Eigen::Vector2d Bezier::evaluateAt(double t) {

    Eigen::Vector2d sum(0.0, 0.0);

    for (auto& i : this->pointsAndBernstein) {
        int power = i.first;
        double bernstein = i.second.second;
        Eigen::Vector2d point = i.second.first;

        sum += bernstein * pow(t, power) * pow(1-t, this->degree - power) *
               point;
    }

    return sum;
}

void Bezier::setPoints(std::vector<Eigen::Vector2d>& points) {

    if(points.size() != this->degree + 1) {
        throw std::length_error("The points count has to be the same as the"
                                "current count of the curve.");
    }
    
    for (int i = 0; i < points.size(); i++)
        this->pointsAndBernstein[i].first = points[i];

}

std::vector<Eigen::Vector2d> Bezier::getPoints() {

    std::vector<Eigen::Vector2d> controlPoints;
    
    for (auto& i : this->pointsAndBernstein)
        controlPoints.push_back(i.second.first);

    return controlPoints;
}

std::map<int, std::pair<Eigen::Vector2d, double>>
Bezier::getPointsAndBernstein() {

    return this->pointsAndBernstein;
}

} /* namespace iphito::math */
