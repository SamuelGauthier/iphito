/**
 * @file Parser.cpp
 * @brief Implementation of the iphito parser
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2020-06-03
 */

#include "Parser.h"

#include "math/Bezier.h"
#include "utils/Logger.h"

namespace iphito::parser {

using namespace iphito::math;
using namespace iphito::utils;

Parser::Parser(std::string input) : inputStream{input}, root{new ASTNode()} {}

bool Parser::parse() {

    std::string errorMessage = "";

    if (!bezierCurve(errorMessage)) {
        return false;
    }

    return true;
}

bool Parser::bezierCurve(std::string& errorMessage) {

    std::vector<Eigen::Vector2d> points;

    if (!bezierName(errorMessage)) {
        Logger::Instance()->critical(errorMessage);
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

bool Parser::bezierName(std::string& errorMessage) {

    std::string bezierName = "bezier";
    int bezierNameSize = bezierName.size();

    std::string actualName(bezierNameSize, ' ');

    this->inputStream.read(&actualName[0], bezierNameSize);
    actualName = this->toLower(actualName);

    if (actualName != bezierName) {

        for (int i = 0; i < bezierNameSize; i++) {
            this->inputStream.unget();
        }

        return false;
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
        return true;
    }

    points.push_back(p);

    while (point2D(p, errorMessage)) {
        if (!character(',', errorMessage)) {
            return true;
        }
        points.push_back(p);
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

bool Parser::character(char c, std::string& errorMessage) {

    char actual = this->inputStream.get();

    if (actual != c) {
        errorMessage = "syntax error: expected '" + std::to_string(c)
                       + "' but got '" + std::to_string(actual) + "'";
        this->inputStream.unget();

        return false;
    }

    return true;
}

bool Parser::leftSquareBracket(std::string& errorMessage) {

    char actual = this->inputStream.get();

    if (actual != '[') {
        errorMessage = "syntax error: expected '[' but got '" + 
                       std::to_string(actual) + "'";
        this->inputStream.unget();

        return false;
    }

    return true;
}

bool Parser::rightSquareBracket(std::string& errorMessage) {

    char actual = this->inputStream.get();

    if (actual != ']') {
        errorMessage = "syntax error: expected ']' but got '" + 
                       std::to_string(actual) + "'";
        this->inputStream.unget();

        return false;
    }

    return true;
}

bool Parser::leftParanthesis(std::string& errorMessage) {

    char actual = this->inputStream.get();

    if (actual != '(') {
        errorMessage = "syntax error: expected '(' but got '" + 
                       std::to_string(actual) + "'";
        this->inputStream.unget();

        return false;
    }

    return true;
}

bool Parser::rightParanthesis(std::string& errorMessage) {

    char actual = this->inputStream.get();

    if (actual != ')') {
        errorMessage = "syntax error: expected ')' but got '" + 
                       std::to_string(actual) + "'";
        this->inputStream.unget();

        return false;
    }

    return true;
}

bool Parser::number(double& n, std::string& errorMessage) {

    std::string number = "";

    char sign = this->inputStream.peek();
    if (sign == '-') {
        number += sign;
        this->inputStream.get();
    }

    char digit = inputStream.get();
    while ((digit >= '0' && digit <= '9') || digit == '.') {
        number += digit;
        digit = this->inputStream.get();
    }

    if (number.empty()) {
        char actual = this->inputStream.peek();
        errorMessage = "expected a decimal number but got: '" +
                        std::to_string(actual) + "'";
        return false;
    }

    n = stod(number);
    this->inputStream.unget();
    return true;
}

bool Parser::comma(std::string& errorMessage) {

    char actual = this->inputStream.get();

    if (actual != ',') {

        errorMessage = "syntax error: expected ',' but got '";
        errorMessage.push_back(actual);

        this->inputStream.unget();
        return false;
    }

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
