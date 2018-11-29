/**
 * @file Test_Curve.cpp
 * @brief Curve tests
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-02
 */
#include <eigen3/Eigen/Core>

#include "catch.h"
#include "math/Hermite3.h"
#include "math/Hermite5.h"

TEST_CASE("curves have an unique ID", "[Curve]") {

    Eigen::Vector2d p1(0, 0);
    Eigen::Vector2d p2(0, 1);
    Eigen::Vector2d t1(-1, 1);
    Eigen::Vector2d t2(1, 1);
    Eigen::Vector2d s1(1, 0);
    Eigen::Vector2d s2(-1, 0);

    Hermite3 h1(p1, t1, p2, t2);
    Hermite3 h2(p1, t1, p2, t2);

    Hermite5 h3(p1, t1, s1, p2, t2, s2);
    Hermite5 h4(p1, t1, s1, p2, t2, s2);

    REQUIRE(h1.getID() != h3.getID());
    REQUIRE(h2.getID() != h4.getID());
}
