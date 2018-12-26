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
#include <vector>
#include <eigen3/Eigen/Core>
#include <GL/glew.h>

#include "math/Curve.h"
#include "Shader.h"

class Curve2D {

public:
    Curve2D() = delete;

    Curve2D(std::unique_ptr<Curve> curve, Eigen::Vector3d curveColor =
            Eigen::Vector3d(0.0, 0.0, 0.0), double curveWidth = 1.0);
    void recomputeVerticesAndIndices();
    unsigned long long getID();
    

    virtual ~Curve2D() = 0;
    virtual void render() = 0;
    virtual bool hasToBeRedrawn() = 0;
    

protected:

    std::unique_ptr<Curve> curve;

    std::unique_ptr<Shader> shader;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    GLuint vertexArrayObjectID;
    GLuint vertexBufferID;
    GLuint indexBufferID;

    Eigen::Vector3d curveColor;
    double curveWidth;

    bool isDirty;

private:
    static std::atomic<unsigned long long> nextID;
    unsigned long long id;

    std::vector<Eigen::Vector2d> sampleCurve();
    void computeVerticesFromSamplePoints(std::vector<Eigen::Vector2d>& samplePoints);
    void computeIndicesFromVertices();
};

inline Curve2D::~Curve2D() {}

#endif /* ifndef CURVE2D_H */
