#include <atomic>
#include <unordered_set>

#include "Curve.h"

class Layer {

public:
    //Layer();
    Layer(std::unordered_set<std::unique_ptr<Layer>> children =
            std::unordered_set<std::unique_ptr<Layer>>(),
          std::unordered_set<std::unique_ptr<Curve>> curves =
            std::unordered_set<std::unique_ptr<Curve>>());
    ~Layer();

    unsigned long long getID() { return this->id; };
    bool addCurve(Curve* curve);
    bool addCurves(std::unordered_set<std::unique_ptr<Curve>> curves);
    bool addLayer(Layer* layer);
    bool addLayers(std::unordered_set<std::unique_ptr<Layer>> layers);
        

private:
    static std::atomic<unsigned long long> nextID;
    unsigned long long id;
    std::unordered_set<std::unique_ptr<Layer>> children;
    std::unordered_set<std::unique_ptr<Curve>> curves;
};
