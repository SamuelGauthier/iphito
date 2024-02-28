/**
 * @file Camera.h
 * @brief Describes the camera matrices generation
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2019-08-05
 */
#ifndef CAMERA_H
#define CAMERA_H

#include <Eigen/Core>

namespace iphito::renderer {

class Camera {

public:
    Camera() = delete;
    ~Camera() = delete;
    
    static Eigen::Matrix4d orthographic(double left, double right,
                                        double bottom, double top, double zNear,
                                        double zFar);

    static Eigen::Matrix3d orthographic(double left, double right,
                                        double bottom, double top);

    static Eigen::Matrix4d lookAt(const Eigen::Vector3d& position,
                                  const Eigen::Vector3d& target,
                                  const Eigen::Vector3d& up);
};

} /* namespace iphito::renderer */

#endif /* ifndef CAMERA_H */
