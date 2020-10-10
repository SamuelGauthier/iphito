#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <stdexcept>
#include <eigen3/Eigen/Core>
#include <docopt/docopt.h>

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

static constexpr auto USAGE =
R"(
Usage:
    iphito show <curve_definition>
    iphito (-f | --file ) <curve_definition_file_path>
    iphito (-e | --export) <curve_definition>
    iphito (-v | --version)
    iphito (-h | --help)
Options:
    -f --file       Use file with curve definition
    -e --export     Export curves in ps format.
    -v --version    Show version.
    -h --help       Show this screen.
)";

void renderCurves(const std::string& curves) {
    int WIDTH = 640;
    int HEIGHT = 640;

    std::string input = curves;// Utils::readInput();

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

int main(int argc, char *argv[])
{
    std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
            { std::next(argv), std::next(argv, argc) },
            true,
            "1.0.0");

    if (args["show"].asBool()) {
        auto curve = args["<curve_definition>"].asString();
        renderCurves(curve);
    }
    else if (args["--file"].asBool()) {
        // TODO: requirements macOS >= 10.15
        /* std::filesystem::path filePath = */
        /*     args["<curve_definition_file_path>"].asString(); */
        /* if (std::filesystem::exists(filePath)) { */
            auto fileName = args["<curve_definition_file_path>"].asString();
            std::ifstream inputStream(fileName);
            std::string fileContent(std::istreambuf_iterator<char>{inputStream}, {});
            renderCurves(fileContent);
        /* } */
        /* else { */
        /*     Logger::Instance()->critical("input file does not exist!"); */
        /* } */
    }

    return 0;
}
