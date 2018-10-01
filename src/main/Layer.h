/**
 * @file Layer.h
 * @brief Describes a Layer
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-09-14
 */
#include <atomic>
#include <unordered_map>
#include <memory>
#include <vector>

#include "Curve.h"

class Layer {

public:
    //Layer();
    Layer(std::vector<std::unique_ptr<Layer>> children =
            std::vector<std::unique_ptr<Layer>>(),
          std::vector<std::unique_ptr<Curve>> curves =
            std::vector<std::unique_ptr<Curve>>());
    ~Layer();

    unsigned long long getID() { return this->id; };
    bool addCurve(std::unique_ptr<Curve>& curve);
    bool addCurves(std::vector<std::unique_ptr<Curve>> curves);
    bool addLayer(std::unique_ptr<Layer>& layer);
    bool addLayers(std::vector<std::unique_ptr<Layer>> layers);
    bool containsCurve(unsigned long long id);
    bool containsLayer(unsigned long long id);
    bool removeCurve(unsigned long long id);
    bool removeLayer(unsigned long long id);
        

private:
    static std::atomic<unsigned long long> nextID;
    unsigned long long id;
    std::unordered_map<unsigned long long, std::unique_ptr<Layer>> children;
    std::unordered_map<unsigned long long, std::unique_ptr<Curve>> curves;
};
