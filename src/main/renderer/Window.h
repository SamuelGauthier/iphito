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
#include <eigen3/Eigen/Core>
#include <GLFW/glfw3.h>

#include "Canvas.h"
#include "Arrow2D.h"
#include "Axes2D.h"

namespace iphito::renderer {

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
    static void updateWindowSizeCallback(GLFWwindow* window, int width,
                                         int height);
    void updateViewMatrix();
    void updateProjectionMatrix();
    void initializeAxes();

    int x;
    int y;
    std::string title;
    std::unique_ptr<Canvas> canvas;
    smart_GLFWwindow window;
    Eigen::Matrix4d projection;
    Eigen::Matrix4d view;
    std::unique_ptr<Axes2D> axes;

    inline static bool leftMouseButtonPressed = false;
    inline static bool mouseScrolling = false;
    inline static bool windowResizing = false;
    inline static Eigen::Vector2d mousePosition = Eigen::Vector2d::Zero();

    inline static Eigen::Vector3d cameraPosition = Eigen::Vector3d(0, 0, 1);
    inline static Eigen::Vector3d cameraTarget = Eigen::Vector3d(0, 0, 0);
    inline static Eigen::Vector3d cameraUp = Eigen::Vector3d(0, 1, 0);

    inline static int currentWindowWidth = 1;
    inline static int currentWindowHeight = 1;
    inline static double initialWindowWidth = 1;
    inline static double initialWindowHeight = 1;
    inline static double zoomFactor = 1.0;

};

} /* namespace iphito::renderer */

#endif /* ifndef WINDOW_H */
