/**
 * @file Line2D.h
 * @brief Describes a 2d line
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2019-02-23
 */
#ifndef LINE2D_H
#define LINE2D_H

#include <memory>
#include <vector>
#include <eigen3/Eigen/Core>
#include <GL/glew.h>

#include "Shader.h"

class Line2D {

public:
    Line2D() = delete;
    Line2D(Eigen::Vector2d startPoint, Eigen::Vector2d endPoint, double width,
           Eigen::Vector3d color);
    ~Line2D();
    
    void render();
    void updateModelMatrix(Eigen::Matrix4d model);
    void updateViewMatrix(Eigen::Matrix4d view);
    void updateProjectionMatrix(Eigen::Matrix4d projection);

private:
    Eigen::Vector2d startPoint;
    Eigen::Vector2d endPoint;
    double width;
    Eigen::Vector3d color;
    Eigen::Matrix3d transform;
    Eigen::Matrix4d model;
    Eigen::Matrix4d view;
    Eigen::Matrix4d projection;

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    std::unique_ptr<Shader> shader;
    GLuint vertexArrayObjectID;
    GLuint vertexBufferID;
    GLuint indexBufferID;

    void recomputeVerticesAndIndices();
};

#endif /* ifndef LINE2D_H */
