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

using namespace iphito::parser;
using namespace iphito::math;
using namespace iphito::renderer;
using namespace iphito::utils;

int main(int argc, char *argv[])
{

    int WIDTH = 640;
    int HEIGHT = 640;


    /* Eigen::Vector2d p1(0, 0); */
    /* Eigen::Vector2d t1(1, 2); */
    /* Eigen::Vector2d s1(-4, 0); */
    /* Eigen::Vector2d p2(0.25, 0); */
    /* Eigen::Vector2d t2(1, -2); */
    /* Eigen::Vector2d s2(4, 0); */
    /* std::unique_ptr<Hermite3> c1(new Hermite3(p1, t1, p2, t2)); */
    /* std::unique_ptr<Hermite5> h5(new Hermite5(p1, t1, s1, p2, t2, s2)); */

    Eigen::Vector3d curveColor(1.0, 0.0, 0.0);
    Eigen::Vector3d tangentColor(0.0, 0.0, 1.0);
    Eigen::Vector3d controlPointsColor(0.0, 1.0, 0.0);
    Eigen::Vector3d secondDerivativeColor(0.0, 1.0, 1.0);
    double curveWidth = 0.01;

    /* std::vector<Eigen::Vector2d> points = { Eigen::Vector2d(-0.5, 0), */
    /*                                         Eigen::Vector2d(-0.7, 0.6), */
    /*                                         Eigen::Vector2d(0.0, 0.9), */
    /*                                         Eigen::Vector2d(0.7, 0.6), */
    /*                                         Eigen::Vector2d(0.5, 0) */
    /*                                       }; */
    /* std::unique_ptr<Bezier> b1(new Bezier(points)); */

    std::string input = "";
    std::string currentInput = "";
    while (std::cin >> currentInput) {
        input += currentInput;
    }

    Parser parser(input);
    bool parsingSuccessfull = parser.parse();
    if (!parsingSuccessfull) {
        Logger::Instance()->critical("Error during parsing of input");
        return 1;
    }

    std::shared_ptr<ASTNode> rootNode = parser.getRootNode();

    try{
        Window w(WIDTH, HEIGHT, "iphito");
        std::unique_ptr<Canvas> canvas(new Canvas(WIDTH, HEIGHT));
        std::unique_ptr<Layer> rootLayer(new Layer());
        /* std::unique_ptr<Curve2D> c2D(new Hermite32D(std::move(c1), curveWidth, */
        /*             curveColor, tangentColor, controlPointsColor)); */
        /* std::unique_ptr<Curve2D> b2D(new Bezier2D(std::move(b1), curveWidth, */
        /*             curveColor, controlPointsColor, controlPointsColor)); */
        /* std::unique_ptr<Curve2D> h52D(new Hermite52D(std::move(h5), curveWidth, */
        /*             curveColor, tangentColor, secondDerivativeColor, */
        /*             controlPointsColor)); */
        /* rootLayer->addCurve(c2D); */
        /* rootLayer->addCurve(b2D); */
        /* rootLayer->addCurve(h52D); */
        Logger::Instance()->critical(std::to_string(rootNode->getChildren().size()));

        for (auto& i : rootNode->getChildren()) {
            if (i->getNodeType() == NodeType::Bezier) {
                auto bezier = std::static_pointer_cast<Bezier>(i->getCurve());
                std::unique_ptr<Curve2D> bezier2D(new Bezier2D(bezier,
                            curveWidth, curveColor, controlPointsColor,
                            controlPointsColor));
                rootLayer->addCurve(bezier2D);
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
