/**
 * @file Test_Layer.cpp
 * @brief Layer tests
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-09-28
 */
#include <memory>
#include <vector>
#include "catch.h"
#include "renderer/Layer.h"

using namespace iphito::renderer;

TEST_CASE("layers have an unique ID", "[Layer]") {

    Layer l1;
    Layer l2;

    REQUIRE(l1.getID() == 0);
    REQUIRE(l1.getID() != l2.getID());
}

TEST_CASE("layers can be added to layers", "[Layer]"){

    std::unique_ptr<Layer> l1(new Layer());
    std::unique_ptr<Layer> l2(new Layer());

    SECTION("adding a layer to a layer should contain it", "[Layer]") {
        
        unsigned long long l2ID = l2->getID();
        REQUIRE(l1->addLayer(l2) == true);
        REQUIRE(l1->containsLayer(l2ID) == true);
    }

    SECTION("adding itself to itslef should fail", "[Layer]") {
        
        unsigned long long l1ID = l1->getID();
        REQUIRE(l1->addLayer(l1) == false);
        REQUIRE(l1->containsLayer(l1ID) == false);
    }
}

TEST_CASE("layers can be constructed with other layers as their children",
          "[Layer]") {

    std::vector<std::unique_ptr<Layer>> children;
    std::vector<unsigned long long> ids;

    int num_elems = 10;

    for(int i = 0; i < num_elems; i++) {

        std::unique_ptr<Layer> current(new Layer());
        ids.push_back(current->getID());
        children.push_back(std::move(current));
    }

    std::unique_ptr<Layer> l1(new Layer(std::move(children)));

    for(int i = 0; i < num_elems; i++) {

        REQUIRE(l1->containsLayer(ids[i]) == true);
    }
}
