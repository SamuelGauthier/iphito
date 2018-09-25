#include "Layer.h"

std::atomic<unsigned long long> Layer::nextID = 0;

Layer::Layer(std::unordered_set<std::unique_ptr<Layer>> children, 
             std::unordered_set<std::unique_ptr<Curve>> curves) {

    this->id = this->nextID.fetch_add(1);
    this->children = std::move(children);
    this->curves = std::move(curves);
}

Layer::~Layer() {}


