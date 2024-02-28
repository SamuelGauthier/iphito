/**
 * @file Test_Canvas.cpp
 * @brief Canvas tests
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-01
 */
#include "src/main/renderer/Canvas.h"
#include <catch2/catch_test_macros.hpp>

using namespace iphito::renderer;

TEST_CASE("canvas size", "[Canvas]") {
  Canvas c = Canvas(3, 4);

  REQUIRE(c.getWidth() == 3);
  REQUIRE(c.getHeight() == 4);
}
