#include "Layer.h"

std::atomic<unsigned long long> Layer::nextID = 0;

Layer::Layer() {

    this->id = this->nextID.fetch_add(1);
    this->children = {};
    this->curves = {};
}

Layer::~Layer() {

    for (auto& i : children)
        delete i;

    for (auto& i : curves)
        delete i;

}
