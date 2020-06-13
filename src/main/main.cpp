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
#include "renderer/Curve2DFactory.h"
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

void renderCurves() {
    int WIDTH = 640;
    int HEIGHT = 640;

    std::string input = Utils::readInput();

    Parser parser(input);
    while (parser.parse()) {}

    try{
        Window w(WIDTH, HEIGHT, "iphito");
        std::unique_ptr<Canvas> canvas(new Canvas(WIDTH, HEIGHT));

        std::shared_ptr<ASTNode> rootNode = parser.getRootNode();
        Curve2DFactory curve2DFactory(rootNode);

        Eigen::Vector3d curveColor(1.0, 0.0, 0.0);
        Eigen::Vector3d tangentColor(0.0, 0.0, 1.0);
        Eigen::Vector3d controlPointsColor(0.0, 1.0, 0.0);
        Eigen::Vector3d secondDerivativeColor(0.0, 1.0, 1.0);
        double curveWidth = 0.01;

        curve2DFactory.setCurveColor(curveColor);
        curve2DFactory.setTangentColor(tangentColor);
        curve2DFactory.setControlPointsColor(controlPointsColor);
        curve2DFactory.setSecondDerivativeColor(secondDerivativeColor);
        curve2DFactory.setCurveWidth(curveWidth);

        std::unique_ptr<Layer> rootLayer = curve2DFactory.getRootLayer();

        canvas->setRootLayer(std::move(rootLayer));
        w.setCanvas(canvas);
        w.render();
    }
    catch(std::exception& e) {

        Logger::Instance()->critical(e.what());
    }

    Logger::Instance()->info("Quitting...");
}

void printUsage() {

    std::cout << "iphito" << std::endl;
    std::cout << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "  iphito <curve definition>" << std::endl;
    std::cout << "  iphito (-e|--export) <input file name>" << std::endl;
    std::cout << "  iphito -v | --version" << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -e --export\tExport iphito file to postscript." << std::endl;
    std::cout << "  -v --version\tShow version." << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        renderCurves();
    }
    else if (argc == 2) {
        std::string version(argv[1]);

        if (version == "-v" || version == "--version") {
            std::cout << "1.0.0" << std::endl;
        }
        else {
            printUsage();
        }
    }
    else if (argc == 3) {
        std::string exportFlag(argv[1]);
        std::string inputFileName(argv[2]);

        if (exportFlag == "-e" || exportFlag == "--export") {
            // TODO
        }
        else {
            printUsage();
        }
    }
    else {
        printUsage();
    }


    return 0;
}
