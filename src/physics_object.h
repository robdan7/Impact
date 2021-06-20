//
// Created by Robin on 2021-05-30.
//
#pragma once
#include "impact.h"
namespace Impact {
    class Physics_object {
        friend Physics_world;
        virtual void integrate(scalar duration) {};
        virtual void apply_force(const vec3& force) {};
    };
}