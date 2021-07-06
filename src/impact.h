//
// Created by Robin on 2021-05-27.
//
#ifndef __IMPACT_H__
#define __IMPACT_H__
#include "mat4.h"
#include "mat3.h"
#include "mat34.h"
#include "vec3.h"
#include "vec4.h"
#include "quaternion.h"
#include "defines.h"
#include "tools/sparse_table.h"
#include "tools/ptr.h"
namespace Impact {

    struct test {
        void* operator->();

    };

    class Physics_object;
    /**
     * Apply a position and rotation to a 4x4 transform matrix.
     * @param transform
     * @param position
     * @param rotation
     */
    void apply_transform(mat4& transform, const vec3& position, const quaternion& rotation);
    void transform_inertia(mat3& world_inverse_inertia, const quaternion& q,const mat3& local_inverse_inertia, const mat4& rotmat);
    void orthogonal_basis(const vec3& x, vec3& y, vec3& z);
    void integrate(scalar duration);
    private_ptr<Physics_object*> register_object(Physics_object* obj);

    class Physics_world {
    public:
        Physics_world() = default;
        void integrate(scalar duration);
        private_ptr<Physics_object*> reg(Physics_object* obj);
    private:
        //Same_arena_allocator<1,uint8_t,Physics_object*> m_physics_objects;
        Sparse_stack<ptr_primitive,1,uint8_t,Physics_object*> m_physics_objects;
    };

    void set_physics_world(Physics_world* world);
}
#endif __IMPACT_H__
#include "physics_object.h"