/**
 * @file Hermite.h
 * @brief Describes a cubic Hermite curve
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-01
 */
#include <Eigen/Vector3d>

#include "Curve.h"

class Hermite3 : public Curve {

public:
    Hermite3(Eigen::Vector3d p1, Eigen::Vector3d t1,
             Eigen::Vector3d p2, Eigen::Vector3d t2);
    ~Hermite3();
    

private:
    Eigen::Vector3d p1;
    Eigen::Vector3d p2;
    Eigen::Vector3d t1;
    Eigen::Vector3d t2;
};
