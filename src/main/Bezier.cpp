/**
 * @file Bezier.cpp
 * @brief Implements a Bézier curve
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-16
 */
#include <stdexcept>

#include "Bezier.h"
#include "Utils.h"

Bezier::Bezier(std::vector<Eigen::Vector2d> points) : id{Curve::getNextID()},
                                                      degree{0} {

    if(points.size() <= 1) {
        throw std::length_error("A Bézier curve has to have at least two"
                                "points.");
    }

    this->degree = points.size();

    for (int i = 0; i < points.size(); i++) {
        double bernsteinCoefficient = Utils::factorial(this->degree) /
                                      (Utils::factorial(i) *
                                       Utils::factorial(this->degree - i));

        this->pointsAndBernstein[i] = {points[i], bernsteinCoefficient};
    }
}

Bezier::~Bezier() {}

unsigned long long Bezier::getID() { return this->id; }

Eigen::Vector2d Bezier::evaluateAt(double t) {

    Eigen::Vector2d sum;

    for (auto& i : this->pointsAndBernstein) {
        int power = i.first;
        double bernstein = i.second.second;
        Eigen::Vector2d point = i.second.first;

        sum += bernstein * pow(t, power) * pow(1-t, this->degree - power) *
               point;
    }

    return sum;
}

void Bezier::render() {

}

void Bezier::setPoints(std::vector<Eigen::Vector2d>& points) {

    if(points.size() != this->degree) {
        throw std::length_error("The points count has to be the same as the"
                                "current count of the curve.");
    }
    
    for (int i = 0; i < points.size(); i++)
        this->pointsAndBernstein[i].first = points[i];

}
