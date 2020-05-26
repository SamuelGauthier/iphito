/**
 * @file Hermite32D.cpp
 * @brief Implements the 2D cubic Hermite curve
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2018-12-01
 */
#include <iostream>
#include <GL/glew.h>

#include "Hermite32D.h"
#include "utils/Logger.h"

namespace iphito::renderer {

using namespace iphito::math;

Hermite32D::Hermite32D(std::shared_ptr<Hermite3> curve, double curveWidth,
                       Eigen::Vector3d curveColor,
                       Eigen::Vector3d tangentColor,
                       Eigen::Vector3d controlPointsColor) :
    curve{curve}, Curve2D(curve, curveWidth, curveColor),
    tangentColor{tangentColor}, controlPointsColor{controlPointsColor} {

    Curve2D::recomputeVerticesAndIndices();

    Eigen::Vector2d startControlPoint = this->curve->getStartControlPoint();
    Eigen::Vector2d endControlPoint = this->curve->getEndControlPoint();
    Eigen::Vector2d startTangentVector = this->curve->getStartTangentVector();
    Eigen::Vector2d endTangentVector = this->curve->getEndTangentVector();

    this->startTangent.reset(
            new Arrow2D(startControlPoint, startTangentVector,
                        startTangentVector.norm(), curveWidth, tangentColor));
    this->endTangent.reset(
            new Arrow2D(endControlPoint, endTangentVector,
                        endTangentVector.norm(), curveWidth, tangentColor));

    this->startControlPoint.reset(new Point2D(startControlPoint,
                                              this->controlPointsColor,
                                              curveWidth));
    this->endControlPoint.reset(new Point2D(endControlPoint,
                                            this->controlPointsColor,
                                            curveWidth));
}

Hermite32D::~Hermite32D() {

    // TODO: Correctly destory buffers
}

void Hermite32D::render() {

    if (this->hasToBeRedrawn()) {
        Curve2D::recomputeVerticesAndIndices();
    }

    if (Curve2D::viewMatrixUpdate) {
        this->startTangent->updateViewMatrix(Curve2D::view);
        this->endTangent->updateViewMatrix(Curve2D::view);

        this->startControlPoint->updateViewMatrix(Curve2D::view);
        this->endControlPoint->updateViewMatrix(Curve2D::view);
        Curve2D::viewMatrixUpdate = false;
    }

    if (Curve2D::projectionMatrixUpdate) {
        this->startTangent->updateProjectionMatrix(Curve2D::projection);
        this->endTangent->updateProjectionMatrix(Curve2D::projection);

        this->startControlPoint->updateProjectionMatrix(Curve2D::projection);
        this->endControlPoint->updateProjectionMatrix(Curve2D::projection);
        Curve2D::projectionMatrixUpdate = false;
    }

    this->startTangent->render();
    this->endTangent->render();

    Curve2D::shader->useProgram();
    Curve2D::shader->setMatrix4("model", Curve2D::model);
    Curve2D::shader->setMatrix4("view", Curve2D::view);
    Curve2D::shader->setMatrix4("projection", Curve2D::projection);

    glBindVertexArray(Curve2D::vertexArrayObjectID);
    glDrawElements(GL_TRIANGLES, Curve2D::indices.size(), GL_UNSIGNED_INT,
                   NULL);
    glBindVertexArray(0);

    this->startControlPoint->render();
    this->endControlPoint->render();
}

bool Hermite32D::hasToBeRedrawn() { return Curve2D::isDirty; }

} /* namespace iphito::renderer */

