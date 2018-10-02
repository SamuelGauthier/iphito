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
    Hermite5(Eigen::Vector2d p1, Eigen::Vector2d t1, Eigen::Vector2d s1,
             Eigen::Vector2d p2, Eigen::Vector2d t2, Eigen::Vector2d s2);
    ~Hermite5();

    void setControlPoint1(Eigen::Vector2d p);
    void setControlPoint2(Eigen::Vector2d p);
    void setControlPoints(Eigen::Vector2d p1, Eigen::Vector2d p2);
    void setTangentVector1(Eigen::Vector2d t);
    void setTangentVector2(Eigen::Vector2d t);
    void setTangentVectors(Eigen::Vector2d t1, Eigen::Vector2d t2);
    void setVelocityVector1(Eigen::Vector2d s);
    void setVelocityVector2(Eigen::Vector2d s);
    void setVelocityVectors(Eigen::Vector2d s1, Eigen::Vector2d s2);

    unsigned long long getID();

private:
    Eigen::Vector2d p1;
    Eigen::Vector2d p2;
    Eigen::Vector2d t1;
    Eigen::Vector2d t2;
    Eigen::Vector2d s1;
    Eigen::Vector2d s2;

    unsigned long long id;
};

#endif /* ifndef HERMITE5H */
