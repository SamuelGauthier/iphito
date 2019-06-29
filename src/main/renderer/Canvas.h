/**
 * @file Canvas.h
 * @brief Describes the Canvas responsible for holding all the layers and
 * curves.
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-09-14
 */
#ifndef CANVAS_H
#define CANVAS_H

#include <eigen3/Eigen/Core>
#include <GL/glew.h>

#include "Layer.h"

class Canvas {

public:
    Canvas(unsigned int width, unsigned int height);
    ~Canvas();

    unsigned int getWidth();
    unsigned int getHeight();

    void setRootLayer(std::shared_ptr<Layer> rootLayer);
    void render();
    /* void updateMousePosition(double x, double y); */
    void updateTransform(Eigen::Matrix3d transform);
    

private:
    unsigned int width; 
    unsigned int height; 
    std::shared_ptr<Layer> rootLayer; // shared or unique?
    GLuint vertexArrayObjectID;
    Eigen::Matrix3d transform;
};

#endif /* ifndef CANVAS_H */
