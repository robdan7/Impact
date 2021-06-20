//
// Created by Robin on 2021-05-18.
//
#pragma once
#include "defines.h"
#include <stdint.h>
#include <initializer_list>
namespace Impact {
    struct vec4 {
        scalar x,y,z,w;
        vec4() : x{0}, y{0}, z{0}, w{0} {}
        vec4(scalar x, scalar y, scalar z, scalar w) : x{x}, y{y}, z{z}, w{w} {}
        scalar& operator[](uint8_t index) {
            return ((scalar*)this)[index];
        }
        const scalar& operator[](uint8_t index) const {
            return ((scalar*)this)[index];
        }
        vec4 operator*(const vec4& other) {
            return {x*other.x,y*other.y,z*other.z,w*other.w};
        }

        vec4 operator+(const vec4& other) {
            return {x+other.x,y+other.y,z+other.z,w+other.w};
        }

        vec4 operator-(const vec4& other) {
            return {x-other.x,y-other.y,z-other.z,w-other.w};
        }

        vec4 operator/(const vec4& other) {
            return {x/other.x,y/other.y,z/other.z,w/other.w};
        }
        vec4& operator*=(const vec4& other) {
            this->x *= other.x;
            this->y *= other.y;
            this->z *= other.z;
            this->w *= other.w;
            return *this;
        }
        vec4& operator*=(const scalar& f) {
            x*=f;
            y*=f;
            x*=f;
            z*=f;
            w*=f;
            return *this;
        }
        vec4& operator-=(const vec4& other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            w -= other.w;
            return *this;
        }
        vec4& operator-=(const scalar& f) {
            x-=f;
            y-=f;
            x-=f;
            z-=f;
            w-=f;
            return *this;
        }
        vec4& operator+=(const vec4& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
            return *this;
        }
        vec4& operator+=(const scalar& f) {
            x+=f;
            y+=f;
            x+=f;
            z+=f;
            w+=f;
            return *this;
        }
        vec4& operator/=(const vec4& other) {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            w /= other.w;
            return *this;
        }
        vec4& operator/=(const scalar& f) {
            x/=f;
            y/=f;
            x/=f;
            z/=f;
            w/=f;
            return *this;
        }
    };
}