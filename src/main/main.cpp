#include <iostream>
#include <memory>
#include <stdexcept>
#include <eigen3/Eigen/Core>
#include <limits>

#include "Layer.h"
#include "Canvas.h"
#include "Window.h"

int main(int argc, char *argv[])
{
    
    Layer l1;
    Layer l2;
    Layer l3;

    std::cout << l1.getID() << std::endl;
    std::cout << l2.getID() << std::endl;
    std::cout << l3.getID() << std::endl;

    std::unique_ptr<Layer> l4(new Layer());
    std::unique_ptr<Layer> l5(new Layer());
    std::unique_ptr<Layer> l6(new Layer());

    std::cout << l4->getID() << std::endl;
    std::cout << l5->getID() << std::endl;
    std::cout << l6->getID() << std::endl;

    l4->addLayer(l5);

    if(l5) std::cout << l5.get() << std::endl;
    else std::cout << "null" << std::endl;

    Canvas c(12, 13);
    Window w(640, 480, "iphito", c);

    w.render();

    return 0;
}
