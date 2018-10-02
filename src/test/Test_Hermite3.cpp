/**
 * @file Test_Hermite3.cpp
 * @brief Hermite3 tests
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-02
 */
#include <eigen3/Eigen/Core>

#include "catch.h"
#include "Hermite3.h"

TEST_CASE("cubic Hermite curves have an unique ID", "[Hermite3]") {

    Eigen::Vector2d p1(0, 0);
    Eigen::Vector2d p2(0, 1);
    Eigen::Vector2d t1(-1, 1);
    Eigen::Vector2d t2(1, 1);

    Hermite3 h1(p1, t1, p2, t2);
    Hermite3 h2(p1, t1, p2, t2);
    Hermite3 h3(p1, t1, p2, t2);
    Hermite3 h4(p1, t1, p2, t2);

    REQUIRE(h1.getID() != h2.getID());
    REQUIRE(h3.getID() != h4.getID());
}
