//
// Created by Robin on 2021-05-19.
//
#pragma once
#include "particle.h"
#include "defines.h"
#include <stdint.h>
namespace Impact {
    class particle_contact {
    public:
        /**
         * Create a new particle contact
         * @param p1 - The first particle
         * @param p2 - The second particle. Can be a nullptr
         * @param contact_normal - The normal from the second to the first particle.
         * @param depth - The contact depth
         * @param restitution - A value between 0 and 1 that determines the bounce factor.
         */
        particle_contact(particle* p1, particle* p2, const vec3& contact_normal, scalar depth, scalar restitution = 0) : contact_normal(contact_normal),depth(depth),restitution(restitution){
            //p_particles[0] = p1;
            // p_particles[1] = p2;
        }
        particle* p_particles[2] = {nullptr};
        scalar restitution;
        vec3 contact_normal;
        scalar depth;
        scalar separating_velocity() const;
        void resolve(scalar duration);
    protected:
        void resolve_depth(scalar duration);
        void resolve_velocity(scalar duration);
    };

    class Contact_resolver {
    public:
        Contact_resolver(uint32_t iterations);
        void set_iterations(uint32_t iterations);
        void resolve_contacts(particle_contact* contact_array, uint32_t num_contacts,scalar duration);
    protected:
        uint32_t iterations;
        uint32_t iterations_used;
    };
}