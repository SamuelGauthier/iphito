/**
 * @file Window.cpp
 * @brief iphito Window implementation
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-11-01
 */
#include <iostream>
#include <stdexcept>
#include <Eigen/Dense>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"

#include "Camera.h"
#include "src/main/utils/Logger.h"
#include "src/main/utils/Utils.h"

namespace iphito::renderer {

using namespace iphito::utils;

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
    glfwSetWindowSizeCallback(this->window.get(),
                              this->updateWindowSizeCallback);

    Window::currentWindowWidth = this->x;
    Window::currentWindowHeight = this->y;
    Window::initialWindowWidth = this->x;
    Window::initialWindowHeight = this->y;

    /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    updateViewMatrix();
    updateProjectionMatrix();

    initializeAxes();
    initializeGrid();
    updateGridAABB();
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

        if(Window::mouseScrolling || Window::windowResizing)
        {
            this->updateProjectionMatrix();
            this->updateGridAABB();
            this->grid->updateProjectionMatrix(Window::projection);
            this->axes->updateProjectionMatrix(Window::projection);
            this->canvas->updateProjectionMatrix(Window::projection);
            Window::mouseScrolling = false;
            Window::windowResizing = false;
        }
        if (Window::leftMouseButtonPressed) {
            this->updateViewMatrix();
            this->updateGridAABB();
            this->grid->updateViewMatrix(Window::view);
            this->axes->updateViewMatrix(Window::view);
            this->canvas->updateViewMatrix(Window::view);
            /* Window::windowResizing = false; */
        }

        this->grid->render();
        this->axes->render();
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
    // TODO: This is ugly doing it here but we cannot do it in the constructor
    // because the canvas pointer is not set yet
    this->canvas->updateViewMatrix(Window::view);
    this->canvas->updateProjectionMatrix(Window::projection);
}

void Window::setMouseCallbacks() {
    glfwSetMouseButtonCallback(this->window.get(), this->mouseButtonCallback);
    glfwSetCursorPosCallback(this->window.get(), this->cursorPositionCallback);
    glfwSetScrollCallback(this->window.get(), this->scrollButtonCallback);
}

void Window::mouseButtonCallback(GLFWwindow* window, int button, int action,
                                 int modifiers) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {

        if (action == GLFW_PRESS) {
            Window::leftMouseButtonPressed = true;
            Window::updateMousePosition(window);
        }

        else if (action == GLFW_RELEASE) {
            Window::leftMouseButtonPressed = false;
        }
    }
}

void Window::cursorPositionCallback(GLFWwindow* window, double xPosition,
                                    double yPosition) {
    if(Window::leftMouseButtonPressed) {
        Eigen::Vector2d previousMousePosition = Window::mousePosition;
        Window::updateMousePosition(window);
        Eigen::Vector2d translationVector = Window::mousePosition -
                                            previousMousePosition;
        translationVector *= Window::scale;

        Eigen::Vector4d cameraTranslationScreen(translationVector(0),
                                                translationVector(1), 1, 0);

        Eigen::Vector4d cameraTranslationWorld = Window::viewInverse *
                                                 Window::projectionInverse *
                                                 cameraTranslationScreen;

        Eigen::Vector3d cameraTranslation(cameraTranslationWorld(0),
                                          cameraTranslationWorld(1), 0);

        Window::cameraPosition += cameraTranslation;
        Window::cameraTarget += cameraTranslation;
    }
}

void Window::updateMousePosition(GLFWwindow* window) {

    double xPosition = 0.0;
    double yPosition = 0.0;
    glfwGetCursorPos(window, &xPosition, &yPosition);

    int windowWidth = 0;
    int windowHeight = 0;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    double wRatio = Window::currentWindowWidth / Window::initialWindowWidth;
    double hRatio = Window::currentWindowHeight / Window::initialWindowHeight;
    wRatio *= Window::zoomFactor;
    hRatio *= Window::zoomFactor;
    xPosition = (xPosition / windowWidth) - wRatio;
    yPosition = (yPosition / windowHeight) - hRatio;
    xPosition *= -1;

    Window::mousePosition << xPosition, yPosition;
}

void Window::scrollButtonCallback(GLFWwindow* window, double xOffset,
                                  double yOffset) {

    if (Window::zoomFactor + yOffset < 0.1) {
        return;
    }

    Window::zoomFactor += yOffset;
    Window::mouseScrolling = true;
}

void Window::updateWindowSizeCallback(GLFWwindow* window, int width,
                                      int height) {

    int oldWidth = Window::currentWindowWidth;
    int oldHeight = Window::currentWindowHeight;

    int newWidth = width;
    int newHeight = height;
    glViewport(0, 0, newWidth, newHeight);

    Window::currentWindowWidth = newWidth;
    Window::currentWindowHeight = newHeight;

    Window::windowResizing = true;
}

void Window::initializeAxes() {

    Eigen::Vector3d white(1.0, 1.0, 1.0);
    Eigen::Vector2d xDir(1.0, 0.0);
    Eigen::Vector2d yDir(0.0, 1.0);
    double axisLength = 1.0;
    double axisWidth = 0.01;

    this->axes.reset(new Axes2D(Eigen::Vector2d::Zero(), xDir, yDir, white,
                                axisLength, axisWidth));
    this->axes->updateViewMatrix(Window::view);
    this->axes->updateProjectionMatrix(Window::projection);
}

void Window::initializeGrid() {

    Eigen::Vector3d white(0.4, 0.4, 0.4);

    this->grid.reset(new Grid(white));
    this->grid->updateViewMatrix(Window::view);
    this->grid->updateProjectionMatrix(Window::projection);
}

void Window::updateGridAABB() {
    double wRatio = Window::currentWindowWidth / Window::initialWindowWidth;
    double hRatio = Window::currentWindowHeight / Window::initialWindowHeight;
    wRatio *= Window::scale * Window::zoomFactor;
    hRatio *= Window::scale * Window::zoomFactor;

    Eigen::Vector2d min;
    Eigen::Vector2d max;

    min[0] = Window::cameraTarget[0] - wRatio;
    min[1] = Window::cameraTarget[1] - hRatio;
    max[0] = Window::cameraTarget[0] + wRatio;
    max[1] = Window::cameraTarget[1] + hRatio;

    this->grid->setViewAABB(AABB(min, max));
}

void Window::updateViewMatrix() {

    Window::view = Camera::lookAt(Window::cameraPosition, Window::cameraTarget,
                                Window::cameraUp);
    Window::viewInverse = Window::view.inverse();
}

void Window::updateProjectionMatrix() {

    double wRatio = Window::currentWindowWidth / Window::initialWindowWidth;
    double hRatio = Window::currentWindowHeight / Window::initialWindowHeight;
    wRatio *= Window::zoomFactor;
    hRatio *= Window::zoomFactor;
    Window::projection = Camera::orthographic(-Window::scale * wRatio,
                                              Window::scale * wRatio,
                                              -Window::scale * hRatio,
                                              Window::scale * hRatio,
                                              0.1, 100);
    Window::projectionInverse = Window::projection.inverse();
}

} /* namespace iphito::renderer */
