/**
 * @file Line.cpp
 * @brief Describes a 2d line based on two points
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2020-12-13
 */
#ifndef LINE_H
#define LINE_H

#include <Eigen/Core>

namespace iphito::math {

class Line {

public:
    Line(Eigen::Vector2d a, Eigen::Vector2d b);

    bool intersect(const Line& other, Eigen::Vector2d& intersection);
    Eigen::Vector2d getA() const;
    Eigen::Vector2d getB() const;

private:
    Eigen::Vector2d a;
    Eigen::Vector2d b;
};
} /* namespace iphito::math */

#endif /* ifndef LINE_H */
