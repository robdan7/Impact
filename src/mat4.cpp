//
// Created by Robin on 2021-05-18.
//
#include "mat4.h"
namespace Impact {

    mat4 mat4::operator*(const mat4 &other) {
        mat4 target(0);
        target[1][0] = (*this)[0][0]*other[1][0] + (*this)[1][0]*other[1][1] + (*this)[2][0]*other[1][2] + (*this)[3][0]*other[1][3];
        target[0][0] = (*this)[0][0]*other[0][0] + (*this)[1][0]*other[0][1] + (*this)[2][0]*other[0][2] + (*this)[3][0]*other[0][3];
        target[2][0] = (*this)[0][0]*other[2][0] + (*this)[1][0]*other[2][1] + (*this)[2][0]*other[2][2] + (*this)[3][0]*other[2][3];
        target[3][0] = (*this)[0][0]*other[3][0] + (*this)[1][0]*other[3][1] + (*this)[2][0]*other[3][2] + (*this)[3][0]*other[3][3];

        target[1][1] = (*this)[0][0]*other[1][1] + (*this)[1][1]*other[1][1] + (*this)[2][1]*other[1][2] + (*this)[3][1]*other[1][3];
        target[0][1] = (*this)[0][0]*other[0][1] + (*this)[1][1]*other[0][1] + (*this)[2][1]*other[0][2] + (*this)[3][1]*other[0][3];
        target[2][1] = (*this)[0][0]*other[2][1] + (*this)[1][1]*other[2][1] + (*this)[2][1]*other[2][2] + (*this)[3][1]*other[2][3];
        target[3][1] = (*this)[0][0]*other[3][1] + (*this)[1][1]*other[3][1] + (*this)[2][1]*other[3][2] + (*this)[3][1]*other[3][3];

        target[0][2] = (*this)[0][2]*other[0][0] + (*this)[1][2]*other[0][1] + (*this)[2][2]*other[0][2] + (*this)[3][2]*other[0][3];
        target[1][2] = (*this)[0][2]*other[1][0] + (*this)[1][2]*other[1][1] + (*this)[2][2]*other[1][2] + (*this)[3][2]*other[1][3];
        target[2][2] = (*this)[0][2]*other[2][0] + (*this)[1][2]*other[2][1] + (*this)[2][2]*other[2][2] + (*this)[3][2]*other[2][3];
        target[3][2] = (*this)[0][2]*other[3][0] + (*this)[1][2]*other[3][1] + (*this)[2][2]*other[3][2] + (*this)[3][2]*other[3][3];

        target[1][3] = (*this)[0][3]*other[1][0] + (*this)[1][3]*other[1][1] + (*this)[2][3]*other[1][2] + (*this)[3][3]*other[1][3];
        target[0][3] = (*this)[0][3]*other[0][0] + (*this)[1][3]*other[0][1] + (*this)[2][3]*other[0][2] + (*this)[3][3]*other[0][3];
        target[2][3] = (*this)[0][3]*other[2][0] + (*this)[1][3]*other[2][1] + (*this)[2][3]*other[2][2] + (*this)[3][3]*other[2][3];
        target[3][3] = (*this)[0][3]*other[3][0] + (*this)[1][3]*other[3][1] + (*this)[2][3]*other[3][2] + (*this)[3][3]*other[3][3];
        return target;
    }

    mat4 mat4::operator*(const mat34 &other) {
        mat4 target(0);
        target[0][0] = (*this)[0][0]*other[0][0] + (*this)[1][0]*other[0][1] + (*this)[2][0]*other[0][2]+(*this)[3][0]*other[0][3];
        target[1][0] = (*this)[0][0]*other[1][0] + (*this)[1][0]*other[1][1] + (*this)[2][0]*other[1][2]+(*this)[3][0]*other[1][3];
        target[2][0] = (*this)[0][0]*other[2][0] + (*this)[1][0]*other[2][1] + (*this)[2][0]*other[2][2]+(*this)[3][0]*other[2][3];
        target[3][0] = (*this)[0][0]*other[3][0] + (*this)[1][0]*other[3][1] + (*this)[2][0]*other[3][2]+(*this)[3][0]*other[3][3];

        target[0][1] = (*this)[0][1]*other[0][0] + (*this)[1][1]*other[0][1] + (*this)[2][1]*other[0][2]+(*this)[3][1]*other[0][3];
        target[1][1] = (*this)[0][1]*other[1][0] + (*this)[1][1]*other[1][1] + (*this)[2][1]*other[1][2]+(*this)[3][1]*other[1][3];
        target[2][1] = (*this)[0][1]*other[2][0] + (*this)[1][1]*other[2][1] + (*this)[2][1]*other[2][2]+(*this)[3][1]*other[2][3];
        target[3][1] = (*this)[0][1]*other[3][0] + (*this)[1][1]*other[3][1] + (*this)[2][1]*other[3][2]+(*this)[3][1]*other[3][3];

        target[0][2] = (*this)[0][2]*other[0][0] + (*this)[1][2]*other[0][1] + (*this)[2][2]*other[0][2]+(*this)[3][2]*other[0][3];
        target[1][2] = (*this)[0][2]*other[1][0] + (*this)[1][2]*other[1][1] + (*this)[2][2]*other[1][2]+(*this)[3][2]*other[1][3];
        target[2][2] = (*this)[0][2]*other[2][0] + (*this)[1][2]*other[2][1] + (*this)[2][2]*other[2][2]+(*this)[3][2]*other[2][3];
        target[3][2] = (*this)[0][2]*other[3][0] + (*this)[1][2]*other[3][1] + (*this)[2][2]*other[3][2]+(*this)[3][2]*other[3][3];

        target[0][3] = (*this)[0][3]*other[0][0] + (*this)[1][3]*other[0][1] + (*this)[2][3]*other[0][2]+(*this)[3][3]*other[0][3];
        target[1][3] = (*this)[0][3]*other[1][0] + (*this)[1][3]*other[1][1] + (*this)[2][3]*other[1][2]+(*this)[3][3]*other[0][3];
        target[2][3] = (*this)[0][3]*other[2][0] + (*this)[1][3]*other[2][1] + (*this)[2][3]*other[2][2]+(*this)[3][3]*other[0][3];
        target[3][3] = (*this)[0][3]*other[3][0] + (*this)[1][3]*other[3][1] + (*this)[2][3]*other[3][2]+(*this)[3][3]*other[0][3];
        return target;
    }

    vec3 mat4::operator*(const vec3 &vec) {
        return {col0[0]*vec.x+col1[0]*vec.y+col2[0]*vec.z+col3[0],
                col0[1]*vec.x+col1[1]*vec.y+col2[1]*vec.z+col3[1],
                col0[2]*vec.x+col1[2]*vec.y+col2[2]*vec.z+col3[2]};
    }

    vec4 mat4::operator*(const vec4 &vec) {
        return {col0[0]*vec.x+col1[0]*vec.y+col2[0]*vec.z+col3[0]*vec.w,
                col0[1]*vec.x+col1[1]*vec.y+col2[1]*vec.z+col3[1]*vec.w,
                col0[2]*vec.x+col1[2]*vec.y+col2[2]*vec.z+col3[2]*vec.w,
                col0[3]*vec.x+col1[3]*vec.y+col2[3]*vec.z+col3[3]*vec.w};
    }

    mat4 mat4::transpose() {
        mat4 target(0);
        target[0][0] = (*this)[0][0];
        target[0][1] = (*this)[1][0];
        target[0][2] = (*this)[2][0];
        target[0][3] = (*this)[3][0];

        target[1][0] = (*this)[0][1];
        target[1][1] = (*this)[1][1];
        target[1][2] = (*this)[2][1];
        target[1][3] = (*this)[3][1];

        target[2][0] = (*this)[0][2];
        target[2][1] = (*this)[1][2];
        target[2][2] = (*this)[2][2];
        target[2][3] = (*this)[3][2];

        target[3][0] = (*this)[0][3];
        target[3][1] = (*this)[1][3];
        target[3][2] = (*this)[2][3];
        target[3][3] = (*this)[3][3];



        return target;
    }

    scalar mat4::determinant() {
        scalar A00 = col1[1]*(col2[2]*col3[3]-col3[2]*col2[3])      -col2[1]*(col1[2]*col3[3]-col3[2]*col1[3])      +col3[1]*(col1[2]*col2[3]-col2[2]*col1[3]);
        scalar A01 = col0[1]*(col2[2]*col3[3]-col3[2]*col2[3])      -col2[1]*(col0[2]*col3[3]-col3[2]*col0[3])      +col3[1]*(col0[2]*col2[3]-col2[2]*col0[3]);
        scalar A02 = col0[1]*(col1[2]*col3[3]-col3[2]*col1[3])      -col1[1]*(col0[2]*col3[3]-col3[2]*col0[3])      +col3[1]*(col0[2]*col1[3]-col1[2]*col0[3]);
        scalar A03 = col0[1]*(col1[2]*col2[3]-col2[2]*col1[3])      -col1[1]*(col0[2]*col2[3]-col2[2]*col0[3])      +col2[1]*(col0[2]*col1[3]-col1[2]*col0[3]);
        return col0[0]*A00-col1[0]*A01+col2[0]*A02+col3[0]*A03;
    }

    void mat4::set_rotation(const quaternion &q) {
        col0[0] = 1-2*(q.j*q.j+q.k*q.k);
        col0[1] = 2*(q.i*q.j+q.k*q.r);
        col0[2] = 2*(q.i*q.k - q.j*q.r);

        col1[0] = 2*(q.i*q.j - q.k*q.r);
        col1[1] = 1 - 2*(q.i*q.i  + q.k*q.k);
        col1[2] = 2*(q.j*q.k + q.i*q.r);

        col2[0] = 2*(q.i*q.k + q.j*q.r);
        col2[1] = 2*(q.j*q.k - q.i*q.r);
        col2[2] = 1 - 2*(q.i*q.i  + q.j*q.j);
    }

    mat4 mat4::inverse() {
        mat4 target(0);

        scalar A00 = col1[1]*(col2[2]*col3[3]-col3[2]*col2[3])      -col2[1]*(col1[2]*col3[3]-col3[2]*col1[3])      +col3[1]*(col1[2]*col2[3]-col2[2]*col1[3]);
        scalar A01 = col0[1]*(col2[2]*col3[3]-col3[2]*col2[3])      -col2[1]*(col0[2]*col3[3]-col3[2]*col0[3])      +col3[1]*(col0[2]*col2[3]-col2[2]*col0[3]);
        scalar A02 = col0[1]*(col1[2]*col3[3]-col3[2]*col1[3])      -col1[1]*(col0[2]*col3[3]-col3[2]*col0[3])      +col3[1]*(col0[2]*col1[3]-col1[2]*col0[3]);
        scalar A03 = col0[1]*(col1[2]*col2[3]-col2[2]*col1[3])      -col1[1]*(col0[2]*col2[3]-col2[2]*col0[3])      +col2[1]*(col0[2]*col1[3]-col1[2]*col0[3]);

        scalar det = col0[0]*A00-col1[0]*A01+col2[0]*A02+col3[0]*A03;
        if (det == 0) return target;

        det = ((scalar)1.0)/det;

        target[0][0] = A00;
        target[0][1] = -A01;
        target[0][2] = A02;
        target[0][3] = -A03;

        target[1][0] = -(col1[0]*(col2[2]*col3[3]-col3[2]*col2[3])      -col2[0]*(col1[2]*col3[3]-col3[2]*col1[3])      +col3[0]*(col1[2]*col2[3]-col2[2]*col1[3]));
        target[1][1] = col0[0]*(col2[2]*col3[3]-col3[2]*col2[3])      -col2[0]*(col0[2]*col3[3]-col3[2]*col0[3])      +col3[0]*(col0[2]*col2[3]-col2[2]*col0[3]);
        target[1][2] = -(col0[0]*(col1[2]*col3[3]-col3[2]*col1[3])      -col1[0]*(col0[2]*col3[3]-col3[2]*col0[3])      +col3[0]*(col0[2]*col1[3]-col1[2]*col0[3]));
        target[1][3] = col0[0]*(col1[2]*col2[3]-col2[2]*col1[3])      -col1[0]*(col0[2]*col2[3]-col2[2]*col0[3])      +col2[0]*(col0[2]*col1[3]-col1[2]*col0[3]);

        target[2][0] = col1[0]*(col2[1]*col3[3]-col3[1]*col2[3])      -col2[0]*(col1[1]*col3[3]-col3[1]*col1[3])      +col3[0]*(col1[1]*col2[3]-col2[1]*col1[3]);
        target[2][1] = -(col0[0]*(col2[1]*col3[3]-col3[1]*col2[3])      -col2[0]*(col0[1]*col3[3]-col3[1]*col0[3])      +col3[0]*(col0[1]*col2[3]-col2[1]*col0[3]));
        target[2][2] = col0[0]*(col1[1]*col3[3]-col3[1]*col1[3])      -col1[0]*(col0[1]*col3[3]-col3[1]*col0[3])      +col3[0]*(col0[1]*col1[3]-col1[1]*col0[3]);
        target[2][3] = -(col0[0]*(col1[1]*col2[3]-col2[1]*col1[3])      -col1[0]*(col0[1]*col2[3]-col2[1]*col0[3])      +col2[0]*(col0[1]*col1[3]-col1[1]*col0[3]));

        target[3][0] = -(col1[0]*(col2[1]*col3[2]-col3[1]*col2[2])      -col2[0]*(col1[1]*col3[2]-col3[1]*col1[2])      +col3[0]*(col1[1]*col2[2]-col2[1]*col1[2]));
        target[3][1] = col0[0]*(col2[1]*col3[2]-col3[1]*col2[2])      -col2[0]*(col0[1]*col3[2]-col3[1]*col0[2])      +col3[0]*(col0[1]*col2[2]-col2[1]*col0[2]);
        target[3][2] = -(col0[0]*(col1[1]*col3[2]-col3[1]*col1[2])      -col1[0]*(col0[1]*col3[2]-col3[1]*col0[2])      +col3[0]*(col0[1]*col1[2]-col1[1]*col0[2]));
        target[3][3] = col0[0]*(col1[1]*col2[2]-col2[1]*col1[2])      -col1[0]*(col0[1]*col2[2]-col2[1]*col0[2])      +col2[0]*(col0[1]*col1[2]-col1[1]*col0[2]);



        /*
        target[0][0] = col1[1]*(col2[2]*col3[3]-col3[2]*col2[3])-col2[1]*(col1[1]*col3[3]-col3[1]*col1[3])+col3[1]*(col1[1]*col2[3]-col3[1]*col1[3]);
        target[1][0] = col0[1]*(col2[2]*col3[3]-col3[2]*col2[3])-col2[1]*(col0[2]*col3[3]-col3[2]*col0[3])+col3[1]*(col0[2]*col2[3]-col2[2]*col0[3]);
        target[2][0] = col0[1]*(col1[2]*col3[3]-col3[2]*col1[3])-col1[1]*(col0[2]*col3[3]-col3[2]*col0[3])+col3[1]*(col0[2]*col1[3]-col1[2]*col0[3]);
        target[3][0] = col0[1]*(col1[2]*col2[3]-col2[2]*col1[3])-col1[1]*(col0[2]*col2[3]-col2[2]*col0[3])+col2[1]*(col0[2]*col1[3]-col1[2]*col0[3]);

        target[0][1] = col1[0]*(col2[2]*col3[3]-col3[2]*col2[3])-col2[0]*(col1[0]*col3[3]-col3[0]*col1[3])+col3[0]*(col1[0]*col2[3]-col3[0]*col1[3]);
        target[1][1] = col0[0]*(col2[2]*col3[3]-col3[2]*col2[3])-col2[0]*(col0[2]*col3[3]-col3[2]*col0[3])+col3[0]*(col0[2]*col2[3]-col2[2]*col0[3]);
        target[2][1] = col0[0]*(col1[2]*col3[3]-col3[2]*col1[3])-col1[0]*(col0[2]*col3[3]-col3[2]*col0[3])+col3[0]*(col0[2]*col1[3]-col1[2]*col0[3]);
        target[3][1] = col0[0]*(col1[2]*col2[3]-col2[2]*col1[3])-col1[0]*(col0[2]*col2[3]-col2[2]*col0[3])+col2[0]*(col0[2]*col1[3]-col1[2]*col0[3]);

        target[0][2] = col1[0]*(col2[1]*col3[3]-col3[1]*col2[3])-col2[0]*(col1[0]*col3[3]-col3[0]*col1[3])+col3[0]*(col1[0]*col2[3]-col3[0]*col1[3]);
        target[1][2] = col0[0]*(col2[1]*col3[3]-col3[1]*col2[3])-col2[0]*(col0[1]*col3[3]-col3[1]*col0[3])+col3[0]*(col0[1]*col2[3]-col2[1]*col0[3]);
        target[2][2] = col0[0]*(col1[1]*col3[3]-col3[1]*col1[3])-col1[0]*(col0[1]*col3[3]-col3[1]*col0[3])+col3[0]*(col0[1]*col1[3]-col1[1]*col0[3]);
        target[3][2] = col0[0]*(col1[1]*col2[3]-col2[1]*col1[3])-col1[0]*(col0[1]*col2[3]-col2[1]*col0[3])+col2[0]*(col0[1]*col1[3]-col1[1]*col0[3]);

        target[0][3] = col1[0]*(col2[1]*col3[2]-col3[1]*col2[2])-col2[0]*(col1[0]*col3[2]-col3[0]*col1[2])+col3[0]*(col1[0]*col2[2]-col3[0]*col1[2]);
        target[1][3] = col0[0]*(col2[1]*col3[2]-col3[1]*col2[2])-col2[0]*(col0[1]*col3[2]-col3[1]*col0[2])+col3[0]*(col0[1]*col2[2]-col2[1]*col0[2]);
        target[2][3] = col0[0]*(col1[1]*col3[2]-col3[1]*col1[2])-col1[0]*(col0[1]*col3[2]-col3[1]*col0[2])+col3[0]*(col0[1]*col1[2]-col1[1]*col0[2]);
        target[3][3] = col0[0]*(col1[1]*col2[2]-col2[1]*col1[2])-col1[0]*(col0[1]*col2[2]-col2[1]*col0[2])+col2[0]*(col0[1]*col1[2]-col1[1]*col0[2]);
         */
        target *=det;
        return target;
    }

    mat4 &mat4::operator*=(const scalar &f) {
        col0*=f;
        col1*=f;
        col2*=f;
        col3*=f;
        return *this;
    }

    mat4 &mat4::operator+=(const scalar &f) {
        col0+=f;
        col1+=f;
        col2+=f;
        col3+=f;
        return *this;
    }

    mat4 &mat4::operator-=(const scalar &f) {
        col0-=f;
        col1-=f;
        col2-=f;
        col3-=f;
        return *this;
    }

    mat4 &mat4::operator/=(const scalar &f) {
        col0 /= f;
        col1 /= f;
        col2 /= f;
        col3 /= f;
        return *this;
    }

    void mat4::set_translation(const vec4 &v) {
        col3 = v;
    }

    void mat4::translate(const vec3 &v) {
        this->col3.x += v.x;
        this->col3.y += v.y;
        this->col3.z += v.z;
    }

    void mat4::translate(const vec4 &v) {
        this->col3.x += v.x;
        this->col3.y += v.y;
        this->col3.z += v.z;
        this->col3.w += v.w;
    }
}
