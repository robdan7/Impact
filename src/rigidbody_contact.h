//
// Created by Robin on 2021-05-31.
//
#pragma once
#include "vec3.h"
#include "mat3.h"
#include "rigidbody.h"
namespace Impact {
    struct Rigidbody_contact {
        vec3 point;
        vec3 normal;
        scalar depth;
        mat3 contact_to_world;
        Rigidbody* bodies[2];

        void calc_contact_basis() {
            vec3 contact_agent[2];

            if (real_abs(normal.x) > real_abs(normal.y)) {
                const scalar s = (scalar)1.0/real_sqrt(normal.z*normal.z+normal.x*normal.x);
                contact_agent[0].x = normal.z*s;
                contact_agent[0].y = 0;
                contact_agent[0].z = -normal.x*s;

                contact_agent[1].x = normal.y*contact_agent[0].x;
                contact_agent[1].y = normal.z*contact_agent[0].x-normal.x*contact_agent[0].z;
                contact_agent[1].z = -normal.y*contact_agent[0].x;
            } else {
                const scalar s = (scalar)1.0/ real_sqrt(normal.z*normal.z+normal.y*normal.y);

                contact_agent[0].x = 0;
                contact_agent[0].y = -normal.z*s;
                contact_agent[0].z = normal.y*s;

                contact_agent[1].x = normal.y*contact_agent[0].z-normal.z*contact_agent[0].y;
                contact_agent[1].y = -normal.x*contact_agent[0].z;
                contact_agent[1].z = normal.x*contact_agent[0].y;
            }
            contact_to_world[0] = normal;
            contact_to_world[1] = contact_agent[0];
            contact_to_world[2] = contact_agent[1];
        }
    private:
        void resolve_impulse();
    };
}