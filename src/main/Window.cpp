/**
 * @file Window.cpp
 * @brief iphito Window implementation
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-11-01
 */
#include <stdexcept>

#include "Window.h"

Window::Window(int x, int y, std::string title, Canvas canvas) :
    x{x}, y{y}, title{title}, canvas{canvas} {
    
    if(!glfwInit())
        throw std::runtime_error("Could not initialize GLFW.");

    this->window.reset(glfwCreateWindow(this->x, this->y, this->title.c_str(),
                                        NULL, NULL));

    if(!this->window.get()) {
        glfwTerminate();
        throw std::runtime_error("Could not create GLFW window.");
    }
}

Window::~Window() {
    glfwTerminate();
}

void Window::render() {

    /* Make the window's context current */
    glfwMakeContextCurrent(this->window.get());

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(this->window.get()))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(this->window.get());

        /* Poll for and process events */
        glfwPollEvents();
    }
}
