/**
 * @file Hermite52D.cpp
 * @brief Implements the 2D quintic Hermite curve
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2019-03-16
 */
#include <GL/glew.h>

#include "Hermite52D.h"

Hermite52D::Hermite52D(std::shared_ptr<Hermite5> curve,
                       double curveWidth, Eigen::Vector3d curveColor,
                       Eigen::Vector3d tangentColor,
                       Eigen::Vector3d secondDerivativeColor,
                       Eigen::Vector3d controlPointsColor) :
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
                this->controlPointsColor, 0.015));
    this->endControlPoint.reset(new Point2D(endControlPoint,
                this->controlPointsColor, 0.015));
}

Hermite52D::~Hermite52D() {
    // TODO: properly destroy everything if needed
}

void Hermite52D::render() {

    this->startTangent->render();
    this->endTangent->render();
    this->startSecondDerivative->render();
    this->endSecondDerivative->render();
    glUseProgram(Curve2D::shader->getProgramID());
    glBindVertexArray(Curve2D::vertexArrayObjectID);
    glDrawElements(GL_TRIANGLES, Curve2D::indices.size(), GL_UNSIGNED_INT,
                   NULL);
    this->startControlPoint->render();
    this->endControlPoint->render();
}

bool Hermite52D::hasToBeRedrawn() { return Curve2D::isDirty; }
