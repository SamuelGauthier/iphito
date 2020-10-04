/**
 * @file Arrow2D.h
 * @brief Describes a 2d arrow
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2018-12-26
 */
#ifndef ARROW2D_H
#define ARROW2D_H

#include <memory>
#include <vector>
#include <eigen3/Eigen/Core>
#include <GL/glew.h>

#include "Shader.h"

namespace iphito::renderer {

class Arrow2D {

public:
    Arrow2D(const Eigen::Vector2d& position, const Eigen::Vector2d& direction,
            double length, double width, const Eigen::Vector3d& color);
    ~Arrow2D();
    
    void render();
    void updateModelMatrix(const Eigen::Matrix4d& model);
    void updateViewMatrix(const Eigen::Matrix4d& view);
    void updateProjectionMatrix(const Eigen::Matrix4d& projection);

private:
    Eigen::Vector2d position;
    Eigen::Vector2d direction;
    double length;
    double width;
    Eigen::Vector3d color;
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

} /* namespace iphito::renderer */

#endif /* ifndef ARROW2D_H */
