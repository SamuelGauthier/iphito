/**
 * @file Hermite.cpp
 * @brief Implements the cubic Hermite curve
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-01
 */
#include "Hermite3.h"

Hermite3::Hermite3(Eigen::Vector3d p1, Eigen::Vector3d t1,
                   Eigen::Vector3d p2, Eigen::Vector3d t2) : p1{p1}, t1{t1},
                                                             p2{p2}, t2{t2} {}
