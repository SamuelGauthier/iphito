#include "Layer.h"

std::atomic<unsigned long long> Layer::nextID = 0;

Layer::Layer(std::unordered_set<std::unique_ptr<Layer>> children, 
             std::unordered_set<std::unique_ptr<Curve>> curves) {

    this->id = this->nextID.fetch_add(1);
    this->children = std::move(children);
    this->curves = std::move(curves);
}

Layer::~Layer() {}

bool Layer::addCurve(std::unique_ptr<Curve>& curve) {

    if(this->containsCurve(curve)) return false;

    this->curves.insert(std::move(curve));
    return true;
}


bool Layer::addCurves(std::vector<std::unique_ptr<Curve>> curves) {

    for (auto& i : curves) {
        std::unique_ptr<Curve> j = std::move(i);
        addCurve(j);
    }
}

bool Layer::addLayer(std::unique_ptr<Layer>& layer) {

    if(this->containsLayer(layer)) return false;

    this->children.insert(std::move(layer));
    return true;
}

bool Layer::addLayers(std::vector<std::unique_ptr<Layer>> layers) {

    for (auto& i : layers) {
        std::unique_ptr<Layer> j = std::move(i);
        addLayer(j);
    }
}

bool Layer::containsCurve(std::unique_ptr<Curve>& curve) {
    
    for(auto& i : this->curves)
        if(i == curve) return true;

    for(auto& i : this->children)
        if(i->containsCurve(curve)) return true;

    return false;
}

bool Layer::containsLayer(std::unique_ptr<Layer>& layer) {
    
    for(auto& i : this->children)
        if(i == layer) return true;

    for(auto& i : this->children)
        if(i->containsLayer(layer)) return true;

    return false;
}
