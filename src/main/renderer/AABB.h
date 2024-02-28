#ifndef AABB_H
#define AABB_H

#include <Eigen/Core>

namespace iphito::renderer {

class AABB {

public:
    AABB(Eigen::Vector2d min = Eigen::Vector2d(),
         Eigen::Vector2d max = Eigen::Vector2d());

    const Eigen::Vector2d getMin();
    const Eigen::Vector2d getMax();

    const AABB operator+(const AABB& b) const;
    const AABB operator+=(const AABB& b) const;
    const AABB operator-(const AABB& b) const;
    const AABB operator-=(const AABB& b) const;

private:
    Eigen::Vector2d min;
    Eigen::Vector2d max;
};
} /* namespace iphito::renderer */

#endif /* ifndef AABB_H */
