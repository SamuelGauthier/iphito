/**
 * @file Curve2DFactory.h
 * @brief A factory producing Curve2Ds and taking as input a root ASTNode
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2020-06-13
 */
#ifndef CURVE2D_FACTORY
#define CURVE2D_FACTORY

#include <memory>
#include <Eigen/Core>

#include "src/main/cli/ASTNode.h"
#include "Layer.h"

namespace iphito::renderer {

class Curve2DFactory {

public:
    Curve2DFactory(std::shared_ptr<parser::ASTNode> rootNode);

    void setCurveColor(const Eigen::Vector3d& curveColor);
    void setTangentColor(const Eigen::Vector3d& tangentColor);
    void setControlPointsColor(const Eigen::Vector3d& controlPointsColor);
    void setSecondDerivativeColor(const Eigen::Vector3d& secondDerivativeColor);
    void setCurveWidth(double width);

    std::unique_ptr<Layer> getRootLayer();

private:
    std::shared_ptr<parser::ASTNode> rootNode;

    Eigen::Vector3d curveColor;
    Eigen::Vector3d tangentColor;
    Eigen::Vector3d controlPointsColor;
    Eigen::Vector3d secondDerivativeColor;
    double curveWidth;
};

} /* namespace iphito::renderer */

#endif /* ifndef CURVE2D_FACTORY */
