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
#include <memory>
#include <eigen3/Eigen/Core>

namespace iphito::math {

class Curve {

public:
    virtual ~Curve() = 0;
    virtual Eigen::Vector2d evaluateAt(double t) = 0;
    virtual Eigen::Vector2d operator()(double t) { return this->evaluateAt(t); }
    virtual std::unique_ptr<Curve> offsetBy(double amount) = 0;
    
};

inline Curve::~Curve() {}

} /* namespace iphito::math */

#endif /* ifndef CURVE_H */
