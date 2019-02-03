/**
 * @file 2DHermite3.cpp
 * @brief Implements the 2D cubic Hermite curve
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2018-12-01
 */
#include <GL/glew.h>

#include "Hermite32D.h"

Hermite32D::Hermite32D(std::shared_ptr<Hermite3> curve,
                       Eigen::Vector3d curveColor, double curveWidth,
                       Eigen::Vector3d tangentColor,
                       Eigen::Vector3d controlPointsColor) :
    curve{curve}, Curve2D(curve, curveColor, curveWidth),
    tangentColor{tangentColor}, controlPointsColor{controlPointsColor} {

    Curve2D::recomputeVerticesAndIndices();

    this->startTangent.reset(
            new Arrow2D(this->curve->getStartControlPoint(),
                        this->curve->getStartTangentVector(),
                        this->curve->getStartTangentVector().norm(),
                        curveWidth, tangentColor));
    this->endTangent.reset(
            new Arrow2D(this->curve->getEndControlPoint(),
                        this->curve->getEndTangentVector(),
                        this->curve->getEndTangentVector().norm(),
                        curveWidth, tangentColor));
}

Hermite32D::~Hermite32D() {

    // TODO: Correctly destory buffers
}

void Hermite32D::render() {

    this->startTangent->render();
    this->endTangent->render();
    glUseProgram(Curve2D::shader->getProgramID());
    glBindVertexArray(Curve2D::vertexArrayObjectID);
    glDrawElements(GL_TRIANGLES, Curve2D::indices.size(), GL_UNSIGNED_INT, NULL);
}

bool Hermite32D::hasToBeRedrawn() { return Curve2D::isDirty; }
