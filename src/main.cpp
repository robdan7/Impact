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
#include "particle_contact.h"

using particle_ptr = Impact::private_ptr<Impact::particle>;

int main() {
    std::string s = "Hello world!";
    std::string s2 = std::move(s);
    /// Initiate physics with a world.
    Impact::Physics_world world;
    Impact::set_physics_world(&world);

    Impact::Spatial_octree<particle_ptr> my_octree;


    my_octree.push({0.3f,5.0f,0.0f},{1,1,1},Impact::particle::Create({0,0,0},{0,0,0},1.0f,{0,-9.82f,0}));
    my_octree.push({0.0f,0.0f,0.0f},{1,1,1},Impact::particle::Create({0,0,0}));

    /*
    my_octree.insert({0.3f,5.0f,0.0f},{1,1,1}, Impact::vec3(0,0,0), Impact::vec3(), (Impact::scalar)1,Impact::vec3(0,(Impact::scalar)-9.82,0));
    my_octree.insert({0,0,0},{1,1,1},Impact::vec3(),Impact::vec3());
*/
    Impact::scalar time = 0;
    Impact::Contact_resolver resolver(10);

    while(true) {
        Impact::integrate(0.16f);
        std::vector<std::pair<particle_ptr*,particle_ptr*>> collisionresult;
        my_octree.intersect(collisionresult);
        std::vector<Impact::particle_contact> contacts;
        for (auto& pair : collisionresult) {
            auto radi = pair.first->operator->()->get_position()-pair.second->operator->()->get_position();
            if (radi.len2() <= 4.0f) {
                Impact::scalar len = radi.len();
                radi.normalize();
                contacts.emplace_back(pair.first->operator->(),pair.second->operator->(),radi,len-2.0f);
            }
        }
        if (!contacts.empty()) {
            resolver.resolve_contacts(&contacts[0],(uint32_t)contacts.size(),0.16f);
        }

        time += 0.16f;
        if (time > 10.0f) {
            break;
        }
    }





/*
    std::vector<Structure*> result;
    my_octree.intersect(Impact::vec3(10,5,2),Impact::vec3(2.0f,2.0f,3.0f),result);

    std::cout << result.size() << std::endl;

    std::vector<std::pair<Structure*, Structure*>> result2;
    my_octree.intersect(result2);
*/


    /*
    Impact::Physics_world world;
    Impact::set_physics_world(&world);

    auto rigidbody = Impact::Rigidbody::Create({22,0,0},{0,0,0},(Impact::scalar)1,{0.0f,-9.8f,0.0f});

    std::cout << rigidbody->get_position().y << std::endl;
    Impact::integrate((Impact::scalar)1.0);
    std::cout << rigidbody->get_position().y << std::endl;
     */
}
