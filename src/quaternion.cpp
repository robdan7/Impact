//
// Created by Robin on 2021-05-23.
//
#include "quaternion.h"
#include "defines.h"
namespace Impact {

    void quaternion::normalize() {
        scalar d = r*r+i*i+k*k+j*j;
        if (d==0) {
            r = 1;
            return;
        }
        d=((scalar)1)/ real_sqrt(d);
        r*=d;
        i*=d;
        j*=d;
        k*=d;
    }

    quaternion quaternion::operator*(const quaternion &other) {
        quaternion q = *this;
        q*=*this;
        return q;
    }

    quaternion &quaternion::operator*=(const quaternion &other) {
        quaternion q = *this;
        r = q.r*other.r - q.i*other.i -q.j*other.j - q.k*other.k;
        i = q.r*other.i + q.i*other.r +q.j*other.k - q.k*other.j;
        j = q.r*other.j + q.j*other.r +q.k*other.i - q.i*other.k;
        k = q.r*other.k + q.k*other.r +q.i*other.j - q.j*other.i;
        return *this;
    }

    quaternion &quaternion::operator+=(const vec3 &rotation) {
        i += rotation.x*((scalar)0.5);
        j += rotation.y*((scalar)0.5);
        k += rotation.z*((scalar)0.5);
        return *this;
    }
}