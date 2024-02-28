/**
 * @file 2DCurve.h
 * @brief Describes a 2D parametric curve to be rendered
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2018-12-01
 */
#ifndef CURVE2D_H
#define CURVE2D_H

#include <atomic>
#include <memory>
#include <random>
#include <vector>
#include <Eigen/Core>
#include <GL/glew.h>

#include "src/main/math/Curve.h"
#include "Shader.h"

namespace iphito::renderer {

class Curve2D {

public:
    Curve2D() = delete;

    Curve2D(std::shared_ptr<iphito::math::Curve> curve, double curveWidth = 1.0,
            const Eigen::Vector3d& curveColor = Eigen::Vector3d(0.0, 0.0, 0.0),
            const Eigen::Matrix3d& transform = Eigen::Matrix3d::Identity());
    void recomputeVerticesAndIndices();
    unsigned long long getID();
    void updateModelMatrix(const Eigen::Matrix4d& model);
    void updateViewMatrix(const Eigen::Matrix4d& view);
    void updateProjectionMatrix(const Eigen::Matrix4d& projection);
    

    virtual ~Curve2D() = 0;
    virtual void render() = 0;
    virtual bool hasToBeRedrawn() = 0;
    

protected:

    std::shared_ptr<iphito::math::Curve> curve;

    std::unique_ptr<Shader> shader;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    GLuint vertexArrayObjectID;
    GLuint vertexBufferID;
    GLuint indexBufferID;

    double curveWidth;
    Eigen::Vector3d curveColor;

    bool isDirty;
    bool viewMatrixUpdate;
    bool projectionMatrixUpdate;

    Eigen::Matrix4d model;
    Eigen::Matrix4d view;
    Eigen::Matrix4d projection;

private:
    static std::atomic<unsigned long long> nextID;
    unsigned long long id;
    static std::mt19937_64 engine;
    static std::uniform_real_distribution<double> distribution;
    std::vector<Eigen::Vector2d> samplePoints;

    void sampleCurve(double a, double b);
    void sampleCurve(double a, double b, const iphito::math::Curve& curve);
    bool isFlat(Eigen::Vector2d a, Eigen::Vector2d b, Eigen::Vector2d m);
    void verticesFromSamplePoints(std::vector<Eigen::Vector2d>& samplePoints);
    void indicesFromVertices();
    void updateSamplePoints(Eigen::Matrix3d& transform);
};

inline Curve2D::~Curve2D() {}

} /* namespace iphito::renderer */

#endif /* ifndef CURVE3D_H */
