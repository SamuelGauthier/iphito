/**
 * @file Bezier2D.cpp
 * @brief Implements the 2D Bezier curve
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2019-02-23
 */
#include <iostream>

#include "Bezier2D.h"
#include "utils/Logger.h"

Bezier2D::Bezier2D(std::shared_ptr<Bezier> curve, double curveWidth,
                   Eigen::Vector3d curveColor,
                   Eigen::Vector3d controlPointsColor,
                   Eigen::Vector3d controlPolygonColor) :
    curve{curve}, Curve2D(curve, curveWidth, curveColor),
    controlPointsColor{controlPointsColor},
    controlPolygonColor{controlPolygonColor} {

    Curve2D::recomputeVerticesAndIndices();

    std::vector<Eigen::Vector2d> points = this->curve->getPoints();

    for (auto& i : points) {
        std::unique_ptr<Point2D> p(new Point2D(i, this->controlPointsColor,
                                               0.015));
        this->controlPoints.push_back(std::move(p));
    }

    for (int i = 0; i < points.size() - 1; i++) {
        std::unique_ptr<Line2D> l(new Line2D(points[i], points[i+1], 0.0025,
                                  this->controlPointsColor));
        this->controlPolygon.push_back(std::move(l));
    }
}

Bezier2D::~Bezier2D() {
    // TODO: Correctly destroy everything
}

void Bezier2D::render() {

    if (this->hasToBeRedrawn()) {
        this->recomputeVerticesAndIndices();
    }

    for (auto& i : this->controlPolygon)
        i->render();

    glUseProgram(this->shader->getProgramID());
    glBindVertexArray(this->vertexArrayObjectID);
    glDrawElements(GL_TRIANGLES, Curve2D::indices.size(), GL_UNSIGNED_INT,
                   NULL);
    glBindVertexArray(0);

    for (auto& i : this->controlPoints)
        i->render();

}

bool Bezier2D::hasToBeRedrawn() { return Curve2D::isDirty; }

void Bezier2D::updateTransform(Eigen::Matrix3d& transform) {

    Logger::Instance()->debug("[Bezier2D] Updating transform");

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

    for (auto& i : this->controlPolygon)
        i->updateTransform(transform);

    for (auto& i : this->controlPoints)
        i->updateTransform(transform);
}
