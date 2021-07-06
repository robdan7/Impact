//
// Created by Robin on 2021-05-27.
//
#include "impact.h"
#include "physics_object.h"
namespace Impact {
    Physics_world* current_world = nullptr;
    void apply_transform(Impact::mat4 &transform, const Impact::vec3 &position, const Impact::quaternion &rotation) {
        transform[0][0] = 1-2*rotation.j*rotation.j-2*rotation.k*rotation.k;
        transform[1][0] = 2*rotation.i*rotation.j -2*rotation.r*rotation.k;
        transform[2][0] = 2*rotation.i*rotation.k +2*rotation.r*rotation.j;
        transform[3][0] = position.x;

        transform[0][1] = 2*rotation.i*rotation.j +2*rotation.r*rotation.k;
        transform[1][1] = 1-2*rotation.i*rotation.i-2*rotation.k*rotation.k;
        transform[2][1] = 2*rotation.j*rotation.k -2*rotation.r*rotation.i;
        transform[3][1] = position.y;

        transform[0][2] = 2*rotation.i*rotation.k -2*rotation.r*rotation.j;
        transform[1][2] = 2*rotation.j*rotation.k +2*rotation.r*rotation.i;
        transform[2][2] = 1-2*rotation.i*rotation.i-2*rotation.j*rotation.j;
        transform[3][2] = position.z;
    }

    void transform_inertia(mat3 &world_inverse_inertia, const quaternion &q, const mat3 &local_inverse_inertia,
                           const mat4 &rotmat) {
        scalar t4 = rotmat[0][0]*local_inverse_inertia[0][0]+rotmat[1][0]*local_inverse_inertia[0][1]+rotmat[2][0]*local_inverse_inertia[0][2];
        scalar t9 = rotmat[0][0]*local_inverse_inertia[1][0]+rotmat[1][0]*local_inverse_inertia[1][1]+rotmat[2][0]*local_inverse_inertia[1][2];
        scalar t14 = rotmat[0][0]*local_inverse_inertia[2][0]+rotmat[1][0]*local_inverse_inertia[2][1]+rotmat[2][0]*local_inverse_inertia[2][2];
        scalar t28 = rotmat[0][1]*local_inverse_inertia[0][0]+rotmat[1][1]*local_inverse_inertia[0][1]+rotmat[2][1]*local_inverse_inertia[0][2];
        scalar t33 = rotmat[0][1]*local_inverse_inertia[1][0]+rotmat[1][1]*local_inverse_inertia[1][1]+rotmat[2][1]*local_inverse_inertia[1][2];
        scalar t38 = rotmat[0][1]*local_inverse_inertia[2][0]+rotmat[1][1]*local_inverse_inertia[2][1]+rotmat[2][1]*local_inverse_inertia[2][2];
        scalar t52 = rotmat[0][2]*local_inverse_inertia[0][0]+rotmat[1][2]*local_inverse_inertia[0][1]+rotmat[2][2]*local_inverse_inertia[0][2];
        scalar t57 = rotmat[0][2]*local_inverse_inertia[1][0]+rotmat[1][2]*local_inverse_inertia[1][1]+rotmat[2][2]*local_inverse_inertia[1][2];
        scalar t62 = rotmat[0][2]*local_inverse_inertia[2][0]+rotmat[1][2]*local_inverse_inertia[2][1]+rotmat[2][2]*local_inverse_inertia[2][2];

        world_inverse_inertia[0][0] = t4*rotmat[0][0]+t9*rotmat[1][0]+t14*rotmat[2][0];
        world_inverse_inertia[1][0] = t4*rotmat[0][1]+t9*rotmat[1][1]+t14*rotmat[2][1];
        world_inverse_inertia[2][0] = t4*rotmat[0][2]+t9*rotmat[1][2]+t14*rotmat[2][2];

        world_inverse_inertia[0][1] = t28*rotmat[0][0]+t33*rotmat[1][0]+t38*rotmat[2][0];
        world_inverse_inertia[1][1] = t28*rotmat[0][1]+t33*rotmat[1][1]+t38*rotmat[2][1];
        world_inverse_inertia[2][1] = t28*rotmat[0][2]+t33*rotmat[1][2]+t38*rotmat[2][2];

        world_inverse_inertia[0][2] = t52*rotmat[0][0]+t57*rotmat[1][0]+t62*rotmat[2][0];
        world_inverse_inertia[1][2] = t52*rotmat[0][1]+t57*rotmat[1][1]+t62*rotmat[2][1];
        world_inverse_inertia[2][2] = t52*rotmat[0][2]+t57*rotmat[1][2]+t62*rotmat[2][2];

    }

    private_ptr<Physics_object*> register_object(Physics_object *obj) {
        /// TODO Assert for nullptr
        return current_world->reg(obj);
    }

    void set_physics_world(Physics_world *world) {
        current_world = world;
    }

    void integrate(scalar duration) {
        /// TODO Assert
        current_world->integrate(duration);
    }

    void orthogonal_basis(const vec3 &x, vec3 &y, vec3 &z) {
        z = x.cross(y);
        if (z.len2() == (scalar)0) {
            scalar s = y[0];
            y[0] = -y[1];
            y[1] = y[2];
            y[2] = s;
            z = x.cross(y);
        }
        y = z.cross(x);

        y.normalize();
        z.normalize();
    }

    private_ptr<Physics_object*> Physics_world::reg(Physics_object *obj) {
        auto ID = this->m_physics_objects.push_entry(obj);
        return private_ptr<Physics_object*>(ID, (Container<Physics_object*>*)&this->m_physics_objects);
    }

    void Physics_world::integrate(scalar duration) {
        auto& packed = this->m_physics_objects.get_packed_set();
        for (std::size_t i = 0; i < packed.size(); ++i) {
            packed[i]->integrate(duration);
        }
    }

}
