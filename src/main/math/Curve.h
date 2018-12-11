/**
 * @file Curve.h
 * @brief Describes a parametric curve
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-09-14
 */
#ifndef CURVE_H
#define CURVE_H

#include <atomic>
#include <eigen3/Eigen/Core>

class Curve {

public:
    virtual ~Curve() = 0;
    virtual Eigen::Vector2d evaluateAt(double t) = 0;
    virtual Eigen::Vector2d operator()(double t) { return this->evaluateAt(t); }
    
};

inline Curve::~Curve() {}

#endif /* ifndef CURVE_H */
