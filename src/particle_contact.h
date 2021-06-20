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