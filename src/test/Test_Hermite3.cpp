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

const Eigen::Vector2d p1(0, 0);
const Eigen::Vector2d p2(0, 1);
const Eigen::Vector2d t1(-1, 1);
const Eigen::Vector2d t2(1, 1);

const Eigen::Matrix4d C = (Eigen::Matrix4d() << 
                            2.0, -3.0,  0.0,  1.0,
                            1.0, -2.0,  1.0,  0.0,
                            1.0, -1.0,  0.0,  0.0,
                           -2.0,  3.0,  0.0,  0.0).finished();


TEST_CASE("cubic Hermite curves have an unique ID", "[Hermite3]") {

    Hermite3 h1(p1, t1, p2, t2);
    Hermite3 h2(p1, t1, p2, t2);
    Hermite3 h3(p1, t1, p2, t2);
    Hermite3 h4(p1, t1, p2, t2);

    REQUIRE(h1.getID() != h2.getID());
    REQUIRE(h3.getID() != h4.getID());
}

TEST_CASE("control points of cubic Hermite curves can be accessed",
          "[Hermite3]") {

    Hermite3 h1(p1, t1, p2, t2);

    REQUIRE(h1.getControlPoint1() == p1);
    REQUIRE(h1.getControlPoint2() == p2);
    REQUIRE(h1.getTangentVector1() == t1);
    REQUIRE(h1.getTangentVector2() == t2);

    Eigen::Matrix2Xd B = (Eigen::Matrix2Xd(2,4) << p1, t1, t2, p2).finished()*C;

    REQUIRE(h1.getCurveMatrix() == B);
}

TEST_CASE("control points and tangent vectors of cubic Hermite curves can be"
          "changed", "[Hermite3]") {

    Eigen::Vector2d p1p(1, 0);
    Eigen::Vector2d p2p(0, 2);
    Eigen::Vector2d t1p(-2, 1);
    Eigen::Vector2d t2p(1, 2);

    Eigen::Matrix2Xd B = (Eigen::Matrix2Xd(2,4) << p1, t1, t2, p2).finished()*C;
    Hermite3 h1(p1, t1, p2, t2);

    SECTION("changing the first control point changes the matrix") {
        h1.setControlPoint1(p1p);
        REQUIRE(h1.getControlPoint1() == p1p);

        B = (Eigen::Matrix2Xd(2,4) << p1p, t1, t2, p2).finished()*C;
        REQUIRE(h1.getCurveMatrix() == B);
    }

    SECTION("changing the second control point changes the matrix") {
        h1.setControlPoint2(p2p);
        REQUIRE(h1.getControlPoint2() == p2p);

        B = (Eigen::Matrix2Xd(2,4) << p1, t1, t2, p2p).finished()*C;
        REQUIRE(h1.getCurveMatrix() == B);
    }

    SECTION("changing the first tangent vector changes the matrix") {
        h1.setTangentVector1(t1p);
        REQUIRE(h1.getTangentVector1() == t1p);

        B = (Eigen::Matrix2Xd(2,4) << p1, t1p, t2, p2).finished()*C;
        REQUIRE(h1.getCurveMatrix() == B);
    }

    SECTION("changing the second tangent vector changes the matrix") {
        h1.setTangentVector2(t2p);
        REQUIRE(h1.getTangentVector2() == t2p);

        B = (Eigen::Matrix2Xd(2,4) << p1, t1, t2p, p2).finished()*C;
        REQUIRE(h1.getCurveMatrix() == B);
    }
}

TEST_CASE("Hermite curves can be evaluated", "[Hermite3]") {
    Hermite3 h1(p1, t1, p2, t2);

    REQUIRE(h1.evaluateAt(0.0) == p1);
    REQUIRE(h1.evaluateAt(-1.0) == p1);
    REQUIRE(h1.evaluateAt(1.0) == p2);
    REQUIRE(h1.evaluateAt(2.0) == p2);

    Eigen::Vector2d expected(-0.25, 0.5);
    REQUIRE(h1.evaluateAt(0.5) == expected);
}