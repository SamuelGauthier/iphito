/**
 * @file Arrow2D.h
 * @brief Describes a 2d arrow
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2018-12-26
 */
#ifndef ARROW_H
#define ARROW_H

#include <memory>
#include <vector>
#include <eigen3/Eigen/Core>
#include <GL/glew.h>

#include "Shader.h"

class Arrow2D {

public:
    Arrow2D(Eigen::Vector2d position, Eigen::Vector2d direction, double length,
            double width, Eigen::Vector3d color);
    ~Arrow2D();
    
    void render();

private:
    Eigen::Vector2d position;
    Eigen::Vector2d direction;
    double length;
    double width;
    Eigen::Vector3d color;

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    std::unique_ptr<Shader> shader;
    GLuint vertexArrayObjectID;
    GLuint vertexBufferID;
    GLuint indexBufferID;
    
    void recomputeVerticesAndIndices();
};

#endif /* ifndef ARROW_H */