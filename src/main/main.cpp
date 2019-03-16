#include <iostream>
#include <memory>
#include <stdexcept>
#include <eigen3/Eigen/Core>
#include <limits>
#include <map>

#include "math/Bezier.h"
#include "math/Hermite3.h"
#include "renderer/Bezier2D.h"
#include "renderer/Canvas.h"
#include "renderer/Curve2D.h"
#include "renderer/Hermite32D.h"
#include "renderer/Layer.h"
#include "renderer/Shader.h"
#include "renderer/Window.h"
#include "utils/Logger.h"

int main(int argc, char *argv[])
{

    int WIDTH = 640;
    int HEIGHT = 640;


    std::unique_ptr<Layer> rootLayer(new Layer());
    Eigen::Vector2d p1(0, 0);
    Eigen::Vector2d t1(1, 2);
    Eigen::Vector2d p2(0.25, 0);
    Eigen::Vector2d t2(1, -2);
    std::unique_ptr<Hermite3> c1(new Hermite3(p1, t1, p2, t2));

    Eigen::Vector3d curveColor(1.0, 0.0, 0.0);
    Eigen::Vector3d tangentColor(0.0, 0.0, 1.0);
    Eigen::Vector3d controlPointsColor(0.0, 1.0, 0.0);
    double curveWidth = 0.01;

    std::vector<Eigen::Vector2d> points = { Eigen::Vector2d(-0.5, 0),
                                            Eigen::Vector2d(-0.7, 0.6),
                                            Eigen::Vector2d(0.0, 0.9),
                                            Eigen::Vector2d(0.7, 0.6),
                                            Eigen::Vector2d(0.5, 0)
                                          };
    std::unique_ptr<Bezier> b1(new Bezier(points));

    try{
        Window w(WIDTH, HEIGHT, "iphito");
        std::unique_ptr<Canvas> c(new Canvas(WIDTH, HEIGHT));
        std::unique_ptr<Curve2D> c2D(new Hermite32D(std::move(c1), curveColor,
                    curveWidth, tangentColor, controlPointsColor));
        std::unique_ptr<Curve2D> b2D(new Bezier2D(std::move(b1), curveColor,
                                     curveWidth, controlPointsColor,
                                     controlPointsColor));
        rootLayer->addCurve(c2D);
        rootLayer->addCurve(b2D);
        c->setRootLayer(std::move(rootLayer));
        w.setCanvas(c);
        w.render();
    }
    catch(std::exception& e) {

        /* std::cout << e.what() << std::endl; */
        Logger::Instance()->critical(e.what());
    }

    Logger::Instance()->info("test");

    return 0;
}
