//
// Created by Robin on 2021-05-27.
//
#pragma once
#include "vec3.h"
#include "defines.h"
#include "quaternion.h"
#include "mat4.h"
#include "mat3.h"
#include "particle.h"
#include "volume.h"
#include "tools/allocator.h"
#include "tools/ptr.h"
namespace Impact {
    class Rigidbody : public particle {
        friend Same_allocator<uint16_t,Rigidbody>;
        friend pointer<Rigidbody>;
    public:
        static pointer<Rigidbody> Create(const vec3& position,const vec3& velocity, scalar inverse_mass = 0, const vec3& acceleration = {});
        void integrate(scalar duration) override;
        void set_inertia(const mat3& inertia);
        void apply_torque(const vec3& t);
        void apply_force_at_point(const vec3& force, const vec3& point);
        void apply_force_at_body_point(const vec3& force, const vec3& point);

        /**
         * Apply the transform to a matrix that can then be used for rendering.
         * @param transform
         */
        void copy_transform(mat4& transform);
    private:
        Rigidbody(const vec3& position,const vec3& velocity, scalar inverse_mass, const vec3& acceleration);
        ~Rigidbody() = default;
        //scalar inverse_mass;
        mat3 local_inverse_inertia;
        mat3 world_inverse_inertia;
        //vec3 position;
        quaternion rotation;
        //vec3 velocity;
        vec3 rotation_velocity;
        mat4 transform;
        scalar angular_damping;
        vec3 acc_torque;
        pointer<Physics_object> m_physics_instance; // This stores a reference to itself in the global Impact data structure.
        static Same_arena_allocator<1,uint16_t,Rigidbody> s_allocator;
    };
}