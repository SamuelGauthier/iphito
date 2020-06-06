#include <iostream>
#include <memory>
#include <stdexcept>
#include <eigen3/Eigen/Core>
#include <limits>
#include <map>

#include "cli/Parser.h"
#include "cli/ASTNode.h"
#include "math/Bezier.h"
#include "math/Hermite3.h"
#include "renderer/Bezier2D.h"
#include "renderer/Canvas.h"
#include "renderer/Curve2D.h"
#include "renderer/Hermite32D.h"
#include "renderer/Hermite52D.h"
#include "renderer/Layer.h"
#include "renderer/Shader.h"
#include "renderer/Window.h"
#include "utils/Logger.h"
#include "utils/Utils.h"

using namespace iphito::parser;
using namespace iphito::math;
using namespace iphito::renderer;
using namespace iphito::utils;

int main(int argc, char *argv[])
{

    int WIDTH = 640;
    int HEIGHT = 640;

    std::string input = Utils::readInput();

    Parser parser(input);
    while (parser.parse()) {}

    try{
        Window w(WIDTH, HEIGHT, "iphito");
        std::unique_ptr<Canvas> canvas(new Canvas(WIDTH, HEIGHT));
        std::unique_ptr<Layer> rootLayer(new Layer());

        Eigen::Vector3d curveColor(1.0, 0.0, 0.0);
        Eigen::Vector3d tangentColor(0.0, 0.0, 1.0);
        Eigen::Vector3d controlPointsColor(0.0, 1.0, 0.0);
        Eigen::Vector3d secondDerivativeColor(0.0, 1.0, 1.0);
        double curveWidth = 0.01;

        std::shared_ptr<ASTNode> rootNode = parser.getRootNode();
        for (auto& i : rootNode->getChildren()) {
            auto nodeType = i->getNodeType();

            switch (nodeType) {
                case NodeType::Bezier:
                    {
                        auto bezier = std::static_pointer_cast<Bezier>(i->getCurve());
                        std::unique_ptr<Curve2D> bezier2D(new Bezier2D(bezier,
                                    curveWidth, curveColor, controlPointsColor,
                                    controlPointsColor));
                        rootLayer->addCurve(bezier2D);
                    }
                    break;
                case NodeType::Hermite3:
                    {
                        auto hermite3 = std::static_pointer_cast<Hermite3>(i->getCurve());
                        std::unique_ptr<Curve2D> hermite32D(new Hermite32D(
                                    hermite3, curveWidth, curveColor,
                                    tangentColor, controlPointsColor));
                        rootLayer->addCurve(hermite32D);
                    }
                    break;
                case NodeType::Hermite5:
                    {
                        auto hermite5 = std::static_pointer_cast<Hermite5>(i->getCurve());
                        std::unique_ptr<Curve2D> hermite52D(new Hermite52D(
                                    hermite5, curveWidth, curveColor,
                                    tangentColor, secondDerivativeColor,
                                    controlPointsColor));
                        rootLayer->addCurve(hermite52D);
                    }
                    break;
                 case NodeType::Root:
                 default:
                    break;

            }
        }

        canvas->setRootLayer(std::move(rootLayer));
        w.setCanvas(canvas);
        w.render();
    }
    catch(std::exception& e) {

        Logger::Instance()->critical(e.what());
    }

    Logger::Instance()->info("Quitting...");

    return 0;
}
