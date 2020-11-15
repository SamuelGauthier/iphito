#include <algorithm>

#include "AABB.h"

namespace iphito::renderer {

AABB::AABB(Eigen::Vector2d min, Eigen::Vector2d max) : min{min}, max{max} {}

const Eigen::Vector2d AABB::getMin() {
    return this->min;
}

const Eigen::Vector2d AABB::getMax() {
    return this->max;
}

const AABB AABB::operator+(const AABB& b) const {
    Eigen::Vector2d min;
    Eigen::Vector2d max;

    min[0] = std::min(this->min[0], b.min[0]);
    min[1] = std::min(this->min[1], b.min[1]);

    max[0] = std::max(this->max[0], b.max[0]);
    max[1] = std::max(this->max[1], b.max[1]);

    return AABB(min, max);
}

const AABB AABB::operator+=(const AABB& b) const {
    return *this + b;
}

const AABB AABB::operator-(const AABB& b) const {
    if (this->max[0] >= b.min[0] && this->max[1] >= b.min[1] &&
        this->min[0] <= b.max[0] && this->min[1] <= b.max[1]) {
        return AABB(b.min, this->max);
    }

    return AABB();
}

const AABB AABB::operator-=(const AABB& b) const {
    return *this - b;
}

} /* namespace iphito::renderer */
