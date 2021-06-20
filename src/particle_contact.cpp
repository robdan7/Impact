//
// Created by Robin on 2021-05-19.
//
#include "particle_contact.h"
namespace Impact {

    void particle_contact::resolve(scalar duration) {
        resolve_velocity(duration);
        resolve_depth(duration);
    }

    scalar particle_contact::separating_velocity() const {
        vec3 relative_velocity = p_particles[0]->get_velocity();
        if (p_particles[1]) relative_velocity -= p_particles[1]->get_velocity();

        return relative_velocity.dot(contact_normal);
    }

    void particle_contact::resolve_velocity(scalar duration) {
        scalar separating_velocity = this->separating_velocity();
        if (separating_velocity > 0) {
            return; /// No collision to be resolved.
        }

        scalar new_sep_velocity = -separating_velocity*restitution;

        vec3 acceleration_velocity = p_particles[0]->get_acc();
        if(p_particles[1]) acceleration_velocity -= p_particles[1]->get_acc();
        scalar acc_velocity_speed = acceleration_velocity.dot(contact_normal)*duration;

        if (acc_velocity_speed < 0) {
            new_sep_velocity += restitution*acc_velocity_speed;
            if (new_sep_velocity < 0) new_sep_velocity = 0;
        }

        scalar delta_velocity = new_sep_velocity-separating_velocity;

        scalar total_inverse_mass = p_particles[0]->get_inverse_mass() + (p_particles[1]?p_particles[1]->get_inverse_mass():0);

        if (total_inverse_mass <= 0) return;

        scalar impulse = delta_velocity / total_inverse_mass;

        vec3 impulse_per_mass = contact_normal * impulse;
        p_particles[0]->set_velocity(impulse_per_mass*p_particles[0]->get_inverse_mass()+p_particles[0]->get_velocity());
        if (p_particles[1]) {
            p_particles[1]->set_velocity(impulse_per_mass*(-p_particles[1]->get_inverse_mass())+p_particles[1]->get_velocity());
        }


    }

    void particle_contact::resolve_depth(scalar duration) {
        if (depth <= 0) return;

        scalar total_inverse_mass = p_particles[0]->get_inverse_mass() + (p_particles[1]?p_particles[1]->get_inverse_mass():0);
        if (total_inverse_mass <= 0) return;
        vec3 move_per_mass = contact_normal*(-depth/total_inverse_mass);

        p_particles[0]->set_position(move_per_mass*p_particles[0]->get_inverse_mass()+p_particles[0]->get_position());
        if (p_particles[1]) p_particles[1]->set_position(move_per_mass*(-p_particles[1]->get_inverse_mass())+p_particles[1]->get_position());
    }

    Contact_resolver::Contact_resolver(uint32_t iterations) : iterations(iterations){

    }

    void Contact_resolver::set_iterations(uint32_t iterations) {
        iterations = iterations;
    }

    void Contact_resolver::resolve_contacts(particle_contact *contact_array, uint32_t num_contacts, scalar duration) {
        iterations_used = 0;
        while(iterations_used < iterations) {
            scalar max = 0;
            uint32_t max_index = num_contacts;
            for (uint32_t i = 0; i < num_contacts; ++i) {
                scalar sep_vel = contact_array[i].separating_velocity();
                if (sep_vel < max) {
                    max = sep_vel;
                    max_index = i;
                }
            }
            contact_array[max_index].resolve(duration);
            iterations_used++;
        }
    }
}