/**
 * @file Parser.h
 * @brief Describes a parser for the iphito syntax
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2020-06-03
 */
#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <Eigen/Core>

#include "src/main/cli/ASTNode.h"
#include "src/main/math/Curve.h"

namespace iphito::parser {

class Parser {

public:
    Parser(std::string input);

    bool parse();
    std::shared_ptr<ASTNode> getRootNode();

private:
    std::stringstream inputStream;
    std::shared_ptr<ASTNode> root;

    std::string toLower(std::string s);

    bool bezierCurve();
    bool hermite3Curve();
    bool hermite5Curve();
    bool comment();

    bool listPoints2D(std::vector<Eigen::Vector2d>& points, 
                      std::string& errorMessage);
    bool point2D(Eigen::Vector2d& point, std::string& errorMessage);

    bool string(const std::string s, std::string& errorMessage);
    bool character(const char c, std::string& errorMessage);
    bool number(double& number, std::string& errorMessage);
};

} /* namespace cli */

#endif /* ifndef CURVE_H */
