/**
 * @file Parser.cpp
 * @brief Implementation of the iphito parser
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2020-06-03
 */
#include "Parser.h"

#include "src/main/math/Bezier.h"
#include "src/main/math/Hermite3.h"
#include "src/main/math/Hermite5.h"
#include "src/main/utils/Logger.h"

namespace iphito::parser {

using namespace iphito::math;
using namespace iphito::utils;

Parser::Parser(std::string input) : inputStream{input}, root{new ASTNode()} {}

bool Parser::parse() {

    if (bezierCurve()) {
        return true;
    }
    else if (hermite3Curve()) {
        return true;
    }
    else if (hermite5Curve()) {
        return true;
    }
    else if (comment()) {
        return true;
    }

    return false;
}

bool Parser::bezierCurve() {

    std::string errorMessage = "";
    std::vector<Eigen::Vector2d> points;

    if (!string("bezier", errorMessage)) {
        return false;
    }
    if (!character('[', errorMessage)) {
        Logger::Instance()->critical(errorMessage);
        return false;
    }
    if (!listPoints2D(points, errorMessage)) {
        Logger::Instance()->critical(errorMessage);
        return false;
    }
    if (!character(']', errorMessage)) {
        Logger::Instance()->critical(errorMessage);
        return false;
    }

    std::shared_ptr<Bezier> bezier(new Bezier(points));
    std::shared_ptr<ASTNode> node(new ASTNode(NodeType::Bezier, bezier));
    this->root->addChild(node);

    return true;
}

bool Parser::hermite3Curve() {

    std::string errorMessage = "";
    if (!string("hermite3", errorMessage)) {
        return false;
    }
    if (!character('[', errorMessage)) {
        Logger::Instance()->critical(errorMessage);
        return false;
    }

    Eigen::Vector2d point1;
    Eigen::Vector2d tangent1;
    Eigen::Vector2d point2;
    Eigen::Vector2d tangent2;

    if (!point2D(point1, errorMessage)) {
        Logger::Instance()->critical(errorMessage);
        return false;
    }
    if (!character(',', errorMessage)) {
        return false;
    }
    if (!point2D(tangent1, errorMessage)) {
        Logger::Instance()->critical(errorMessage);
        return false;
    }
    if (!character(',', errorMessage)) {
        return false;
    }
    if (!point2D(point2, errorMessage)) {
        Logger::Instance()->critical(errorMessage);
        return false;
    }
    if (!character(',', errorMessage)) {
        return false;
    }
    if (!point2D(tangent2, errorMessage)) {
        Logger::Instance()->critical(errorMessage);
        return false;
    }

    if (!character(']', errorMessage)) {
        Logger::Instance()->critical(errorMessage);
        return false;
    }

    std::shared_ptr<Hermite3> hermite3(new Hermite3(point1, tangent1,
                                                    point2, tangent2));
    std::shared_ptr<ASTNode> node(new ASTNode(NodeType::Hermite3, hermite3));
    this->root->addChild(node);

    return true;
}

bool Parser::hermite5Curve() {

    std::string errorMessage = "";
    if (!string("hermite5", errorMessage)) {
        return false;
    }
    if (!character('[', errorMessage)) {
        Logger::Instance()->critical(errorMessage);
        return false;
    }

    Eigen::Vector2d point1;
    Eigen::Vector2d tangent1;
    Eigen::Vector2d secondDerivative1;
    Eigen::Vector2d point2;
    Eigen::Vector2d tangent2;
    Eigen::Vector2d secondDerivative2;

    if (!point2D(point1, errorMessage)) {
        Logger::Instance()->critical(errorMessage);
        return false;
    }
    if (!character(',', errorMessage)) {
        return false;
    }
    if (!point2D(tangent1, errorMessage)) {
        Logger::Instance()->critical(errorMessage);
        return false;
    }
    if (!character(',', errorMessage)) {
        return false;
    }
    if (!point2D(secondDerivative1, errorMessage)) {
        Logger::Instance()->critical(errorMessage);
        return false;
    }
    if (!character(',', errorMessage)) {
        return false;
    }
    if (!point2D(point2, errorMessage)) {
        Logger::Instance()->critical(errorMessage);
        return false;
    }
    if (!character(',', errorMessage)) {
        return false;
    }
    if (!point2D(tangent2, errorMessage)) {
        Logger::Instance()->critical(errorMessage);
        return false;
    }
    if (!character(',', errorMessage)) {
        return false;
    }
    if (!point2D(secondDerivative2, errorMessage)) {
        Logger::Instance()->critical(errorMessage);
        return false;
    }

    if (!character(']', errorMessage)) {
        Logger::Instance()->critical(errorMessage);
        return false;
    }

    std::shared_ptr<Hermite5> hermite5(new Hermite5(point1, tangent1,
                secondDerivative1, point2, tangent2, secondDerivative2));
    std::shared_ptr<ASTNode> node(new ASTNode(NodeType::Hermite5, hermite5));
    this->root->addChild(node);

    return true;
}

bool Parser::comment() {

    std::string errorMessage = "";

    if(!character('#', errorMessage)) {
        return false;
    }

    std::string complete = "";
    
    char current = this->inputStream.get();
    complete.push_back(current);

    while (current != '\n' && this->inputStream) {
        current = this->inputStream.get();
        complete.push_back(current);
    }

    return true;
}

bool Parser::listPoints2D(std::vector<Eigen::Vector2d>& points,
                          std::string& errorMessage) {

    Eigen::Vector2d p;

    if (!point2D(p, errorMessage)) {
        return false;
    }
    if (!character(',', errorMessage)) {
        return false;
    }

    points.push_back(p);

    if (!point2D(p, errorMessage)) {
        return false;
    }

    points.push_back(p);

    if (!character(',', errorMessage)) {
        return true;
    }

    while (point2D(p, errorMessage)) {

        points.push_back(p);

        if (!character(',', errorMessage)) {
            return true;
        }
    }
    
    return false;
}

bool Parser::point2D(Eigen::Vector2d& point, std::string& errorMessage) {

    double p1 = 0.0;
    double p2 = 0.0;

    if (!character('(', errorMessage)) {
        return false;
    }
    if (!number(p1, errorMessage)) {
        return false;
    }
    if (!character(',', errorMessage)) {
        return false;
    }
    if (!number(p2, errorMessage)) {
        return false;
    }
    if (!character(')', errorMessage)) {
        return false;
    }

    Eigen::Vector2d p(p1, p2);
    point = p;

    return true;
}

bool Parser::string(const std::string s, std::string& errorMessage) {

    std::string expectedName = s;
    int expectedNameSize = expectedName.size();

    std::string actualName;

    for (int i = 0; i < expectedNameSize; i++) {

        char actual = this->inputStream.get();

        if (std::isspace(actual)) {
            while (std::isspace(actual)) {
                actual = this->inputStream.get();
            }
        }

        if (actual == s[i]) {
            actualName.push_back(actual);
            continue;
        }
        else {
            break;
        }
    }

    actualName = this->toLower(actualName);

    if (actualName != expectedName) {

        errorMessage = "Expected '" + expectedName + "' but found '" +
                       actualName + "'";

        for (int i = 0; i < actualName.size() + 1; i++) {
            this->inputStream.unget();
        }

        return false;
    }

    return true;
}

bool Parser::character(const char c, std::string& errorMessage) {

    char actual = this->inputStream.get();

    if (!std::isspace(c)) {
        while (std::isspace(actual) && this->inputStream) {
            actual = this->inputStream.get(); 
        }
    }

    if (actual != c) {
        errorMessage = "syntax error: expected '" + std::string(1, c)
                       + "' but got '" + std::string(1, actual) + "'";
        this->inputStream.unget();

        return false;
    }

    return true;
}

bool Parser::number(double& n, std::string& errorMessage) {

    std::string number = "";

    char sign = this->inputStream.peek();
    while (std::isspace(sign) && this->inputStream) {
        this->inputStream.get();
        sign = this->inputStream.peek();
    }

    if (sign == '-') {
        number += sign;
        this->inputStream.get();
    }

    char digit = inputStream.get();
    while (std::isspace(digit) && this->inputStream) {
        digit = this->inputStream.get();
    }
    while (digit >= '0' && digit <= '9') {
        number += digit;
        digit = this->inputStream.get();
    }

    if(digit == '.') {
        number += digit;
        digit = this->inputStream.get();

        while (digit >= '0' && digit <= '9') {
            number += digit;
            digit = this->inputStream.get();
        }
    }

    if (number.empty()) {
        char actual = this->inputStream.peek();
        errorMessage = "expected a decimal number but got: '" +
                        std::to_string(actual) + "'";
        return false;
    }

    try {
        n = stod(number);
    }
    catch (std::exception e) {
        errorMessage = "Cannot convert string to double"; 
        return false;
    }

    this->inputStream.unget();
    return true;
}

std::shared_ptr<ASTNode> Parser::getRootNode() {
    return this->root;
}

std::string Parser::toLower(std::string s) {
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c) { return tolower(c);});
    return s;
}

} /* namespace iphito::cli */
