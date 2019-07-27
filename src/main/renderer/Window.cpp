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

#include "utils/Logger.h"
#include "utils/Utils.h"


Window::Window(int x, int y, std::string title) :
    x{x}, y{y}, title{title}, canvas{nullptr} {
    
    if(!glfwInit()) throw std::runtime_error("Could not initialize GLFW.");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

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

    Utils::setGlfwInitialized();
    Utils::setGlewInitialized();

    this->setMouseCallbacks();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

Window::~Window() {
    glfwTerminate();
}

void Window::render() {

    /* Make the window's context current */
    glfwMakeContextCurrent(this->window.get());

    if(!this->canvas)
        throw new std::runtime_error("No canvas set.");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(this->window.get()))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        if(Window::leftMouseButtonPressed || Window::mouseScrolling)
        {
            this->canvas->updateTransform(Window::mouseTransform);
            Window::mouseScrolling = false;
        }

        this->canvas->render();

        /* Swap front and back buffers */
        glfwSwapBuffers(this->window.get());

        /* Poll for and process events */
        /* glfwPollEvents(); */
        glfwWaitEvents();
    }
}

void Window::setCanvas(std::unique_ptr<Canvas>& canvas) {
    this->canvas = std::move(canvas);
}

void Window::setMouseCallbacks() {
    glfwSetMouseButtonCallback(this->window.get(), this->mouseButtonCallback);
    glfwSetCursorPosCallback(this->window.get(), this->cursorPositionCallback);
    glfwSetScrollCallback(this->window.get(), this->scrollButtonCallback);
}

void Window::mouseButtonCallback(GLFWwindow* window, int button, int action,
                                 int modifiers) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
    /* if (button == GLFW_MOUSE_BUTTON_MIDDLE) { */

        if (action == GLFW_PRESS) {
            Logger::Instance()->debug("[Window] Start pressing left mouse button");
            Window::leftMouseButtonPressed = true;
            Window::updateMousePosition(window);
        }

        else if (action == GLFW_RELEASE) {
            Logger::Instance()->debug("[Window] Left mouse button released");
            Window::leftMouseButtonPressed = false;
        }

    }
}

void Window::cursorPositionCallback(GLFWwindow* window, double xPosition,
                                    double yPosition) {
    if(Window::leftMouseButtonPressed) {
        Logger::Instance()->debug("[Window] Panning...");

        Eigen::Vector2d previousMousePosition = Window::mousePosition;
        Window::updateMousePosition(window);
        Eigen::Vector2d translationVector = Window::mousePosition -
                                            previousMousePosition;
        translationVector *= -1;
        // update transform
        Window::mouseTransform(0, 2) = translationVector[0];
        Window::mouseTransform(1, 2) = translationVector[1];

        // avoid updating scaling
        Window::mouseTransform(0, 0) = 0;
        Window::mouseTransform(1, 1) = 0;
    }
}

void Window::updateMousePosition(GLFWwindow* window) {

    double xPosition = 0.0;
    double yPosition = 0.0;
    glfwGetCursorPos(window, &xPosition, &yPosition);

    int windowHeight = 0;
    int windowWidth = 0;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    xPosition = (xPosition / windowWidth) - 0.5;
    yPosition = (yPosition / windowWidth) - 0.5;
    xPosition *= -1;

    Window::mousePosition << xPosition, yPosition;
}

void Window::scrollButtonCallback(GLFWwindow* window, double xOffset,
                                  double yOffset) {
    std::string scrollAmount = std::to_string(yOffset);
    Logger::Instance()->debug("[Window] Scrolling..." + scrollAmount);

    // update scale
    Window::mouseTransform(0, 0) = yOffset;
    Window::mouseTransform(1, 1) = yOffset;

    // avoid updating panning
    Window::mouseTransform(0, 2) = 0;
    Window::mouseTransform(1, 2) = 0;

    Window::mouseScrolling = true;
}
