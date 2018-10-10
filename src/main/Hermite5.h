/**
 * @file Hermite5.h
 * @brief Describes a quintic Hermite curve
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-02
 */
#ifndef HERMITE5H
#define HERMITE5H value

#include <eigen3/Eigen/Core>

#include "Curve.h"

class Hermite5 : public Curve {

public:
    Hermite5(Eigen::Vector2d p1, Eigen::Vector2d v1, Eigen::Vector2d a1,
             Eigen::Vector2d p2, Eigen::Vector2d v2, Eigen::Vector2d a2);
    ~Hermite5();

    unsigned long long getID();
    Eigen::Vector2d evaluateAt(double t);

    void setControlPoint1(Eigen::Vector2d p);
    void setControlPoint2(Eigen::Vector2d p);
    void setControlPoints(Eigen::Vector2d p1, Eigen::Vector2d p2);
    void setVelocityVector1(Eigen::Vector2d v);
    void setVelocityVector2(Eigen::Vector2d v);
    void setVelocityVectors(Eigen::Vector2d v1, Eigen::Vector2d v2);
    void setAccelerationVector1(Eigen::Vector2d a);
    void setAccelerationVector2(Eigen::Vector2d a);
    void setAccelerationVectors(Eigen::Vector2d a1, Eigen::Vector2d a2);
    void setCurveDescription(Eigen::Vector2d p1, Eigen::Vector2d v1, 
                             Eigen::Vector2d a1, Eigen::Vector2d p2,
                             Eigen::Vector2d v2, Eigen::Vector2d a2);

    Eigen::Vector2d getControlPoint1();
    Eigen::Vector2d getControlPoint2();
    Eigen::Vector2d getVelocityVector1();
    Eigen::Vector2d getVelocityVector2();
    Eigen::Vector2d getAccelerationVector1();
    Eigen::Vector2d getAccelerationVector2();
    Eigen::Matrix2Xd getCurveMatrix();

private:
    Eigen::Vector2d p1;
    Eigen::Vector2d p2;
    Eigen::Vector2d v1;
    Eigen::Vector2d v2;
    Eigen::Vector2d a1;
    Eigen::Vector2d a2;

    unsigned long long id;
    Eigen::Matrix2Xd B;
    static const Eigen::MatrixXd C;
};

#endif /* ifndef HERMITE5H */
