/**
 * @file Curve2DFactory.cpp
 * @brief Implementation of a Curve2D factory
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2020-06-13
 */
#include "Curve2DFactory.h"

#include "Bezier2D.h"
#include "Hermite32D.h"
#include "Hermite52D.h"
#include "src/main/math/Bezier.h"
#include "src/main/math/Hermite3.h"
#include "src/main/math/Hermite5.h"
#include "src/main/utils/Logger.h"

namespace iphito::renderer {

using namespace iphito::math;
using namespace iphito::parser;
using namespace iphito::utils;

Curve2DFactory::Curve2DFactory(std::shared_ptr<ASTNode> rootNode) :
    rootNode{rootNode} {
}

void Curve2DFactory::setCurveColor(const Eigen::Vector3d& curveColor) {

    if (curveColor[0] < 0.0 || curveColor[1] < 0.0 || curveColor[2] < 0.0) {
        Logger::Instance()->critical("cannot set color with negative values");
        return;
    }

    this->curveColor = curveColor;
}

void Curve2DFactory::setTangentColor(const Eigen::Vector3d& tangentColor) {

    if (tangentColor[0] < 0.0 || tangentColor[1] < 0.0 ||
        tangentColor[2] < 0.0) {
        Logger::Instance()->critical("cannot set color with negative values");
        return;
    }

    this->tangentColor = tangentColor;
}

void Curve2DFactory::setControlPointsColor(const Eigen::Vector3d& controlPointsColor) {

    if (controlPointsColor[0] < 0.0 || controlPointsColor[1] < 0.0 ||
        controlPointsColor[2] < 0.0) {
        Logger::Instance()->critical("cannot set color with negative values");
        return;
    }

    this->controlPointsColor = controlPointsColor;
}

void Curve2DFactory::setSecondDerivativeColor(const Eigen::Vector3d& secondDerivativeColor) {

    if (secondDerivativeColor[0] < 0.0 ||
        secondDerivativeColor[1] < 0.0 ||
        secondDerivativeColor[2] < 0.0) {
        Logger::Instance()->critical("cannot set color with negative values");
        return;
    }

    this->secondDerivativeColor = secondDerivativeColor;
}

void Curve2DFactory::setCurveWidth(double width) {

    if (width <= 0.0) {
        Logger::Instance()->critical("cannot set a zero curve width");
        return;
    }
    this->curveWidth = width;
}

std::unique_ptr<Layer> Curve2DFactory::getRootLayer() {

    std::unique_ptr<Layer> rootLayer(new Layer());

    for (auto& i : this->rootNode->getChildren()) {
        auto nodeType = i->getNodeType();

        switch (nodeType) {
            case NodeType::Bezier:
                {
                    auto bezier = std::static_pointer_cast<Bezier>(i->getCurve());
                    std::unique_ptr<Curve2D> bezier2D(new Bezier2D(bezier,
                                this->curveWidth, this->curveColor,
                                this->controlPointsColor,
                                this->controlPointsColor));
                    rootLayer->addCurve(bezier2D);
                }
                break;
            case NodeType::Hermite3:
                {
                    auto hermite3 = std::static_pointer_cast<Hermite3>(i->getCurve());
                    std::unique_ptr<Curve2D> hermite32D(new Hermite32D(
                                hermite3, this->curveWidth, this->curveColor,
                                this->tangentColor, this->controlPointsColor));
                    rootLayer->addCurve(hermite32D);
                }
                break;
            case NodeType::Hermite5:
                {
                    auto hermite5 = std::static_pointer_cast<Hermite5>(i->getCurve());
                    std::unique_ptr<Curve2D> hermite52D(new Hermite52D(
                                hermite5, this->curveWidth, this->curveColor,
                                this->tangentColor, this->secondDerivativeColor,
                                this->controlPointsColor));
                    rootLayer->addCurve(hermite52D);
                }
                break;
            case NodeType::Root:
            default:
                break;

        }
    }

    return rootLayer;
}

} /* namespace iphito::renderer */
