/**
 * @file Line.cpp
 * @brief Implements a Line
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2020-12-13
 */
#include "Line.h"
#include "utils/Utils.h"

#include <eigen3/Eigen/Dense>

namespace iphito::math {

using namespace iphito::utils;

Line::Line(Eigen::Vector2d a, Eigen::Vector2d b) : a{a}, b{b} { }

bool Line::intersect(const Line& other, Eigen::Vector2d& intersection) {

    Eigen::Vector2d otherA = other.getA();
    Eigen::Vector2d otherB = other.getB();

    Eigen::Matrix2d denominator;
    denominator << this->a[0] - this->b[0], this->a[1] - this->b[1],
                   otherA[0] - otherB[0], otherA[1] - otherB[1];
    double denominatorDet = denominator.determinant();

    if (Utils::nearlyEqual(denominatorDet, 0.0)) {
        
        intersection[0] = 0.0;
        intersection[1] = 0.0;
        return false;
    }

    Eigen::Matrix2d currentLine;
    currentLine << this->a[0], this->a[1],
                   this->b[0], this->b[1];
    double currentDet = currentLine.determinant();

    Eigen::Matrix2d otherLine;
    otherLine << otherA[0], otherA[1],
                 otherB[0], otherB[1];
    double otherDet = otherLine.determinant();

    Eigen::Matrix2d xNumerator;
    xNumerator << currentDet, this->a[0] - this->b[0],
                    otherDet, otherA[0] - otherB[0];
    double xNumeratorDet = xNumerator.determinant();

    Eigen::Matrix2d yNumerator;
    yNumerator << currentDet, this->a[0] - this->b[0],
                    otherDet, otherA[0] - otherB[0];
    double yNumeratorDet = yNumerator.determinant();

    intersection[0] = xNumeratorDet / denominatorDet;
    intersection[1] = yNumeratorDet / denominatorDet;

    return true;
}

Eigen::Vector2d Line::getA() const {
    return this->a;
}

Eigen::Vector2d Line::getB() const {
    return this->b;
}

} /* namespace iphito::math */
