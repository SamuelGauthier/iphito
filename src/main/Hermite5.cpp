/**
 * @file Hermite5.cpp
 * @brief Implements the quitinc Hermite curve
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-02
 */
#include "Hermite5.h"

const Eigen::MatrixXd Hermite5::C = (Eigen::MatrixXd(6,6) <<
                                      -6,  15,  -10,   0, 0, 1,
                                      -3,   8,   -6,   0, 1, 0,
                                    -0.5, 1.5, -1.5, 0.5, 0, 0,
                                     0.5,  -1,  0.5,   0, 0, 0,
                                      -3,   7,   -4,   0, 0, 0,
                                       6, -15,   10,   0, 0, 0
                                    ).finished();

Hermite5::Hermite5(Eigen::Vector2d p1, Eigen::Vector2d v1, Eigen::Vector2d a1,
                   Eigen::Vector2d p2, Eigen::Vector2d v2, Eigen::Vector2d a2) :
    p1{p1}, v1{v1}, a1{a1}, p2{p2}, v2{v2}, a2{a2}, id{Curve::getNextID()},
    B{(Eigen::Matrix2Xd(2, 6) << p1, v1, a1, a2, v2, p2).finished() * this->C}
{}

Hermite5::~Hermite5() {}

unsigned long long Hermite5::getID() {
    return this->id;
}

Eigen::Vector2d Hermite5::evaluateAt(double t) {

    if(t < 0.0) t = 0.0;
    if(t > 1.0) t = 1.0;

    Eigen::VectorXd v(6);
    v << t*t*t*t*t, t*t*t*t, t*t*t, t*t, t, 1.0;

    return this->B*v;
}

void Hermite5::setControlPoint1(Eigen::Vector2d p) {

    this->p1 = p;
    this->B = (Eigen::Matrix2Xd(2, 6) << this->p1, this->v1, this->a1,
                                         this->a2, this->v2, this->p2
              ).finished() * this->C;

}

void Hermite5::setControlPoint2(Eigen::Vector2d p) {

    this->p2 = p;
    this->B = (Eigen::Matrix2Xd(2, 6) << this->p1, this->v1, this->a1,
                                         this->a2, this->v2, this->p2
              ).finished() * this->C;
}

void Hermite5::setControlPoints(Eigen::Vector2d p1, Eigen::Vector2d p2) {

    this->p1 = p1;
    this->p2 = p2;
    this->B = (Eigen::Matrix2Xd(2, 6) << this->p1, this->v1, this->a1,
                                         this->a2, this->v2, this->p2
              ).finished() * this->C;

}

void Hermite5::setVelocityVector1(Eigen::Vector2d v) {

    this->v1 = v;
    this->B = (Eigen::Matrix2Xd(2, 6) << this->p1, this->v1, this->a1,
                                         this->a2, this->v2, this->p2
              ).finished() * this->C;
}

void Hermite5::setVelocityVector2(Eigen::Vector2d v) {

    this->v2 = v;
    this->B = (Eigen::Matrix2Xd(2, 6) << this->p1, this->v1, this->a1,
                                         this->a2, this->v2, this->p2
              ).finished() * this->C;
}

void Hermite5::setVelocityVectors(Eigen::Vector2d v1, Eigen::Vector2d v2) {

    this->v1 = v1;
    this->v2 = v2;
    this->B = (Eigen::Matrix2Xd(2, 6) << this->p1, this->v1, this->a1,
                                         this->a2, this->v2, this->p2
              ).finished() * this->C;
}

void Hermite5::setAccelerationVector1(Eigen::Vector2d a) {

    this->a1 = a;
    this->B = (Eigen::Matrix2Xd(2, 6) << this->p1, this->v1, this->a1,
                                         this->a2, this->v2, this->p2
              ).finished() * this->C;
}

void Hermite5::setAccelerationVector2(Eigen::Vector2d a) {

    this->a2 = a;
    this->B = (Eigen::Matrix2Xd(2, 6) << this->p1, this->v1, this->a1,
                                         this->a2, this->v2, this->p2
              ).finished() * this->C;
}

void Hermite5::setAccelerationVectors(Eigen::Vector2d a1, Eigen::Vector2d a2) {

    this->a1 = a1;
    this->a2 = a2;
    this->B = (Eigen::Matrix2Xd(2, 6) << this->p1, this->v1, this->a1,
                                        this->a2, this->v2, this->p2
              ).finished() * this->C;
}

void Hermite5::setCurveDescription(Eigen::Vector2d p1, Eigen::Vector2d v1, 
                                   Eigen::Vector2d a1, Eigen::Vector2d p2,
                                   Eigen::Vector2d v2, Eigen::Vector2d a2) {

}


Eigen::Vector2d Hermite5::getControlPoint1() {

    return this->p1;
}

Eigen::Vector2d Hermite5::getControlPoint2() {

    return this->p2;
}

Eigen::Vector2d Hermite5::getVelocityVector1() {

    return this->v1;
}

Eigen::Vector2d Hermite5::getVelocityVector2() {

    return this->v2;
}

Eigen::Vector2d Hermite5::getAccelerationVector1() {

    return this->a1;
}

Eigen::Vector2d Hermite5::getAccelerationVector2() {

    return this->a2;
}

Eigen::Matrix2Xd Hermite5::getCurveMatrix() {

    return this->B;
}

