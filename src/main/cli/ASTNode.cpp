/**
 * @file ASTNode.cpp
 * @brief Implementation of an ASTNode
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2020-06-04
 */
#include "ASTNode.h"

#include <iostream>
#include <Eigen/Core>

#include "src/main/renderer/Bezier2D.h"

namespace iphito::parser {

using namespace iphito::math;
using namespace iphito::renderer;

ASTNode::ASTNode() : nodeType{NodeType::Root}, curve{nullptr},
    children{std::vector<std::shared_ptr<ASTNode>>()} {
}

ASTNode::ASTNode(NodeType nodeType, std::shared_ptr<Curve> curve) :
    nodeType{nodeType}, curve{curve}, 
    children{std::vector<std::shared_ptr<ASTNode>>()} {
}

NodeType ASTNode::getNodeType() {
    return this->nodeType;
}

std::shared_ptr<Curve> ASTNode::getCurve() {
    return this->curve;
}

std::shared_ptr<Curve2D> ASTNode::getCurve2D() {

    Eigen::Vector3d curveColor(1.0, 0.0, 0.0);
    Eigen::Vector3d tangentColor(0.0, 0.0, 1.0);
    Eigen::Vector3d controlPointsColor(0.0, 1.0, 0.0);
    Eigen::Vector3d secondDerivativeColor(0.0, 1.0, 1.0);
    double curveWidth = 0.01;

    std::shared_ptr<Curve2D> curve2D;

    switch (this->nodeType) {
        case NodeType::Bezier: {
                auto bezier = std::static_pointer_cast<Bezier>(this->curve);
                curve2D = std::shared_ptr<Bezier2D>(new Bezier2D(bezier,
                            curveWidth, curveColor, controlPointsColor,
                            controlPointsColor));
                break;
            }
        default:
            curve2D = nullptr;
            break;
    }
    
    return curve2D;
}

void ASTNode::addChild(std::shared_ptr<ASTNode> node) {
    this->children.push_back(node);
}

std::vector<std::shared_ptr<ASTNode>> ASTNode::getChildren() {
    return this->children;
}

} /* namespace iphito::cli */
