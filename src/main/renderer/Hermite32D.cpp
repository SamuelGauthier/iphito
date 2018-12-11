/**
 * @file 2DHermite3.cpp
 * @brief Implements the 2D cubic Hermite curve
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2018-12-01
 */
#include <GL/glew.h>

#include "Hermite32D.h"

Hermite32D::Hermite32D(std::unique_ptr<Hermite3> curve,
                       Eigen::Vector3d curveColor, double curveWidth,
                       Eigen::Vector3d tangentColor,
                       Eigen::Vector3d controlPointsColor) :
    Curve2D(std::unique_ptr<Curve>(std::move(curve)), curveColor, curveWidth),
    tangentColor{tangentColor}, controlPointsColor{controlPointsColor} {

        Curve2D::recomputeVerticesAndIndices();
}

Hermite32D::~Hermite32D() {

}

void Hermite32D::render() {

    glBindVertexArray(Curve2D::vertexArrayObjectID);
    glDrawElements(GL_TRIANGLES, Curve2D::indices.size(), GL_UNSIGNED_INT, NULL);
}

bool Hermite32D::hasToBeRedrawn() { return Curve2D::isDirty; }
