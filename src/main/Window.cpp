/**
 * @file Window.cpp
 * @brief iphito Window implementation
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-11-01
 */
#include <iostream>
#include <stdexcept>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"

#include "Logger.h"

Window::Window(int x, int y, std::string title, Canvas canvas) :
    x{x}, y{y}, title{title}, canvas{canvas} {
    
    if(!glfwInit()) throw std::runtime_error("Could not initialize GLFW.");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window.reset(glfwCreateWindow(this->x, this->y, this->title.c_str(),
                                        NULL, NULL));

    if(!this->window.get()) {
        glfwTerminate();
        throw std::runtime_error("Could not create GLFW window.");
    }

    glfwMakeContextCurrent(this->window.get());

    GLenum status = glewInit();
    if(status != GLEW_OK) {
        glfwTerminate();

        std::stringstream errorMessage;
        errorMessage << "Could not intialize GLEW. Error: ";
        errorMessage << glewGetErrorString(status);

        throw std::runtime_error(errorMessage.str());
    }

    std::stringstream openGLVersion;
    openGLVersion << "OpenGL Version: ";
    openGLVersion << glGetString(GL_VERSION);
    Logger::Instance()->debug(openGLVersion.str());


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
