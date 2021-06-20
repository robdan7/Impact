//
// Created by Robin on 2021-05-19.
//
#include "vec4.h"
#include "mat3.h"
#include "volume.h"
#include "tools/octree.h"
#include <iostream>
#include "impact.h"
#include "rigidbody.h"
struct Structure {
    Impact::vec3 position;
};

int main() {
    Impact::Spatial_octree<Structure> my_octree = Impact::Spatial_octree<Structure>();

    my_octree.insert({0,0,0},{1,1,1});
    my_octree.insert({8,-8,-8},{1,1,1});
    my_octree.insert({8,-8,8},{1,1,1});
    my_octree.insert({8,8,-8},{1,1,1});
    my_octree.insert({8,8,8},{1,1,1});
    my_octree.insert({-8,-8,-8},{1,1,1});
    my_octree.insert({-8,-8,8},{1,1,1});
    my_octree.insert({-8,8,-8},{1,1,1});
    my_octree.insert({-8,8,8},{1,1,1});

    my_octree.insert({0,0,0},{100,100,100});


    std::vector<Structure*> result;
    my_octree.intersect(Impact::vec3(10,5,2),Impact::vec3(2.0f,2.0f,3.0f),result);

    std::cout << result.size() << std::endl;

    std::vector<std::pair<uint16_t, uint16_t>> result2;
    my_octree.intersect(result2);


    for (auto& k : result2) {
        std::cout << "Node " << k.first << " intersects with " << k.second << std::endl;
    }

    /*
    Impact::Physics_world world;
    Impact::set_physics_world(&world);

    auto rigidbody = Impact::Rigidbody::Create({22,0,0},{0,0,0},(Impact::scalar)1,{0.0f,-9.8f,0.0f});

    std::cout << rigidbody->get_position().y << std::endl;
    Impact::integrate((Impact::scalar)1.0);
    std::cout << rigidbody->get_position().y << std::endl;
     */
}
