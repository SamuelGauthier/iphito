/**
 * @file Layer.h
 * @brief Implements the Layer description
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-09-14
 */
#include <vector>
#include "Layer.h"

namespace iphito::renderer {

std::atomic<unsigned long long> Layer::nextID = 0;

Layer::Layer(std::vector<std::unique_ptr<Layer>> children, 
             std::vector<std::unique_ptr<Curve2D>> curves) {

    this->id = this->nextID.fetch_add(1);

    for (auto& i : children) {
        this->children.insert({i->getID(), std::move(i)});
    }

    for (auto& i : curves) {
        this->curves.insert({i->getID(), std::move(i)});
    }
}

Layer::~Layer() {}

bool Layer::addCurve(std::unique_ptr<Curve2D>& curve) {

    unsigned long long curveID = curve->getID();

    if(this->containsCurve(curveID)) return false;

    this->curves.insert({curveID, std::move(curve)});
    return true;
}


void Layer::addCurves(std::vector<std::unique_ptr<Curve2D>> curves) {

    for (auto& i : curves) {
        std::unique_ptr<Curve2D> j = std::move(i);
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

void Layer::addLayers(std::vector<std::unique_ptr<Layer>> layers) {

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

    if(this->curves.erase(id) != 1) {

        for (auto& i : this->children) {
            if(i.second->removeCurve(id)) return true;
        }

        return false;
    }
    else {
        return true;
    }
}

bool Layer::removeLayer(unsigned long long id) {

    if(this->children.erase(id) != 1) {

        for (auto& i : this->children) {
            if(i.second->removeLayer(id)) return true;
        }

        return false;
    }

    return true;
}

void Layer::render() {

    // back to front rendering to ensure correct order.
    for(auto i = this->children.rbegin(); i != this->children.rend(); i++) {
        i->second->render();
    }

    for(auto i = this->curves.rbegin(); i != this->curves.rend(); i++) {
        i->second->render();
    }
}

void Layer::updateViewMatrix(Eigen::Matrix4d view) {

    for(auto i = this->curves.rbegin(); i != this->curves.rend(); i++) {
        i->second->updateViewMatrix(view);
    }
}

void Layer::updateProjectionMatrix(Eigen::Matrix4d projection) {

    for(auto i = this->curves.rbegin(); i != this->curves.rend(); i++) {
        i->second->updateProjectionMatrix(projection);
    }
}

} /* namespace iphito::renderer */
