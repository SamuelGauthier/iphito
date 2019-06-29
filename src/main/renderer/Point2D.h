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

class Point2D {

public:
    Point2D() = delete;
    Point2D(Eigen::Vector2d center, Eigen::Vector3d color, double radius,
            double width = 0.0);
    ~Point2D();

    void render();
    void updateTransform(Eigen::Matrix3d& transform);
    bool hasToBeRedrawn();
    

private:
    Eigen::Vector2d center;
    Eigen::Vector3d color;
    double radius;
    double width;
    Eigen::Matrix3d transform;
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

#endif /* ifndef POINT2D_H */
