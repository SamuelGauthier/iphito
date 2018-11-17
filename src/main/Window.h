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
    Window(int x, int y, std::string title, Canvas canvas);
    ~Window();

    void render();

private:

    int x;
    int y;
    std::string title;
    Canvas canvas;
    //Curve Renderer
    // Camera
    smart_GLFWwindow window;
};
#endif /* ifndef WINDOW_H */
