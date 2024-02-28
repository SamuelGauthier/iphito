/**
 * @file ASTNode.h
 * @brief Describes an AST Node
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2020-06-04
 */
#ifndef ASTNODE_H
#define ASTNODE_H

#include <memory>
#include <vector>

#include "src/main/math/Curve.h"
#include "src/main/renderer/Curve2D.h"

namespace iphito::parser {

enum class NodeType { 
    Root,
    Bezier,
    Hermite3,
    Hermite5
};

class ASTNode {

public:
    ASTNode();
    ASTNode(NodeType curveType, std::shared_ptr<iphito::math::Curve> curve);
    /* ~ASTNode(); */

    NodeType getNodeType();
    std::shared_ptr<iphito::math::Curve> getCurve();
    std::shared_ptr<iphito::renderer::Curve2D> getCurve2D();
    void addChild(std::shared_ptr<ASTNode> node);
    std::vector<std::shared_ptr<ASTNode>> getChildren();

private:
    NodeType nodeType;
    std::shared_ptr<iphito::math::Curve> curve;
    std::vector<std::shared_ptr<ASTNode>> children;
};

} /* namespace iphito::cli */

#endif /* ifndef ASTNODE_H */
