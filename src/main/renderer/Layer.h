/**
 * @file Layer.h
 * @brief Describes a Layer
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-09-14
 */
#ifndef LAYER_H
#define LAYER_H

#include <atomic>
#include <map>
#include <memory>
#include <vector>

#include <eigen3/Eigen/Core>

#include "Curve2D.h"

class Layer {

public:
    //Layer();
    Layer(std::vector<std::unique_ptr<Layer>> children =
            std::vector<std::unique_ptr<Layer>>(),
          std::vector<std::unique_ptr<Curve2D>> curves =
            std::vector<std::unique_ptr<Curve2D>>());
    ~Layer();

    unsigned long long getID() { return this->id; };
    bool addCurve(std::unique_ptr<Curve2D>& curve);
    void addCurves(std::vector<std::unique_ptr<Curve2D>> curves);
    bool addLayer(std::unique_ptr<Layer>& layer);
    void addLayers(std::vector<std::unique_ptr<Layer>> layers);
    bool containsCurve(unsigned long long id);
    bool containsLayer(unsigned long long id);
    bool removeCurve(unsigned long long id);
    bool removeLayer(unsigned long long id);
    void render();
    void updateViewMatrix(Eigen::Matrix4d view);
    void updateProjectionMatrix(Eigen::Matrix4d projection);
        

private:
    static std::atomic<unsigned long long> nextID;
    unsigned long long id;
    std::map<unsigned long long, std::unique_ptr<Layer>> children;
    std::map<unsigned long long, std::unique_ptr<Curve2D>> curves;
};

#endif /* ifndef LAYER_H */
