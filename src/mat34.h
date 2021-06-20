//
// Created by Robin on 2021-05-18.
//
#pragma once
#include "vec3.h"
#include "vec4.h"
#include "defines.h"
#include "quaternion.h"
#include <stdint.h>
namespace Impact {
    struct mat34 {
    public:
        mat34(scalar f) {
            col0[0] = f;
            col1[1] = f;
            col2[2] = f;
        }
        void from_rotation(const quaternion& q, const vec3& pos);
        vec3& operator[](uint8_t index) {
            return ((vec3*)this)[index];
        }
        const vec3& operator[](uint8_t index) const {
            return ((vec3*)this)[index];
        }
        vec4 operator*(const vec4& vec) const;
        vec3 operator*(const vec3& vec) const;
        mat34 operator*(const mat34& other) const;
        mat34& operator*=(const scalar& f);
        mat34& operator+=(const scalar& f);
        mat34& operator-=(const scalar& f);
        mat34& operator/=(const scalar& f);
        mat34 inverse();
        scalar determinant();
    private:
        vec3 col0{};
        vec3 col1{};
        vec3 col2{};
        vec3 col3{};
    };
}