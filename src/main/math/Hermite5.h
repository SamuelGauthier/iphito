/**
 * @file Hermite5.h
 * @brief Describes a quintic Hermite curve
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-02
 */
#ifndef HERMITE5_H
#define HERMITE5_H

#include <Eigen/Core>

#include "Curve.h"

namespace iphito::math {

class Hermite5 : public Curve {

public:
    Hermite5(Eigen::Vector2d startControlPoint,
             Eigen::Vector2d startVelocityVector,
             Eigen::Vector2d startAccelerationVector,
             Eigen::Vector2d endControlPoint,
             Eigen::Vector2d endVelocityVector,
             Eigen::Vector2d endAccelerationVector);
    ~Hermite5();

    Eigen::Vector2d evaluateAt(double t) override;
    std::unique_ptr<Curve> offsetBy(double amount) override;

    void setStartControlPoint(Eigen::Vector2d p);
    void setEndControlPoint(Eigen::Vector2d p);
    void setControlControlPoints(Eigen::Vector2d startControlPoint, 
                                 Eigen::Vector2d endControlPoint);
    void setStartVelocityVector(Eigen::Vector2d v);
    void setEndVelocityVector(Eigen::Vector2d v);
    void setVelocityVectors(Eigen::Vector2d startVelocityVector,
                            Eigen::Vector2d endVelocityVector);
    void setStartAccelerationVector(Eigen::Vector2d a);
    void setEndAccelerationVector(Eigen::Vector2d a);
    void setAccelerationVectors(Eigen::Vector2d startAccelerationVector,
                                Eigen::Vector2d endAccelerationVector);
    void setCurveDescription(Eigen::Vector2d startControlPoint,
                             Eigen::Vector2d startVelocityVector, 
                             Eigen::Vector2d startAccelerationVector,
                             Eigen::Vector2d endControlPoint,
                             Eigen::Vector2d endVelocityVector,
                             Eigen::Vector2d endAccelerationVector);

    Eigen::Vector2d getStartControlPoint();
    Eigen::Vector2d getEndControlPoint();
    Eigen::Vector2d getStartVelocityVector();
    Eigen::Vector2d getEndVelocityVector();
    Eigen::Vector2d getStartAccelerationVector();
    Eigen::Vector2d getEndAccelerationVector();
    Eigen::Matrix2Xd getCurveMatrix();

private:
    Eigen::Vector2d startControlPoint;
    Eigen::Vector2d endControlPoint;
    Eigen::Vector2d startVelocityVector;
    Eigen::Vector2d endVelocityVector;
    Eigen::Vector2d startAccelerationVector;
    Eigen::Vector2d endAccelerationVector;

    Eigen::Matrix2Xd B;
    static const Eigen::MatrixXd C;
};

} /* namespace iphito::math */

#endif /* ifndef HERMITE5_H */
