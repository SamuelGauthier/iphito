/**
 * @file Hermite.h
 * @brief Describes a cubic Hermite curve
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-01
 */
#ifndef HERMITE3H
#define HERMITE3H

#include <eigen3/Eigen/Core>

#include "Curve.h"

class Hermite3 : public Curve {

public:
    Hermite3(Eigen::Vector2d startPoint, Eigen::Vector2d startTangentVector,
             Eigen::Vector2d endPoint, Eigen::Vector2d endTangentVector);
    ~Hermite3();

    unsigned long long getID();
    Eigen::Vector2d evaluateAt(double t);
    void render();

    void setStartControlPoint(Eigen::Vector2d p);
    void setEndControlPoint(Eigen::Vector2d p);
    void setControlPoints(Eigen::Vector2d startPoint, Eigen::Vector2d endPoint);
    void setStartTangentVector(Eigen::Vector2d t);
    void setEndTangentVector(Eigen::Vector2d t);
    void setTangentVectors(Eigen::Vector2d startTangentVector,
                           Eigen::Vector2d endTangentVector);
    void setCurveDescription(Eigen::Vector2d startPoint,
                             Eigen::Vector2d startTangentVector,
                             Eigen::Vector2d endPoint,
                             Eigen::Vector2d endTangentVector);

    Eigen::Vector2d getStartControlPoint();
    Eigen::Vector2d getEndControlPoint();
    Eigen::Vector2d getStartTangentVector();
    Eigen::Vector2d getEndTangentVector();
    Eigen::Matrix2Xd getCurveMatrix();

private:
    Eigen::Vector2d startPoint;
    Eigen::Vector2d endPoint;
    Eigen::Vector2d startTangentVector;
    Eigen::Vector2d endTangentVector;

    unsigned long long id;
    Eigen::Matrix2Xd B;
    static const Eigen::Matrix4d C;

    void recomputeB();
};

#endif /* ifndef HERMITE3H */
