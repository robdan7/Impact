//
// Created by Robin on 2021-05-20.
//
#pragma once
#include "vec3.h"
#include "vec4.h"
#include "quaternion.h"
#include <stdint.h>
namespace Impact {
    struct mat3 {
    public:
        mat3() = default;
        mat3(scalar val) {
            this->col0[0] = val;
            this->col1[1] = val;
            this->col2[2] = val;
        }
        mat3& operator=(const quaternion& q);
        vec3& operator[](uint8_t index) {
            return ((vec3*)this)[index];
        }
        const vec3& operator[](uint8_t index) const {
            return ((vec3*)this)[index];
        }
        vec3 operator*(const vec4& vec);
        vec3 operator*(const vec3& vec);
        mat3 operator*(const mat3& other);
        mat3& operator*=(const scalar& f);
        mat3& operator+=(const scalar& f);
        mat3& operator-=(const scalar& f);
        mat3& operator/=(const scalar& f);
        mat3 inverse() const;
        scalar determinant() const;
        mat3 transpose() const;
    private:
        vec3 col0{};
        vec3 col1{};
        vec3 col2{};
    };

}