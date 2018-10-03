#include <iostream>
#include <memory>
#include <eigen3/Eigen/Core>

#include "Layer.h"


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


    std::cout << "================matrix tests===================" << std::endl;
    Eigen::Matrix4Xd m(4, 2);
    m << 1, 2, 3, 4, 5, 6, 7, 8;
    std::cout << m << std::endl;

    Eigen::Vector2d t(4, 4);

    std::cout << t << std::endl;
    //std::cout << m*t << std::endl;

    Eigen::Vector4d res = m*t;

    std::cout << res << std::endl;


    Eigen::Vector2d a(1, 2);
    Eigen::Vector2d b(3, 4);
    Eigen::Matrix2d c;
    c << a, b;

    std::cout << c << std::endl;

    return 0;
}
