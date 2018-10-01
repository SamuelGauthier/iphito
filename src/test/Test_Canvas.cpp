/**
 * @file Test_Canvas.cpp
 * @brief Canvas tests
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-01
 */
#include "catch.h"
#include "Canvas.h"

TEST_CASE("canvas size", "[Canvas]") {
    Canvas c = Canvas(3, 4);

    REQUIRE(c.getWidth() == 3);
    REQUIRE(c.getHeight() == 4);
}

