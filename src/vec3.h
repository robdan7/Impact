//
// Created by Robin on 2021-05-18.
//
#pragma once
#include "defines.h"
#include <stdint.h>
namespace Impact {
    struct vec3 {
        scalar x,y,z;
        vec3() : x{0}, y{0}, z{0} {}
        vec3(scalar x, scalar y, scalar z) : x{x}, y{y}, z{z} {}
        vec3& operator=(scalar f) {
            x = f;
            y = f;
            z = f;
            return *this;
        }
        vec3& operator=(const vec3& other) {
            x = other.x;
            y = other.y;
            z = other.z;
            return *this;
        }
        scalar& operator[](uint8_t index) {
            return ((scalar*)this)[index];
        }
        const scalar& operator[](uint8_t index) const {
            return ((scalar*)this)[index];
        }
        scalar len2() {
            return x*x+y*y+z*z;
        }
        scalar len() {
            return real_sqrt(len2());
        }
        void normalize() {
            scalar len2 = this->len2();
            if (len2 != 1) {
                (*this) *= real_sqrt(len2)/1;
            }
        }
        vec3 cross(const vec3& other) const{
            return {y*other.z-z*other.y,z*other.x-x*other.z,x*other.y-y*other.x};
        }
        scalar dot(const vec3& other) const{
            return x*other.x+y*other.y+z*other.z;
        }

        vec3 operator*(scalar f) const{
            return {x*f,y*f,z*f};
        }

        vec3 operator*(const vec3& v) const{
            return {x*v.x,y*v.y,z*v.z};
        }
        vec3 operator+(scalar f) const{
            return {x+f,y+f,z+f};
        }

        vec3 operator+(const vec3& v) const{
            return {x+v.x,y+v.y,z+v.z};
        }

        vec3 operator-(scalar f) const{
            return {x-f,y-f,z-f};
        }

        vec3 operator-(const vec3& v) const{
            return {x-v.x,y-v.y,z-v.z};
        }

        vec3 operator/(const vec3& other) const{
            return {x/other.x,y/other.y,z/other.z};
        }

        vec3 operator/(scalar f) const{
            return {x/f,y/f,z/f};
        }


        vec3& operator*=(const vec3& other) {
            this->x *= other.x;
            this->y *= other.y;
            this->z *= other.z;
            return *this;
        }
        vec3& operator*=(scalar f) {
            x *= f;
            y *= f;
            z *= f;
            return *this;
        }
        vec3& operator-=(const vec3& other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }
        vec3& operator-=(scalar f) {
            x -= f;
            y -= f;
            z -= f;
            return *this;
        }
        vec3& operator+=(const vec3& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }
        vec3& operator+=(scalar f) {
            x += f;
            y += f;
            z += f;
            return *this;
        }
        vec3& operator/=(const vec3& other) {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            return *this;
        }
        vec3& operator/=(scalar f) {
            x /= f;
            y /= f;
            z /= f;
            return *this;
        }
    };
}