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

    // TODO: Remove ugly hardwritten radius
    this->startControlPoint.reset(new Point2D(startControlPoint,
                                              this->controlPointsColor, 0.015));
    this->endControlPoint.reset(new Point2D(endControlPoint,
                                              this->controlPointsColor, 0.015));
}

Hermite32D::~Hermite32D() {

    // TODO: Correctly destory buffers
}

void Hermite32D::render() {

    if (this->hasToBeRedrawn()) {
        Curve2D::recomputeVerticesAndIndices();
    }

    this->startTangent->render();
    this->endTangent->render();

    glUseProgram(this->shader->getProgramID());
    glBindVertexArray(this->vertexArrayObjectID);
    glDrawElements(GL_TRIANGLES, Curve2D::indices.size(), GL_UNSIGNED_INT,
                   NULL);
    glBindVertexArray(0);

    this->startControlPoint->render();
    this->endControlPoint->render();
}

bool Hermite32D::hasToBeRedrawn() { return this->isDirty; }

void Hermite32D::updateTransform(Eigen::Matrix3d& transform) {

    Logger::Instance()->debug("[Hermite32D] Updating transform");

    if (transform.isApprox(Eigen::Matrix3d::Identity())) {
        if (this->hasToBeRedrawn())
            this->isDirty = false;
        return;
    }

    this->transform(0, 2) += transform(0, 2);
    this->transform(1, 2) += transform(1, 2);

    this->transform(0, 0) += transform(0, 0);
    this->transform(1, 1) += transform(1, 1);

    if (this->transform(0, 0) < 0.0) {
        this->transform(0, 0) = 0.0;
        this->transform(1, 1) = 0.0;
    }

    this->isDirty = true;

    this->startTangent->updateTransform(transform);
    this->endTangent->updateTransform(transform);
    this->startControlPoint->updateTransform(transform);
    this->endControlPoint->updateTransform(transform);

}
