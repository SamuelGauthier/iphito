/**
 * @file Test_Canvas.cpp
 * @brief Canvas tests
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-01
 */
#include <catch2/catch.hpp>
#include "renderer/Canvas.h"

using namespace iphito::renderer;

TEST_CASE("canvas size", "[Canvas]") {
    Canvas c = Canvas(3, 4);

    REQUIRE(c.getWidth() == 3);
    REQUIRE(c.getHeight() == 4);
}

