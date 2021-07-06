//
// Created by Robin on 2021-06-22.
//
#include "particle.h"
namespace Impact {
    Same_arena_allocator<1,uint16_t,particle> particle::s_allocator;

    private_ptr<particle>
    particle::Create(const vec3 &position, const vec3 &velocity, scalar inverse_mass, const vec3 &acceleration) {
        auto ID =  (ptr_primitive)s_allocator.alloc(position,velocity,inverse_mass,acceleration);

        return private_ptr<particle>(ID, (Container<particle>*)&s_allocator);
    }

    private_ptr<particle> particle::Create(const vec3 &acceleration) {
        auto ID =  (ptr_primitive)s_allocator.alloc(acceleration);

        return private_ptr<particle>(ID, (Container<particle>*)&s_allocator);
    }
}