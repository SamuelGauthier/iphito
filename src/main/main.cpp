#include <iostream>
#include <memory>
#include <stdexcept>
#include <eigen3/Eigen/Core>
#include <limits>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Layer.h"

struct DestroyGLFWWindow{

    void operator()(GLFWwindow* ptr){
         glfwDestroyWindow(ptr);
    }

};

typedef std::unique_ptr<GLFWwindow, DestroyGLFWWindow> smart_GLFWwindow;

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

    if(!glfwInit())
        throw std::runtime_error("Could not initialize GLFW.");

    smart_GLFWwindow window(glfwCreateWindow(640, 480, "iphito", NULL, NULL));
    
    if(!window) {
        glfwTerminate();
        throw std::runtime_error("Could not create GLFW window.");
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window.get());

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window.get()))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window.get());

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
