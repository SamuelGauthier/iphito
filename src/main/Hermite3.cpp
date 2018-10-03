/**
 * @file Hermite.cpp
 * @brief Implements the cubic Hermite curve
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-01
 */
#include <eigen3/Eigen/Core>
#include "Hermite3.h"

const Eigen::Matrix4d Hermite3::C = (Eigen::Matrix4d() << 
                                      2.0, -3.0,  0.0,  1.0,
                                      1.0, -2.0, -1.0,  0.0,
                                      1.0, -1.0,  1.0,  0.0,
                                     -2.0,  3.0,  0.0,  0.0).finished();

Hermite3::Hermite3(Eigen::Vector2d p1, Eigen::Vector2d t1,
                   Eigen::Vector2d p2, Eigen::Vector2d t2) :
    p1{p1}, t1{t1}, p2{p2}, t2{t2}, id{Curve::getNextID()},
    B{(Eigen::Matrix2Xd(2,4) << p1, t1, t2, p2).finished()} {}

Hermite3::~Hermite3() {}

unsigned long long Hermite3::getID() {

    return this->id;
}

void Hermite3::setControlPoint1(Eigen::Vector2d p) {

    this->p1 = p;
    this->B(0,0) = p(0);
    this->B(1,0) = p(1);
}

void Hermite3::setControlPoint2(Eigen::Vector2d p) {

    this->p2 = p;
    this->B(0,3) = p(0);
    this->B(1,3) = p(1);
}

void Hermite3::setControlPoints(Eigen::Vector2d p1, Eigen::Vector2d p2) {

    this->p1 = p1;
    this->p2 = p2;
    this->B(0,0) = p1(0);
    this->B(1,0) = p1(1);
    this->B(0,3) = p2(0);
    this->B(1,3) = p2(1);
}

void Hermite3::setTangentVector1(Eigen::Vector2d t) {

    this->t1 = t;
    this->B(0,1) = t(0);
    this->B(1,1) = t(1);
}

void Hermite3::setTangentVector2(Eigen::Vector2d t) {

    this->t2 = t;
    this->B(0,2) = t(0);
    this->B(1,2) = t(1);
}

void Hermite3::setTangentVectors(Eigen::Vector2d t1, Eigen::Vector2d t2) {

    this->t1 = t1;
    this->t2 = t2;
    this->B(0,1) = t1(0);
    this->B(1,1) = t1(1);
    this->B(0,2) = t2(0);
    this->B(1,2) = t2(1);
}

void Hermite3::setCurveDescription(Eigen::Vector2d p1, Eigen::Vector2d t1,
                                   Eigen::Vector2d p2, Eigen::Vector2d t2) {
    this->p1 = p1;
    this->p2 = p2;
    this->t1 = t1;
    this->t2 = t2;

    this->B << p1, t1, t2, p2;
}

Eigen::Vector2d Hermite3::getControlPoint1() {
    return this->p1;
}

Eigen::Vector2d Hermite3::getControlPoint2() {
    return this->p2;
}

Eigen::Vector2d Hermite3::getTangentVector1() {
    return this->t1;
}

Eigen::Vector2d Hermite3::getTangentVector2() {
    return this->t2;
}

Eigen::Matrix2Xd Hermite3::getCurveDescription() {
    return this->B;
}

Eigen::Vector2d Hermite3::evaluateAt(double t) {

    Eigen::Vector4d v(t*t*t, t*t, t, 1.0);

    return this->B*this->C*v;
}
