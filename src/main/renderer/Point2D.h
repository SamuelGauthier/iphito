/**
 * @file Point2D.h
 * @brief Describes a 2D point
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2018-12-29
 */
#ifndef POINT2D_H
#define POINT2D_H

#include <memory>
#include <random>
#include <vector>
#include <eigen3/Eigen/Core>
#include <GL/glew.h>

#include "Shader.h"

namespace iphito::renderer {

class Point2D {

public:
    Point2D() = delete;
    Point2D(Eigen::Vector2d center, Eigen::Vector3d color, double radius,
            double width = 0.0);
    ~Point2D();

    void render();
    bool hasToBeRedrawn();
    void updateModelMatrix(Eigen::Matrix4d model);
    void updateViewMatrix(Eigen::Matrix4d view);
    void updateProjectionMatrix(Eigen::Matrix4d projection);

private:
    Eigen::Vector3d center;
    Eigen::Vector3d color;
    double radius;
    double width;
    Eigen::Matrix4d model;
    Eigen::Matrix4d view;
    Eigen::Matrix4d projection;
    bool isDirty;
    
    std::unique_ptr<Shader> shader;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    GLuint vertexArrayObjectID;
    GLuint vertexBufferID;
    GLuint indexBufferID;
    std::vector<Eigen::Vector2d> samplePoints;

    static std::mt19937_64 engine;
    static std::uniform_real_distribution<double> distribution;

    void sampleCurve(double a, double b);
    bool isFlat(Eigen::Vector2d a, Eigen::Vector2d b, Eigen::Vector2d m);
    Eigen::Vector2d evaluateCircleAt(double t);
    void recomputeVerticesAndIndices();
};

} /* namespace iphito::renderer */

#endif /* ifndef POINT2D_H */
