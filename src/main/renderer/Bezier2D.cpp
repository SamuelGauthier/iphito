/**
 * @file Bezier2D.cpp
 * @brief Implements the 2D Bezier curve
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2019-02-23
 */
#include <iostream>
#include "Bezier2D.h"

Bezier2D::Bezier2D(std::shared_ptr<Bezier> curve, Eigen::Vector3d curveColor,
                   double curveWidth, Eigen::Vector3d controlPointsColor,
                   Eigen::Vector3d controlPolygonColor) :
    curve{curve}, Curve2D(curve, curveColor, curveWidth),
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

    for (auto& i : this->controlPolygon)
        i->render();

    glUseProgram(Curve2D::shader->getProgramID());
    glBindVertexArray(Curve2D::vertexArrayObjectID);
    glDrawElements(GL_TRIANGLES, Curve2D::indices.size(), GL_UNSIGNED_INT,
                   NULL);

    for (auto& i : this->controlPoints)
        i->render();

}

bool Bezier2D::hasToBeRedrawn() { return Curve2D::isDirty; }
