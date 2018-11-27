#include <iostream>
#include <memory>
#include <stdexcept>
#include <eigen3/Eigen/Core>
#include <limits>
#include <map>

#include "Layer.h"
#include "Canvas.h"
#include "Window.h"
#include "Hermite3.h"
#include "Logger.h"
#include "Shader.h"

int main(int argc, char *argv[])
{

    int WIDTH = 640;
    int HEIGHT = 480;


    std::unique_ptr<Layer> rootLayer(new Layer());
    Eigen::Vector2d p1(0, 0);
    Eigen::Vector2d t1(1, 0);
    Eigen::Vector2d p2(1, 0);
    Eigen::Vector2d t2(1, 0);
    std::unique_ptr<Curve> c1(new Hermite3(p1, t1, p2, t2));
    rootLayer->addCurve(c1);

    Canvas c(WIDTH, HEIGHT);
    c.setRootLayer(std::move(rootLayer));

    try{
        Window w(WIDTH, HEIGHT, "iphito", c);
        Shader t = Shader("../src/shaders/basic.vert", "../src/shaders/basic.frag");
        w.render();
    }
    catch(std::exception& e) {

        /* std::cout << e.what() << std::endl; */
        Logger::Instance()->critical(e.what());
    }

    Logger::Instance()->info("test");

    return 0;
}
