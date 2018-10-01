/**
 * @file Layer.h
 * @brief Implements the Layer description
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-09-14
 */
#include <vector>
#include "Layer.h"

std::atomic<unsigned long long> Layer::nextID = 0;

Layer::Layer(std::vector<std::unique_ptr<Layer>> children, 
             std::vector<std::unique_ptr<Curve>> curves) {

    this->id = this->nextID.fetch_add(1);

    for (auto& i : children) {
        this->children.insert({i->getID(), std::move(i)});
    }

    for (auto& i : curves) {
        this->curves.insert({i->getID(), std::move(i)});
    }
}

Layer::~Layer() {}

bool Layer::addCurve(std::unique_ptr<Curve>& curve) {

    unsigned long long curveID = curve->getID();

    if(this->containsCurve(curveID)) return false;

    this->curves.insert({curveID, std::move(curve)});
    return true;
}


bool Layer::addCurves(std::vector<std::unique_ptr<Curve>> curves) {

    for (auto& i : curves) {
        std::unique_ptr<Curve> j = std::move(i);
        addCurve(j);
    }
}

bool Layer::addLayer(std::unique_ptr<Layer>& layer) {

    unsigned long long layerID = layer->getID();

    if(this->getID() == layerID) return false;
    if(this->containsLayer(layerID)) return false;

    this->children.insert({layerID, std::move(layer)});
    return true;
}

bool Layer::addLayers(std::vector<std::unique_ptr<Layer>> layers) {

    for (auto& i : layers) {
        std::unique_ptr<Layer> j = std::move(i);
        addLayer(j);
    }
}

bool Layer::containsCurve(unsigned long long id) {
    
    if(this->curves.find(id) != this->curves.end()) return true;

    for(auto& i : this->children)
        if(i.second->containsCurve(id)) return true;

    return false;
}

bool Layer::containsLayer(unsigned long long id) {
    
    if(this->children.find(id) != this->children.end()) return true;

    for(auto& i : this->children)
        if(i.second->containsLayer(id)) return true;

    return false;
}

bool Layer::removeCurve(unsigned long long id) {

}

bool Layer::removeLayer(unsigned long long id) {

    for (auto& i : this->children) {
        
    }
}
