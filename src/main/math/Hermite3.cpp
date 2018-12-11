/**
 * @file Hermite.cpp
 * @brief Implements the cubic Hermite curve
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-01
 */
#include <vector>
#include <sstream>
#include <eigen3/Eigen/Core>
#include <GL/glew.h>

#include "Hermite3.h"

#include "renderer/Shader.h"

const Eigen::Matrix4d Hermite3::C = (Eigen::Matrix4d() << 
                                      2.0, -3.0,  0.0,  1.0,
                                      1.0, -2.0,  1.0,  0.0,
                                      1.0, -1.0,  0.0,  0.0,
                                     -2.0,  3.0,  0.0,  0.0).finished();

Hermite3::Hermite3(Eigen::Vector2d startPoint,
                   Eigen::Vector2d startTangentVector,
                   Eigen::Vector2d endPoint,
                   Eigen::Vector2d endTangentVector) :
    startPoint{startPoint}, startTangentVector{startTangentVector},
    endPoint{endPoint}, endTangentVector{endTangentVector},
    B{(Eigen::Matrix2Xd(2, 4) << startPoint, startTangentVector,
                                 endTangentVector, endPoint
      ).finished() * this->C} {} 

Hermite3::~Hermite3() {}

Eigen::Vector2d Hermite3::evaluateAt(double t) {

    if(t < 0.0) t = 0.0;
    if(t > 1.0) t = 1.0;

    Eigen::Vector4d v(t*t*t, t*t, t, 1.0);

    return this->B*v;
}

void Hermite3::setStartControlPoint(Eigen::Vector2d p) {

    this->startPoint = p;
    this->B = (Eigen::Matrix2Xd(2, 4) << this->startPoint,
                                         this->startTangentVector,
                                         this->endTangentVector,
                                         this->endPoint).finished() * this->C;
}

void Hermite3::setEndControlPoint(Eigen::Vector2d p) {

    this->endPoint = p;
    this->B = (Eigen::Matrix2Xd(2, 4) << this->startPoint,
                                         this->startTangentVector,
                                         this->endTangentVector,
                                         this->endPoint).finished() * this->C;
}

void Hermite3::setControlPoints(Eigen::Vector2d startPoint,
                                Eigen::Vector2d endPoint) {

    this->startPoint = startPoint;
    this->endPoint = endPoint;
    this->B = (Eigen::Matrix2Xd(2, 4) << this->startPoint,
                                         this->startTangentVector,
                                         this->endTangentVector,
                                         this->endPoint).finished() * this->C;
}

void Hermite3::setStartTangentVector(Eigen::Vector2d t) {

    this->startTangentVector = t;
    this->B = (Eigen::Matrix2Xd(2, 4) << this->startPoint,
                                         this->startTangentVector,
                                         this->endTangentVector,
                                         this->endPoint).finished() * this->C;
}

void Hermite3::setEndTangentVector(Eigen::Vector2d t) {

    this->endTangentVector = t;
    this->B = (Eigen::Matrix2Xd(2, 4) << this->startPoint,
                                         this->startTangentVector,
                                         this->endTangentVector,
                                         this->endPoint).finished() * this->C;
}

void Hermite3::setTangentVectors(Eigen::Vector2d startTangentVector,
                                 Eigen::Vector2d endTangentVector) {

    this->startTangentVector = startTangentVector;
    this->endTangentVector = endTangentVector;
    this->B = (Eigen::Matrix2Xd(2, 4) << this->startPoint,
                                         this->startTangentVector,
                                         this->endTangentVector,
                                         this->endPoint).finished() * this->C;
}

void Hermite3::setCurveDescription(Eigen::Vector2d startPoint,
                                   Eigen::Vector2d startTangentVector,
                                   Eigen::Vector2d endPoint,
                                   Eigen::Vector2d endTangentVector) {
    this->startPoint = startPoint;
    this->endPoint = endPoint;
    this->startTangentVector = startTangentVector;
    this->endTangentVector = endTangentVector;

    this->B = (Eigen::Matrix2Xd(2, 4) << this->startPoint,
                                         this->startTangentVector,
                                         this->endTangentVector,
                                         this->endPoint).finished() * this->C;
}

Eigen::Vector2d Hermite3::getStartControlPoint() {
    return this->startPoint;
}

Eigen::Vector2d Hermite3::getEndControlPoint() {
    return this->endPoint;
}

Eigen::Vector2d Hermite3::getStartTangentVector() {
    return this->startTangentVector;
}

Eigen::Vector2d Hermite3::getEndTangentVector() {
    return this->endTangentVector;
}

Eigen::Matrix2Xd Hermite3::getCurveMatrix() {
    return this->B;
}
