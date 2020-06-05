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
#include <eigen3/Eigen/Core>

#include "cli/ASTNode.h"
#include "math/Curve.h"

namespace iphito::parser {

class Parser {

public:
    Parser(std::string input);

    bool parse();

    bool bezierCurve(std::string& errorMessage);
    bool bezierName(std::string& errorMessage);

    bool listPoints2D(std::vector<Eigen::Vector2d>& points, 
                      std::string& errorMessage);
    bool point2D(Eigen::Vector2d& point, std::string& errorMessage);

    bool character(char c, std::string& errorMessage);
    bool leftSquareBracket(std::string& errorMessage);
    bool rightSquareBracket(std::string& errorMessage);
    bool leftParanthesis(std::string& errorMessage);
    bool rightParanthesis(std::string& errorMessage);
    bool number(double& number, std::string& errorMessage);
    bool comma(std::string& errorMessage);

    std::shared_ptr<ASTNode> getRootNode();

private:
    std::stringstream inputStream;
    std::shared_ptr<ASTNode> root;

    std::string toLower(std::string s);
};

} /* namespace cli */

#endif /* ifndef CURVE_H */
