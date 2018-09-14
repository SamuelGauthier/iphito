#include <iostream>
#include "Layer.h"

int main(int argc, char *argv[])
{
    
    Layer l1;
    Layer l2;
    Layer l3;

    std::cout << l1.getID() << std::endl;
    std::cout << l2.getID() << std::endl;
    std::cout << l3.getID() << std::endl;

    return 0;
}
