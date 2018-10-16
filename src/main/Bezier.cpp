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

    if(points.size() != 0) {
        this->degree = points.size();

        for (int i = 0; i < points.size(); i++) {
            double bernsteinCoefficient = Utils::factorial(this->degree) /
                                          (Utils::factorial(i) *
                                           Utils::factorial(this->degree - i));

            this->pointsAndBernstein[i] = {points[i], bernsteinCoefficient};
        }
    }
}

Bezier::~Bezier() {}

unsigned long long Bezier::getID() { return this->id; }

Eigen::Vector2d Bezier::evaluateAt(double t) {

    return Eigen::Vector2d();
}
