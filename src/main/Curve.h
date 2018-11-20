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
    virtual unsigned long long getID() = 0;
    virtual Eigen::Vector2d evaluateAt(double t) = 0;
    virtual Eigen::Vector2d operator()(double t) { return this->evaluateAt(t); }
    virtual void render() = 0;
    
    unsigned long long getNextID() { return this->nextID.fetch_add(1); }
    

private:
    static std::atomic<unsigned long long> nextID;
};

inline Curve::~Curve() {}

inline std::atomic<unsigned long long> Curve::nextID = 0;
#endif /* ifndef CURVE_H */
