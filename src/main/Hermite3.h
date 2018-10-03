/**
 * @file Hermite.h
 * @brief Describes a cubic Hermite curve
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-01
 */
#ifndef HERMITE3H
#define HERMITE3H value

#include <eigen3/Eigen/Core>

#include "Curve.h"

class Hermite3 : public Curve {

public:
    Hermite3(Eigen::Vector2d p1, Eigen::Vector2d t1,
             Eigen::Vector2d p2, Eigen::Vector2d t2);
    ~Hermite3();

    void setControlPoint1(Eigen::Vector2d p);
    void setControlPoint2(Eigen::Vector2d p);
    void setControlPoints(Eigen::Vector2d p1, Eigen::Vector2d p2);
    void setTangentVector1(Eigen::Vector2d t);
    void setTangentVector2(Eigen::Vector2d t);
    void setTangentVectors(Eigen::Vector2d t1, Eigen::Vector2d t2);
    void setCurveDescription(Eigen::Vector2d p1, Eigen::Vector2d t1,
                             Eigen::Vector2d p2, Eigen::Vector2d t2);

    Eigen::Vector2d getControlPoint1();
    Eigen::Vector2d getControlPoint2();
    Eigen::Vector2d getTangentVector1();
    Eigen::Vector2d getTangentVector2();
    Eigen::Matrix2Xd getCurveDescription();

    unsigned long long getID();
    Eigen::Vector2d evaluateAt(double t);

private:
    Eigen::Vector2d p1;
    Eigen::Vector2d p2;
    Eigen::Vector2d t1;
    Eigen::Vector2d t2;

    unsigned long long id;
    Eigen::Matrix2Xd B;
    static const Eigen::Matrix4d C;

    void recomputeB();
};

#endif /* ifndef HERMITE3H */
