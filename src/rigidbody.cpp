//
// Created by Robin on 2021-05-27.
//
#include "rigidbody.h"
#include "impact.h"
namespace Impact {
    Same_arena_allocator<1,uint16_t,Rigidbody> Rigidbody::s_allocator;

    void Rigidbody::copy_transform(mat4& transform) {
        transform = this->transform;
    }


    void Rigidbody::set_inertia(const mat3 &inertia) {
        this->local_inverse_inertia = inertia.inverse();
    }

    void Rigidbody::integrate(scalar duration) {
        vec3 angular_acceleration = world_inverse_inertia*acc_torque;
        rotation_velocity += angular_acceleration*duration;
        rotation_velocity*= real_pow(angular_damping,duration);
        rotation+=rotation_velocity*duration;
        rotation.normalize();

        particle::integrate(duration);
        this->acc_torque = 0;

        apply_transform(this->transform,this->position,this->rotation);
        transform_inertia(this->world_inverse_inertia,this->rotation,this->local_inverse_inertia,transform); /// TODO Move this somewhere else

    }

    void Rigidbody::apply_torque(const vec3 &t) {
        this->acc_torque += t;
    }

    private_ptr<Rigidbody> Rigidbody::Create(const vec3& position, const vec3& velocity, scalar inverse_mass, const vec3& acceleration) {
        auto ID =  (ptr_primitive)s_allocator.alloc(position,velocity,inverse_mass,acceleration);

        //return pointer<Rigidbody>(ID,(Container<Rigidbody>*)s_allocator.);
        return private_ptr<Rigidbody>(ID, (Container<Rigidbody>*)&s_allocator);
    }


    Rigidbody::Rigidbody(const vec3 &position, const vec3 &velocity, scalar inverse_mass, const vec3 &acceleration)
            : particle(position, velocity, inverse_mass, acceleration){
    }

    void Rigidbody::apply_force_at_point(const vec3 &force, const vec3 &point) {
        vec3 pt = point;
        pt -= this->position;
        force_accumulation += force;
        acc_torque += pt.cross(force);
    }

    void Rigidbody::apply_force_at_body_point(const vec3 &force, const vec3 &point) {
        vec3 pt = this->transform*point;
        apply_force_at_point(force,pt);
    }
}
