/**
 * @file Camera.cpp
 * @brief Implements the camera matrices generation 
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2019-08-05
 */
#include "Camera.h"

#include <eigen3/Eigen/Dense>

namespace iphito::renderer {

Eigen::Matrix4d Camera::orthographic(double left, double right,
                                     double bottom, double top,
                                     double zNear, double zFar) {

    Eigen::Matrix4d camera = Eigen::Matrix4d::Identity();

    camera(0,0) = 2 / (right - left);
    camera(0,3) = -(right + left) / (right - left);

    camera(1,1) = 2 / (top - bottom);
    camera(1,3) = -(top + bottom) / (top - bottom);

    camera(2,2) = -2 / (zFar - zNear);
    camera(2,3) = -(zFar + zNear) / (zFar - zNear);

    camera(3,3) = 1.0;

    return camera;
}

Eigen::Matrix3d Camera::orthographic(double left, double right,
                                     double bottom, double top) {

    Eigen::Matrix3d camera = Eigen::Matrix3d::Identity();

    camera(0,0) = 2 / (right - left);
    camera(0,2) = -(right + left) / (right - left);

    camera(1,1) = 2 / (top - bottom);
    camera(1,2) = -(top + bottom) / (top - bottom);

    camera(2,2) = 1.0;

    return camera;
}

Eigen::Matrix4d Camera::lookAt(Eigen::Vector3d position, Eigen::Vector3d target,
                               Eigen::Vector3d up) {

    // Camera "direction" vector
    Eigen::Vector3d cameraZ = (position - target);
    cameraZ.normalize();

    // Camera "right" vector
    Eigen::Vector3d cameraX = up.cross(cameraZ);
    cameraX.normalize();

    // Camera "up" vector
    Eigen::Vector3d cameraY = cameraZ.cross(cameraX);
    cameraY.normalize();

    Eigen::Matrix4d cameraXYZ = Eigen::Matrix4d::Identity();
    cameraXYZ << cameraX(0), cameraX(1), cameraX(2), 0,
                 cameraY(0), cameraY(1), cameraY(2), 0,
                 cameraZ(0), cameraZ(1), cameraZ(2), 0,
                 0, 0, 0, 1;

    Eigen::Matrix4d cameraPosition = Eigen::Matrix4d::Identity();
    cameraPosition(0, 3) = -position(0);
    cameraPosition(1, 3) = -position(1);
    cameraPosition(2, 3) = -position(2);

    Eigen::Matrix4d lookAt = cameraXYZ * cameraPosition;
    return lookAt;
}

} /* namespace iphito::renderer */

