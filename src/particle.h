//
// Created by Robin on 2021-05-19.
//
#pragma once
#include "vec3.h"
#include "physics_object.h"
namespace Impact {
    struct particle : public Physics_object{
    public:
        particle(const vec3& position,const vec3& velocity, scalar inverse_mass = 0, const vec3& acceleration = {}):inverse_mass(inverse_mass),position(position),velocity(velocity),acceleration(acceleration) {}
        particle(const vec3& acceleration) : acceleration(acceleration) {}

        /**
         * Apply force that will be translated into acceleration at the next integration step.
         * @param force
         */
        void apply_force(const vec3& force) override{
            force_accumulation+= force;
        }
        void integrate(scalar duration) override {
            vec3 acc = acceleration;
            force_accumulation*=inverse_mass;
            acc+=force_accumulation;

            acc*=duration;
            velocity+=acc;
            velocity*= real_pow(damping,duration);
            position+=(velocity*duration);
            clear_forces();
        }
        void clear_forces() {
            this->force_accumulation = 0;
        }

        const vec3& get_velocity() const {
            return velocity;
        }
        void set_velocity(const vec3& v) {
            velocity = v;
        }
        const vec3& get_position() const {
            return position;
        }
        void set_position(const vec3& p) {
            position = p;
        }
        const vec3& get_acc() const {
            return acceleration;
        }
        const scalar& get_inverse_mass() const {
            return inverse_mass;
        }

    protected:
        vec3 position{};
        vec3 velocity{};
        vec3 acceleration{}; /// Base acceleration from e.g. gravitation.
        vec3 force_accumulation{};
        scalar inverse_mass = 0;
        scalar damping = (scalar)0.999;
    };
}