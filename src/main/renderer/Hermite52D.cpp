/**
 * @file Hermite52D.cpp
 * @brief Implements the 2D quintic Hermite curve
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2019-03-16
 */
#include <GL/glew.h>

#include "Hermite52D.h"
#include "src/main/utils/Logger.h"

namespace iphito::renderer {

using namespace iphito::math;

Hermite52D::Hermite52D(std::shared_ptr<Hermite5> curve,
                       double curveWidth, const Eigen::Vector3d& curveColor,
                       const Eigen::Vector3d& tangentColor,
                       const Eigen::Vector3d& secondDerivativeColor,
                       const Eigen::Vector3d& controlPointsColor) :
    curve{curve}, Curve2D(curve, curveWidth, curveColor),
    tangentColor{tangentColor}, secondDerivativeColor{secondDerivativeColor},
    controlPointsColor{controlPointsColor} {

    Curve2D::recomputeVerticesAndIndices();

    Eigen::Vector2d startControlPoint = this->curve->getStartControlPoint();
    Eigen::Vector2d endControlPoint = this->curve->getEndControlPoint();
    Eigen::Vector2d startVelocityVector = this->curve->getStartVelocityVector();
    Eigen::Vector2d endVelocityVector = this->curve->getEndVelocityVector();
    Eigen::Vector2d startAccelerationVector =
        this->curve->getStartAccelerationVector();
    Eigen::Vector2d endAccelerationVector =
        this->curve->getEndAccelerationVector();

    this->startTangent.reset(new Arrow2D(startControlPoint, startVelocityVector,
                                         startVelocityVector.norm(), curveWidth,
                                         tangentColor));
    this->endTangent.reset(new Arrow2D(endControlPoint, endVelocityVector,
                                       endVelocityVector.norm(), curveWidth,
                                       tangentColor));

    this->startSecondDerivative.reset(
            new Arrow2D(startControlPoint, startAccelerationVector,
                        startAccelerationVector.norm(), curveWidth,
                        secondDerivativeColor));

    this->endSecondDerivative.reset(
            new Arrow2D(endControlPoint, endAccelerationVector,
                        endAccelerationVector.norm(), curveWidth,
                        secondDerivativeColor));

    this->startControlPoint.reset(new Point2D(startControlPoint,
                this->controlPointsColor, curveWidth));
    this->endControlPoint.reset(new Point2D(endControlPoint,
                this->controlPointsColor, curveWidth));
}

Hermite52D::~Hermite52D() {
    // TODO: properly destroy everything if needed
}

void Hermite52D::render() {

    if (this->hasToBeRedrawn()) {
        Curve2D::recomputeVerticesAndIndices();
    }

    if (Curve2D::viewMatrixUpdate) {
        this->startTangent->updateViewMatrix(Curve2D::view);
        this->endTangent->updateViewMatrix(Curve2D::view);
        this->startSecondDerivative->updateViewMatrix(Curve2D::view);
        this->endSecondDerivative->updateViewMatrix(Curve2D::view);

        this->startControlPoint->updateViewMatrix(Curve2D::view);
        this->endControlPoint->updateViewMatrix(Curve2D::view);
        Curve2D::viewMatrixUpdate = false;
    }

    if (Curve2D::projectionMatrixUpdate) {
        this->startTangent->updateProjectionMatrix(Curve2D::projection);
        this->endTangent->updateProjectionMatrix(Curve2D::projection);
        this->startSecondDerivative->updateProjectionMatrix(Curve2D::projection);
        this->endSecondDerivative->updateProjectionMatrix(Curve2D::projection);

        this->startControlPoint->updateProjectionMatrix(Curve2D::projection);
        this->endControlPoint->updateProjectionMatrix(Curve2D::projection);
        Curve2D::projectionMatrixUpdate = false;
    }

    this->startTangent->render();
    this->endTangent->render();
    this->startSecondDerivative->render();
    this->endSecondDerivative->render();

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

bool Hermite52D::hasToBeRedrawn() { return Curve2D::isDirty; }

} /* namespace iphito::renderer */
