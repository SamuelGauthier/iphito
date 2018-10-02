/**
 * @file Hermite5.cpp
 * @brief Implements the quitinc Hermite curve
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-02
 */
#include "Hermite5.h"

Hermite5::Hermite5(Eigen::Vector2d p1, Eigen::Vector2d t1, Eigen::Vector2d s1,
                   Eigen::Vector2d p2, Eigen::Vector2d t2, Eigen::Vector2d s2) :
    p1{p1}, t1{t1}, s1{s1}, p2{p2}, t2{t2}, s2{s2}, id{Curve::getNextID()} {}

Hermite5::~Hermite5() {}

unsigned long long Hermite5::getID() {
    return this->id;
}
