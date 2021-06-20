//
// Created by Robin on 2021-05-27.
//
#pragma once
#include "vec3.h"
#include "mat34.h"
#include "defines.h"
namespace Impact {
    class Primitive {
        //ptr rigidbody;
        //mat34 transform_offset;
        //Primitive(ptr body, const mat34& transform) : rigidbody(body), transform_offset(transform) {}
    };
    class BoundingSphere  {
        scalar radius;
        vec3 position;
    };
    class Boundingbox {
    public:
        vec3 half_axis;
        vec3 position;
        bool axis_align;
        Boundingbox(const vec3& position, const vec3& half_axis, bool axis_align = true) : position(position),half_axis(half_axis), axis_align(axis_align){

        }

        bool aabb_intersect(const Boundingbox& other) const{
            auto other_max = other.position+other.half_axis;
            auto other_min = other.position-other.half_axis;

            auto min = this->position-this->half_axis;
            auto max = this->position+this->half_axis;

            return (other_min.x <= max.x && other_max.x >= min.x) &&
                    (other_min.y <= max.y && other_max.y >= min.y) &&
                    (other_min.z <= max.z && other_max.z >= min.z);
        }

    };

}