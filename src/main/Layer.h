#include <atomic>
#include <unordered_set>
#include <memory>
#include <vector>

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
    bool addCurve(std::unique_ptr<Curve>& curve);
    bool addCurves(std::vector<std::unique_ptr<Curve>> curves);
    bool addLayer(std::unique_ptr<Layer>& layer);
    bool addLayers(std::vector<std::unique_ptr<Layer>> layers);
    bool containsCurve(std::unique_ptr<Curve>& curve);
    bool containsLayer(std::unique_ptr<Layer>& layer);
        

private:
    static std::atomic<unsigned long long> nextID;
    unsigned long long id;
    std::unordered_set<std::unique_ptr<Layer>> children;
    std::unordered_set<std::unique_ptr<Curve>> curves;
};
