/**
 * @file Test_Layer.cpp
 * @brief Layer tests
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-09-28
 */
#include "catch.h"
#include "Layer.h"
#include "Canvas.h"

TEST_CASE("layer have an unique ID", "[Layer]") {
    Layer l1;

    REQUIRE(l1.getID() == 0);
}

TEST_CASE("canvas size", "[Canvas]") {
    Canvas c = Canvas(3, 4);

    REQUIRE(c.getWidth() == 3);
    REQUIRE(c.getHeight() == 4);
}
