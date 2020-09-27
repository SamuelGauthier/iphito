/**
 * @file ParserTest.cpp
 * @brief Parser tests
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2020-09-15
 */
#include <iostream>
#include "catch.h"
#include "cli/Parser.h"

using namespace iphito::parser;

TEST_CASE("a bezier curve with two points can be parsed") {

    const std::string input = "bezier[(-0.5, 0), (-0.7, 0.6)]";
    Parser parser(input);
    REQUIRE(parser.parse() == true);
}

TEST_CASE("a bezier curve with one point cannot be parsed") {

    const std::string input = "bezier[(-0.5, 0)]";
    Parser parser(input);
    REQUIRE(parser.parse() == false);
}

TEST_CASE("a cubic hermite curve can be parsed") {

    const std::string input = "hermite3 [ (0, 0), (1, 2), (0.25, 0), (1, -2) ]";
    Parser parser(input);
    REQUIRE(parser.parse() == true);
}

TEST_CASE("a cubic hermite curve must have two points and two tangents") {

    std::string input = "hermite3 [ (0, 0), (1, 2), (0.25, 0), (1, -2) ]";
    Parser parser(input);
    REQUIRE(parser.parse() == true);

    input = "hermite3 [ (0, 0), (1, 2), (0.25, 0)]";
    parser = Parser(input);
    REQUIRE(parser.parse() == false);
}

TEST_CASE("a quintic hermite curve can be parsed") {

    const std::string input = "hermite5 [ (0, 0), (1, 2), (-4, 0), (0.25, 0),"
                              "(1, -2), (4, 0) ]";
    Parser parser(input);
    REQUIRE(parser.parse() == true);
}

TEST_CASE("a quintic hermite curve must have two points two tangents and"
          "two second derivatives") {

    std::string input = "hermite5 [ (0, 0), (1, 2), (-4, 0), (0.25, 0),"
                              " (1, -2), (4, 0) ]";
    Parser parser(input);
    REQUIRE(parser.parse() == true);

    input = "hermite5 [ (0, 0), (1, 2), (-4, 0), (0.25, 0), (4, 0) ]";
    parser = Parser(input);
    REQUIRE(parser.parse() == false);
}   

TEST_CASE("multiple curves can be parsed") {

    const std::string input = "bezier[(-0.5, 0), (-0.7, 0.6)]\n"
        "hermite3 [ (0, 0), (1, 2), (0.25, 0), (1, -2) ]\n"
        "hermite5 [ (0, 0), (1, 2), (-4, 0), (0.25, 0), (1, -2), (4, 0) ]\n";
    Parser parser(input);
    REQUIRE(parser.parse() == true);
}

TEST_CASE("spaces do not matter") {

    const std::string input = "bezier[(-0.5, 0),             (-0.7,0.6)]";
    Parser parser(input);
    REQUIRE(parser.parse() == true);
}

TEST_CASE("a float doesn't require a period") {

    std::string input = "bezier[(-0.5, 0), (-0.7, 0.1)]";
    Parser parser(input);
    REQUIRE(parser.parse() == true);

    input = "bezier[(-0.5, 0.0), (-0.7, 0.1)]";
    parser = Parser(input);
    REQUIRE(parser.parse() == true);
}

TEST_CASE("a float can be negative") {

    const std::string input = "bezier[(-0.5, 0), (-0.7, 0.1)]";
    Parser parser(input);
    REQUIRE(parser.parse() == true);
}

TEST_CASE("a negative float must have only one negative sign") {

    std::string input = "bezier[(-0.5, 0), (-0.7, 0.1)]";
    Parser parser(input);
    REQUIRE(parser.parse() == true);

    input = "bezier[(--0.5, 0), (-0.7, 0.1)]";
    parser = Parser(input);
    REQUIRE(parser.parse() == false);

}

TEST_CASE("a point must have two floats") {

    std::string input = "bezier[(-0.5, 0), (-0.7)]";
    Parser parser(input);
    REQUIRE(parser.parse() == false);

    input = "bezier[(-0.5, 0), (-0.7, 0.1)]";
    parser = Parser(input);
    REQUIRE(parser.parse() == true);
}

TEST_CASE("a comment starts with a hash and ends with a newline") {

    std::string input = "#bezier[(-0.5, 0), (-0.7)]";
    Parser parser(input);
    REQUIRE(parser.parse() == true);

    input = "//bezier[(-0.5, 0), (-0.7)]";
    parser = Parser(input);
    REQUIRE(parser.parse() == false);

    input = "bezier[(-0.5, 0), (-0.7, 0.1)]#test bezier[(-0.5, 0), (-0.7, 0.1)]";
    parser = Parser(input);
    REQUIRE(parser.parse() == true);
    REQUIRE(parser.parse() == true);
    REQUIRE(parser.parse() == false);
    auto children = parser.getRootNode()->getChildren();
    REQUIRE(children.size() == 1);

    input = "bezier[(-0.5, 0), (-0.7, 0.1)]#test\nbezier[(-0.5, 0), (-0.7, 0.1)]";
    parser = Parser(input);
    REQUIRE(parser.parse() == true);
    REQUIRE(parser.parse() == true);
    REQUIRE(parser.parse() == true);
    children = parser.getRootNode()->getChildren();
    REQUIRE(children.size() == 2);
}

TEST_CASE("a newline does not indicate a new curve") {

    std::string input = "bezier[(-0.5, 0), (-0.7, 0.1)]bezier[(-0.5, 0), (-0.7, 0.1)]";
    Parser parser(input);
    REQUIRE(parser.parse() == true);
    REQUIRE(parser.parse() == true);
    auto children = parser.getRootNode()->getChildren();
    REQUIRE(children.size() == 2);

    input = "bezier[(-0.5, 0), (-0.7, 0.1)]\nhermite3 [ (0, 0), (1, 2), (0.25, 0), (1, -2) ]";
    parser = Parser(input);
    REQUIRE(parser.parse() == true);
    REQUIRE(parser.parse() == true);
    children = parser.getRootNode()->getChildren();
    REQUIRE(children.size() == 2);
}



