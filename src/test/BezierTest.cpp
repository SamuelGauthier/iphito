/**
 * @file BezierTest.cpp
 * @brief Bezier test
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2019-03-02
 */
#include <eigen3/Eigen/Core>
#include <memory>
#include <vector>

#include "catch.h"
#include "math/Curve.h"
#include "math/Bezier.h"
#include "utils/Utils.h"

const Eigen::Vector2d p0(-1, 0);
const Eigen::Vector2d p1(0, 1);
const Eigen::Vector2d p2(2, 0);
const std::vector<Eigen::Vector2d> p = {p0, p1, p2};

TEST_CASE("A Bezier curve can be evaluated", "[Bezier]") {

    Bezier b1(p);
    Eigen::Vector2d e1 = b1.evaluateAt(0.0);
    Eigen::Vector2d e2 = b1.evaluateAt(1.0);
    Eigen::Vector2d e3 = b1.evaluateAt(0.5);
    Eigen::Vector2d e4 = b1.evaluateAt(0.25);
    Eigen::Vector2d e5 = b1.evaluateAt(0.75);
    Eigen::Vector2d e6 = b1.evaluateAt(0.1);
    Eigen::Vector2d e7 = b1.evaluateAt(0.81);
    Eigen::Vector2d e8 = b1.evaluateAt(0.2);
    Eigen::Vector2d e9 = b1.evaluateAt(0.3);
    Eigen::Vector2d e10 = b1.evaluateAt(0.4);
    Eigen::Vector2d e11 = b1.evaluateAt(0.6);
    Eigen::Vector2d e12 = b1.evaluateAt(0.9);

    Eigen::Vector2d a1 = p0;
    REQUIRE(Utils::nearlyEqual(e1[0], p0[0]) == true);
    REQUIRE(Utils::nearlyEqual(e1[1], p0[1]) == true);

    Eigen::Vector2d a2 = p2;
    REQUIRE(Utils::nearlyEqual(e2[0], p2[0]) == true);
    REQUIRE(Utils::nearlyEqual(e2[1], p2[1]) == true);

    Eigen::Vector2d a3 = Eigen::Vector2d(0.25, 0.5);
    REQUIRE(Utils::nearlyEqual(e3[0], a3[0]) == true);
    REQUIRE(Utils::nearlyEqual(e3[1], a3[1]) == true);

    Eigen::Vector2d a4 = Eigen::Vector2d(-0.4375, 0.375);
    REQUIRE(Utils::nearlyEqual(e4[0], a4[0]) == true);
    REQUIRE(Utils::nearlyEqual(e4[1], a4[1]) == true);

    Eigen::Vector2d a5 = Eigen::Vector2d(1.0625, 0.375);
    REQUIRE(Utils::nearlyEqual(e5[0], a5[0]) == true);
    REQUIRE(Utils::nearlyEqual(e5[1], a5[1]) == true);

    Eigen::Vector2d a6 = Eigen::Vector2d(-0.79, 0.18);
    REQUIRE(Utils::nearlyEqual(e6[0], a6[0]) == true);
    REQUIRE(Utils::nearlyEqual(e6[1], a6[1]) == true);

    Eigen::Vector2d a7 = Eigen::Vector2d(1.2761, 0.3078);
    REQUIRE(Utils::nearlyEqual(e7[0], a7[0]) == true);
    REQUIRE(Utils::nearlyEqual(e7[1], a7[1]) == true);

    Eigen::Vector2d a8 = Eigen::Vector2d(-0.56, 0.32);
    REQUIRE(Utils::nearlyEqual(e8[0], a8[0]) == true);
    REQUIRE(Utils::nearlyEqual(e8[1], a8[1]) == true);

    Eigen::Vector2d a9 = Eigen::Vector2d(-0.31, 0.42);
    REQUIRE(Utils::nearlyEqual(e9[0], a9[0]) == true);
    REQUIRE(Utils::nearlyEqual(e9[1], a9[1]) == true);

    Eigen::Vector2d a10 = Eigen::Vector2d(-0.04, 0.48);
    REQUIRE(Utils::nearlyEqual(e10[0], a10[0]) == true);
    REQUIRE(Utils::nearlyEqual(e10[1], a10[1]) == true);

    Eigen::Vector2d a11 = Eigen::Vector2d(0.56, 0.48);
    REQUIRE(Utils::nearlyEqual(e11[0], a11[0]) == true);
    REQUIRE(Utils::nearlyEqual(e11[1], a11[1]) == true);

    Eigen::Vector2d a12 = Eigen::Vector2d(1.61, 0.18);
    REQUIRE(Utils::nearlyEqual(e12[0], a12[0]) == true);
    REQUIRE(Utils::nearlyEqual(e12[1], a12[1]) == true);
}

TEST_CASE("A Bezier curve can be cast into a Curve", "[Bezier]") {

    std::unique_ptr<Bezier> b1(new Bezier(p));
    std::unique_ptr<Curve> c1 = std::move(b1);

    Eigen::Vector2d e1 = c1->evaluateAt(0.0);
    Eigen::Vector2d e2 = c1->evaluateAt(0.1);
    Eigen::Vector2d e3 = c1->evaluateAt(0.2);
    Eigen::Vector2d e4 = c1->evaluateAt(0.3);
    Eigen::Vector2d e5 = c1->evaluateAt(0.4);
    Eigen::Vector2d e6 = c1->evaluateAt(0.5);
    Eigen::Vector2d e7 = c1->evaluateAt(0.6);
    Eigen::Vector2d e8 = c1->evaluateAt(0.7);
    Eigen::Vector2d e9 = c1->evaluateAt(0.8);
    Eigen::Vector2d e10 = c1->evaluateAt(0.9);
    Eigen::Vector2d e11 = c1->evaluateAt(1.0);

    Eigen::Vector2d a1 = p0;
    REQUIRE(Utils::nearlyEqual(e1[0], a1[0]) == true);
    REQUIRE(Utils::nearlyEqual(e1[1], a1[1]) == true);

    Eigen::Vector2d a2 = Eigen::Vector2d(-0.79, 0.18);
    REQUIRE(Utils::nearlyEqual(e2[0], a2[0]) == true);
    REQUIRE(Utils::nearlyEqual(e2[1], a2[1]) == true);

    Eigen::Vector2d a3 = Eigen::Vector2d(-0.56, 0.32);
    REQUIRE(Utils::nearlyEqual(e3[0], a3[0]) == true);
    REQUIRE(Utils::nearlyEqual(e3[1], a3[1]) == true);

    Eigen::Vector2d a4 = Eigen::Vector2d(-0.31, 0.42);
    REQUIRE(Utils::nearlyEqual(e4[0], a4[0]) == true);
    REQUIRE(Utils::nearlyEqual(e4[1], a4[1]) == true);

    Eigen::Vector2d a5 = Eigen::Vector2d(-0.04, 0.48);
    REQUIRE(Utils::nearlyEqual(e5[0], a5[0]) == true);
    REQUIRE(Utils::nearlyEqual(e5[1], a5[1]) == true);

    Eigen::Vector2d a6 = Eigen::Vector2d(0.25, 0.5);
    REQUIRE(Utils::nearlyEqual(e6[0], a6[0]) == true);
    REQUIRE(Utils::nearlyEqual(e6[1], a6[1]) == true);

    Eigen::Vector2d a7 = Eigen::Vector2d(0.56, 0.48);
    REQUIRE(Utils::nearlyEqual(e7[0], a7[0]) == true);
    REQUIRE(Utils::nearlyEqual(e7[1], a7[1]) == true);

    Eigen::Vector2d a8 = Eigen::Vector2d(0.89, 0.42);
    REQUIRE(Utils::nearlyEqual(e8[0], a8[0]) == true);
    REQUIRE(Utils::nearlyEqual(e8[1], a8[1]) == true);

    Eigen::Vector2d a9 = Eigen::Vector2d(1.24, 0.32);
    REQUIRE(Utils::nearlyEqual(e9[0], a9[0]) == true);
    REQUIRE(Utils::nearlyEqual(e9[1], a9[1]) == true);

    Eigen::Vector2d a10 = Eigen::Vector2d(1.61, 0.18);
    REQUIRE(Utils::nearlyEqual(e10[0], a10[0]) == true);
    REQUIRE(Utils::nearlyEqual(e10[1], a10[1]) == true);

    Eigen::Vector2d a11 = p2;
    REQUIRE(Utils::nearlyEqual(e11[0], a11[0]) == true);
    REQUIRE(Utils::nearlyEqual(e11[1], a11[1]) == true);
}

TEST_CASE("Bezier control points can be retrieved", "[Bezier]") {

    Bezier b1(p);

    std::vector<Eigen::Vector2d> controlPoints = b1.getPoints();

    REQUIRE(controlPoints[0] == p0);
    REQUIRE(controlPoints[1] == p1);
    REQUIRE(controlPoints[2] == p2);
}

TEST_CASE("Bezier Berstein coefficients can be retrieved", "[Bezier]") {

    Bezier b1(p);

    std::map<int, std::pair<Eigen::Vector2d, double>> pointsAndBernstein =
        b1.getPointsAndBernstein();

    REQUIRE(pointsAndBernstein[0].second == 1.0);
    REQUIRE(pointsAndBernstein[1].second == 2.0);
    REQUIRE(pointsAndBernstein[2].second == 1.0);
}
