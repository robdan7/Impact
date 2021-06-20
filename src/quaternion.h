//
// Created by Robin on 2021-05-20.
//
#pragma once
#include "defines.h"
#include "vec4.h"
#include "vec3.h"
namespace Impact {
    struct quaternion {
        union {
            struct {
                scalar r;
                scalar i;
                scalar j;
                scalar k;
            };
            scalar data[4];
        };
        void normalize();

        /**
         * Perform multiplication that is equal to first performing rotation starting with the rightmost argument.
         * @param other
         * @return
         */
        quaternion operator*(const quaternion& other);
        /**
         * Apply the rotation of this onto the other quaternion.
         * @param other
         * @return
         */
        quaternion& operator*=(const quaternion& other);
        /**
         * Apply an angular vector to a quaternion.
         * @param rotation
         * @return
         */
        quaternion& operator+=(const vec3& rotation);
    };
}