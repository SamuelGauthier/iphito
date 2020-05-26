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

namespace iphito::renderer {

using namespace iphito::math;

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

    if (Curve2D::viewMatrixUpdate) {

        for (auto& i : this->controlPolygon)
            i->updateViewMatrix(Curve2D::view);

        for (auto& i : this->controlPoints)
            i->updateViewMatrix(Curve2D::view);

        Curve2D::viewMatrixUpdate = false;
    }

    if (Curve2D::projectionMatrixUpdate) {

        for (auto& i : this->controlPolygon)
            i->updateProjectionMatrix(Curve2D::projection);

        for (auto& i : this->controlPoints)
            i->updateProjectionMatrix(Curve2D::projection);

        Curve2D::projectionMatrixUpdate = false;
    }

    for (auto& i : this->controlPolygon)
        i->render();

    Curve2D::shader->useProgram();
    Curve2D::shader->setMatrix4("model", Curve2D::model);
    Curve2D::shader->setMatrix4("view", Curve2D::view);
    Curve2D::shader->setMatrix4("projection", Curve2D::projection);
    glBindVertexArray(Curve2D::vertexArrayObjectID);
    glDrawElements(GL_TRIANGLES, Curve2D::indices.size(), GL_UNSIGNED_INT,
                   NULL);
    glBindVertexArray(0);

    for (auto& i : this->controlPoints)
        i->render();

}

bool Bezier2D::hasToBeRedrawn() { return Curve2D::isDirty; }

} /* namespace iphito::renderer */
