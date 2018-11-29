/**
 * @file Test_Hermite5.cpp
 * @brief Hermite5 tests
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-11
 */
#include <eigen3/Eigen/Core>

#include "catch.h"
#include "math/Hermite5.h"

const Eigen::Vector2d p1(0, 0);
const Eigen::Vector2d p2(0, 1);
const Eigen::Vector2d v1(-1, 1);
const Eigen::Vector2d v2(1, 1);
const Eigen::Vector2d a1(-2, -2);
const Eigen::Vector2d a2(2, 2);

const Eigen::MatrixXd C = (Eigen::MatrixXd(6,6) <<
                             -6,  15,  -10,   0, 0, 1,
                             -3,   8,   -6,   0, 1, 0,
                           -0.5, 1.5, -1.5, 0.5, 0, 0,
                            0.5,  -1,  0.5,   0, 0, 0,
                             -3,   7,   -4,   0, 0, 0,
                              6, -15,   10,   0, 0, 0
                           ).finished();

TEST_CASE("quintic Hermite curves have an unique ID", "[Hermite5]") {

    Hermite5 h1(p1, v1, a1, p2, v2, a2);
    Hermite5 h2(p1, v1, a1, p2, v2, a2);
    Hermite5 h3(p1, v1, a1, p2, v2, a2);
    Hermite5 h4(p1, v1, a1, p2, v2, a2);

    REQUIRE(h1.getID() != h2.getID());
    REQUIRE(h1.getID() != h3.getID());
    REQUIRE(h1.getID() != h4.getID());
    REQUIRE(h2.getID() != h4.getID());
    REQUIRE(h3.getID() != h2.getID());
    REQUIRE(h3.getID() != h4.getID());
}

TEST_CASE("control points, velocity and acceleration vectors of quintic"
          " Hermite curves can be accessed", "[Hermite5]") {

    Hermite5 h1(p1, v1, a1, p2, v2, a2);

    REQUIRE(h1.getStartControlPoint() == p1);
    REQUIRE(h1.getStartVelocityVector() == v1);
    REQUIRE(h1.getStartAccelerationVector() == a1);
    REQUIRE(h1.getEndControlPoint() == p2);
    REQUIRE(h1.getEndVelocityVector() == v2);
    REQUIRE(h1.getEndAccelerationVector() == a2);

    Eigen::Matrix2Xd B = (Eigen::Matrix2Xd(2, 6) << p1, v1, a1, a2, v2, p2
                         ).finished()*C;

    REQUIRE(h1.getCurveMatrix() == B);
}

TEST_CASE("control points, velocity and acceleration vectors of quintic Hermite"
          " curves can be changed", "[Hermite5]") {

    Eigen::Vector2d p1p(1, 0);
    Eigen::Vector2d v1p(-2, 1);
    Eigen::Vector2d a1p(-3, 3);
    Eigen::Vector2d p2p(0, 2);
    Eigen::Vector2d v2p(1, 2);
    Eigen::Vector2d a2p(4, 6);

    Eigen::Matrix2Xd B = (Eigen::Matrix2Xd(2, 6) << p1, v1, a1, a2, v2, p2
                         ).finished()*C;
    Hermite5 h1(p1, v1, a1, p2, v2, a2);

    SECTION("changing the first control point changes the matrix") {
        h1.setStartControlPoint(p1p);
        REQUIRE(h1.getStartControlPoint() == p1p);

        B = (Eigen::Matrix2Xd(2, 6) << p1p, v1, a1, a2, v2, p2).finished()*C;
        REQUIRE(h1.getCurveMatrix() == B);
    }

    SECTION("changing the second control point changes the matrix") {
        h1.setEndControlPoint(p2p);
        REQUIRE(h1.getEndControlPoint() == p2p);

        B = (Eigen::Matrix2Xd(2, 6) << p1, v1, a1, a2, v2, p2p).finished()*C;
        REQUIRE(h1.getCurveMatrix() == B);
    }

    SECTION("changing the first velocity vector changes the matrix") {
        h1.setStartVelocityVector(v1p);
        REQUIRE(h1.getStartVelocityVector() == v1p);

        B = (Eigen::Matrix2Xd(2, 6) << p1, v1p, a1, a2, v2, p2).finished()*C;
        REQUIRE(h1.getCurveMatrix() == B);
    }

    SECTION("changing the second velocity vector changes the matrix") {
        h1.setEndVelocityVector(v2p);
        REQUIRE(h1.getEndVelocityVector() == v2p);

        B = (Eigen::Matrix2Xd(2, 6) << p1, v1, a1, a2, v2p, p2).finished()*C;
        REQUIRE(h1.getCurveMatrix() == B);
    }

    SECTION("changing the first acceleration vector changes the matrix") {
        h1.setStartAccelerationVector(a1p);
        REQUIRE(h1.getStartAccelerationVector() == a1p);

        B = (Eigen::Matrix2Xd(2, 6) << p1, v1, a1p, a2, v2, p2).finished()*C;
        REQUIRE(h1.getCurveMatrix() == B);
    }

    SECTION("changing the second acceleration vector changes the matrix") {
        h1.setEndAccelerationVector(a2p);
        REQUIRE(h1.getEndAccelerationVector() == a2p);

        B = (Eigen::Matrix2Xd(2, 6) << p1, v1, a1, a2p, v2, p2).finished()*C;
        REQUIRE(h1.getCurveMatrix() == B);
    }
}

TEST_CASE("Quintic Hermite curves can be evaluated", "[Hermite5]") {
    Hermite5 h1(p1, v1, a1, p2, v2, a2);

    REQUIRE(h1.evaluateAt(0.0) == p1);
    REQUIRE(h1.evaluateAt(-1.0) == p1);
    REQUIRE(h1.evaluateAt(1.0) == p2);
    REQUIRE(h1.evaluateAt(2.0) == p2);

    Eigen::Vector2d expected(-0.3125, 0.5);
    REQUIRE(h1.evaluateAt(0.5) == expected);
}
