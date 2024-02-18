/**
 * @file Hermite5.cpp
 * @brief Implements the quitinc Hermite curve
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-02
 */
#include "Hermite5.h"

namespace iphito::math {

const Eigen::MatrixXd Hermite5::C = (Eigen::MatrixXd(6,6) <<
                                      -6,  15,  -10,   0, 0, 1,
                                      -3,   8,   -6,   0, 1, 0,
                                    -0.5, 1.5, -1.5, 0.5, 0, 0,
                                     0.5,  -1,  0.5,   0, 0, 0,
                                      -3,   7,   -4,   0, 0, 0,
                                       6, -15,   10,   0, 0, 0
                                    ).finished();

Hermite5::Hermite5(Eigen::Vector2d startControlPoint,
                   Eigen::Vector2d startVelocityVector,
                   Eigen::Vector2d startAccelerationVector,
                   Eigen::Vector2d endControlPoint,
                   Eigen::Vector2d endVelocityVector,
                   Eigen::Vector2d endAccelerationVector) :
    startControlPoint{startControlPoint},
    startVelocityVector{startVelocityVector},
    startAccelerationVector{startAccelerationVector},
    endControlPoint{endControlPoint},
    endVelocityVector{endVelocityVector},
    endAccelerationVector{endAccelerationVector},
    B{(Eigen::Matrix2Xd(2, 6) << startControlPoint, startVelocityVector,
            startAccelerationVector, endAccelerationVector, endVelocityVector,
            endControlPoint).finished() * this->C}
{}

Hermite5::~Hermite5() {}

Eigen::Vector2d Hermite5::evaluateAt(double t) {

    if(t < 0.0) t = 0.0;
    if(t > 1.0) t = 1.0;

    Eigen::VectorXd v(6);
    v << t*t*t*t*t, t*t*t*t, t*t*t, t*t, t, 1.0;

    return this->B*v;
}

std::unique_ptr<Curve> Hermite5::offsetBy(double amount) {

    Eigen::Vector2d offsetedStartControlPoint = this->startControlPoint;//+ direction;
    Eigen::Vector2d offsetedEndControlPoint = this->startControlPoint;//+ direction;

    return std::make_unique<Hermite5>(offsetedStartControlPoint,
                                      this->startVelocityVector,
                                      this->startAccelerationVector,
                                      offsetedEndControlPoint,
                                      this->endVelocityVector,
                                      this->endAccelerationVector);
}

void Hermite5::setStartControlPoint(Eigen::Vector2d p) {

    this->startControlPoint = p;
    this->B = (Eigen::Matrix2Xd(2, 6) << this->startControlPoint,
                                         this->startVelocityVector,
                                         this->startAccelerationVector,
                                         this->endAccelerationVector,
                                         this->endVelocityVector,
                                         this->endControlPoint
              ).finished() * this->C;

}

void Hermite5::setEndControlPoint(Eigen::Vector2d p) {

    this->endControlPoint = p;
    this->B = (Eigen::Matrix2Xd(2, 6) << this->startControlPoint,
                                         this->startVelocityVector,
                                         this->startAccelerationVector,
                                         this->endAccelerationVector,
                                         this->endVelocityVector,
                                         this->endControlPoint
              ).finished() * this->C;
}

void Hermite5::setControlControlPoints(Eigen::Vector2d startControlPoint,
                                Eigen::Vector2d endControlPoint) {

    this->startControlPoint = startControlPoint;
    this->endControlPoint = endControlPoint;
    this->B = (Eigen::Matrix2Xd(2, 6) << this->startControlPoint,
                                         this->startVelocityVector,
                                         this->startAccelerationVector,
                                         this->endAccelerationVector,
                                         this->endVelocityVector,
                                         this->endControlPoint
              ).finished() * this->C;

}

void Hermite5::setStartVelocityVector(Eigen::Vector2d v) {

    this->startVelocityVector = v;
    this->B = (Eigen::Matrix2Xd(2, 6) << this->startControlPoint,
                                         this->startVelocityVector,
                                         this->startAccelerationVector,
                                         this->endAccelerationVector,
                                         this->endVelocityVector,
                                         this->endControlPoint
              ).finished() * this->C;
}

void Hermite5::setEndVelocityVector(Eigen::Vector2d v) {

    this->endVelocityVector = v;
    this->B = (Eigen::Matrix2Xd(2, 6) << this->startControlPoint,
                                         this->startVelocityVector,
                                         this->startAccelerationVector,
                                         this->endAccelerationVector,
                                         this->endVelocityVector,
                                         this->endControlPoint
              ).finished() * this->C;
}

void Hermite5::setVelocityVectors(Eigen::Vector2d startVelocityVector,
                                  Eigen::Vector2d endVelocityVector) {

    this->startVelocityVector = startVelocityVector;
    this->endVelocityVector = endVelocityVector;
    this->B = (Eigen::Matrix2Xd(2, 6) << this->startControlPoint,
                                         this->startVelocityVector,
                                         this->startAccelerationVector,
                                         this->endAccelerationVector,
                                         this->endVelocityVector,
                                         this->endControlPoint
              ).finished() * this->C;
}

void Hermite5::setStartAccelerationVector(Eigen::Vector2d a) {

    this->startAccelerationVector = a;
    this->B = (Eigen::Matrix2Xd(2, 6) << this->startControlPoint,
                                         this->startVelocityVector,
                                         this->startAccelerationVector,
                                         this->endAccelerationVector,
                                         this->endVelocityVector,
                                         this->endControlPoint
              ).finished() * this->C;
}

void Hermite5::setEndAccelerationVector(Eigen::Vector2d a) {

    this->endAccelerationVector = a;
    this->B = (Eigen::Matrix2Xd(2, 6) << this->startControlPoint,
                                         this->startVelocityVector,
                                         this->startAccelerationVector,
                                         this->endAccelerationVector,
                                         this->endVelocityVector,
                                         this->endControlPoint
              ).finished() * this->C;
}

void Hermite5::setAccelerationVectors(Eigen::Vector2d startAccelerationVector,
                                      Eigen::Vector2d endAccelerationVector) {

    this->startAccelerationVector = startAccelerationVector;
    this->endAccelerationVector = endAccelerationVector;
    this->B = (Eigen::Matrix2Xd(2, 6) << this->startControlPoint,
                                         this->startVelocityVector,
                                         this->startAccelerationVector,
                                         this->endAccelerationVector,
                                         this->endVelocityVector,
                                         this->endControlPoint
              ).finished() * this->C;
}

void Hermite5::setCurveDescription(Eigen::Vector2d startControlPoint,
                                   Eigen::Vector2d startVelocityVector, 
                                   Eigen::Vector2d startAccelerationVector,
                                   Eigen::Vector2d endControlPoint,
                                   Eigen::Vector2d endVelocityVector,
                                   Eigen::Vector2d endAccelerationVector) {

    this->startControlPoint = startControlPoint;
    this->endControlPoint = endControlPoint;
    this->startVelocityVector = startVelocityVector;
    this->endVelocityVector = endVelocityVector;
    this->startAccelerationVector = startAccelerationVector;
    this->endAccelerationVector = endAccelerationVector;
    this->B = (Eigen::Matrix2Xd(2, 6) << this->startControlPoint,
                                         this->startVelocityVector,
                                         this->startAccelerationVector,
                                         this->endAccelerationVector,
                                         this->endVelocityVector,
                                         this->endControlPoint
              ).finished() * this->C;
}


Eigen::Vector2d Hermite5::getStartControlPoint() {

    return this->startControlPoint;
}

Eigen::Vector2d Hermite5::getEndControlPoint() {

    return this->endControlPoint;
}

Eigen::Vector2d Hermite5::getStartVelocityVector() {

    return this->startVelocityVector;
}

Eigen::Vector2d Hermite5::getEndVelocityVector() {

    return this->endVelocityVector;
}

Eigen::Vector2d Hermite5::getStartAccelerationVector() {

    return this->startAccelerationVector;
}

Eigen::Vector2d Hermite5::getEndAccelerationVector() {

    return this->endAccelerationVector;
}

Eigen::Matrix2Xd Hermite5::getCurveMatrix() {

    return this->B;
}

} /* namespace iphito::math */
