//
// Created by Robin on 2021-05-18.
//
#pragma once
#include "vec4.h"
#include "mat34.h"
#include "defines.h"
#include <stdint.h>
#include "quaternion.h"
namespace Impact {
    class mat4 {
    public:
        mat4(scalar val) {
            this->col0[0] = val;
            this->col1[1] = val;
            this->col2[2] = val;
            this->col3[3] = val;
        }
        mat4() = default;
        void set_rotation(const quaternion& q);
        void set_translation(const vec4& v);
        void translate(const vec3& v);
        void translate(const vec4& v);
        vec4& operator[](uint8_t index) {
            return ((vec4*)this)[index];
        }
        const vec4& operator[](uint8_t index) const {
            return ((vec4*)this)[index];
        }
        vec4 operator*(const vec4& vec);
        vec3 operator*(const vec3& vec);
        mat4 operator*(const mat4& other);
        mat4 operator*(const mat34& other);
        mat4& operator*=(const scalar& f);
        mat4& operator+=(const scalar& f);
        mat4& operator-=(const scalar& f);
        mat4& operator/=(const scalar& f);
        scalar determinant();
        mat4 inverse();
        mat4 transpose();
    private:
        vec4 col0{};
        vec4 col1{};
        vec4 col2{};
        vec4 col3{};
    };
}