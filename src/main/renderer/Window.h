/**
 * @file Window.h
 * @brief Describes an iphito Window
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-11-01
 */
#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <memory>
/* #include <GL/glew.h> */
#include <eigen3/Eigen/Core>
#include <GLFW/glfw3.h>

#include "Canvas.h"

struct DestroyGLFWWindow{
    void operator()(GLFWwindow* ptr){
         glfwDestroyWindow(ptr);
    }
};

typedef std::unique_ptr<GLFWwindow, DestroyGLFWWindow> smart_GLFWwindow;

class Window {

public:
    Window(int x, int y, std::string title);
    ~Window();

    void render();
    void setCanvas(std::unique_ptr<Canvas>& canvas);

private:
    void setMouseCallbacks();
    static void mouseButtonCallback(GLFWwindow* window, int button, int action,
                                    int modifiers);
    static void cursorPositionCallback(GLFWwindow* window, double xPosition,
                                       double yPosition);
    static void updateMousePosition(GLFWwindow* window);
    static void scrollButtonCallback(GLFWwindow* window, double xOffset,
                                     double yOffset);

    int x;
    int y;
    std::string title;
    std::unique_ptr<Canvas> canvas;
    //Curve Renderer
    // Camera
    smart_GLFWwindow window;

    inline static bool leftMouseButtonPressed = false;
    inline static bool mouseScrolling = false;
    inline static Eigen::Matrix3d mouseTransform = Eigen::Matrix3d::Identity();
    inline static Eigen::Vector2d mousePosition = Eigen::Vector2d::Zero();
};
#endif /* ifndef WINDOW_H */
