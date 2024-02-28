/**
 * @file Bezier.cpp
 * @brief Implements a Bézier curve
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-16
 */
#include <stdexcept>

#include "Bezier.h"
#include "Line.h"
#include "src/main/utils/Utils.h"

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

std::unique_ptr<Curve> Bezier::offsetBy(double amount) {

    std::vector<Eigen::Vector2d> controlPoints = this->getPoints();
    auto controlPointsSize = controlPoints.size();

    std::vector<Eigen::Vector2d> newControlPoints;

    for (int i = 0; i < controlPointsSize-1; i++) {
        Eigen::Vector2d line = controlPoints[i] - controlPoints[i+1];

        double x = line[0];
        double y = line[1];
        line[0] = -y;
        line[1] = x;

        line.normalize();

        newControlPoints.push_back(controlPoints[i] + amount * line);
        newControlPoints.push_back(controlPoints[i+1] + amount * line);
    }

    std::vector<Eigen::Vector2d> prunedNewControlPoints;

    for (int i = 0; i < newControlPoints.size(); i += 4) {

        if (i == 0) {
            prunedNewControlPoints.push_back(newControlPoints[i]);
        }

        if (i+2 >= newControlPoints.size()) {
            prunedNewControlPoints.push_back(newControlPoints[i+1]);
            continue;
        }

        Line a(newControlPoints[i], newControlPoints[i+1]);
        Line b(newControlPoints[i+2], newControlPoints[i+3]);
        
        Eigen::Vector2d intersection;
        if (a.intersect(b, intersection)) {
            prunedNewControlPoints.push_back(intersection);
        }

        if (i + 3 == newControlPoints.size() - 1) {
            prunedNewControlPoints.push_back(newControlPoints[i+3]);
        }
    }

    return std::make_unique<Bezier>(prunedNewControlPoints);
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
