//
// Created by Robin on 2021-05-30.
//
#pragma once
#include "impact.h"
namespace Impact {
    class Physics_object {
        friend Physics_world;
    protected:
        Physics_object() : m_physics_instance(Impact::register_object(this)){};
        virtual void integrate(scalar duration) {};
        virtual void apply_force(const vec3& force) {};
    private:
        /// This stores a reference to itself in the global Impact data structure.
        /// When a physics object, e.g. a particle, is removed from memory we also want to delete registration from the engine.
        /// This pointer will do exactly that for us.
        private_ptr<Physics_object*> m_physics_instance;
    };
}