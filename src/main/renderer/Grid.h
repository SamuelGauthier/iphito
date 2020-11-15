
#ifndef GRID_H
#define GRID_H

#include <memory>
#include <vector>
#include <eigen3/Eigen/Core>
#include <GL/glew.h>

#include "AABB.h"
#include "Shader.h"

namespace iphito::renderer {

class Grid {

public:
    Grid(const Eigen::Vector3d& color);
    /* ~Grid(); */
    
    void render();
    void updateModelMatrix(const Eigen::Matrix4d& model);
    void updateViewMatrix(const Eigen::Matrix4d& view);
    void updateProjectionMatrix(const Eigen::Matrix4d& projection);
    void setViewAABB(const AABB& aabb);

private:
    Eigen::Vector3d color;
    Eigen::Matrix4d model;
    Eigen::Matrix4d view;
    Eigen::Matrix4d projection;

    AABB viewAabb;

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    std::unique_ptr<Shader> shader;
    GLuint vertexArrayObjectID;
    GLuint vertexBufferID;
    GLuint indexBufferID;

    void recomputeGrid();
};
} /* namespace iphito::renderer */

#endif /* ifndef GRID_H */
