//
// Created by Robin on 2021-05-20.
//
#include "mat3.h"
namespace Impact {
    vec3 mat3::operator*(const vec4 &vec) {
        return vec3();
    }

    vec3 mat3::operator*(const vec3 &vec) {
        return vec3();
    }

    mat3 mat3::operator*(const mat3 &other) {
        mat3 target(0);
        target[0][0] = (*this)[0][0]*other[0][0] + (*this)[1][0]*other[0][1] + (*this)[2][0]*other[0][2];
        target[1][0] = (*this)[0][0]*other[1][0] + (*this)[1][0]*other[1][1] + (*this)[2][0]*other[1][2];
        target[2][0] = (*this)[0][0]*other[2][0] + (*this)[1][0]*other[2][1] + (*this)[2][0]*other[2][2];

        target[0][1] = (*this)[0][1]*other[0][0] + (*this)[1][1]*other[0][1] + (*this)[2][1]*other[0][2];
        target[1][1] = (*this)[0][1]*other[1][0] + (*this)[1][1]*other[1][1] + (*this)[2][1]*other[1][2];
        target[2][1] = (*this)[0][1]*other[2][0] + (*this)[1][1]*other[2][1] + (*this)[2][1]*other[2][2];

        target[0][2] = (*this)[0][2]*other[0][0] + (*this)[1][2]*other[0][1] + (*this)[2][2]*other[0][2];
        target[1][2] = (*this)[0][2]*other[1][0] + (*this)[1][2]*other[1][1] + (*this)[2][2]*other[1][2];
        target[2][2] = (*this)[0][2]*other[2][0] + (*this)[1][2]*other[2][1] + (*this)[2][2]*other[2][2];

        target[0][3] = (*this)[0][3]*other[0][0] + (*this)[1][3]*other[0][1] + (*this)[2][3]*other[0][2];
        target[1][3] = (*this)[0][3]*other[1][0] + (*this)[1][3]*other[1][1] + (*this)[2][3]*other[1][2];
        target[2][3] = (*this)[0][3]*other[2][0] + (*this)[1][3]*other[2][1] + (*this)[2][3]*other[2][2];

        return target;
    }


    mat3 mat3::inverse() const{
        mat3 target;

        scalar A00 = col1[1]*col2[2]-col2[1]*col1[2];
        scalar A01 = col0[1]*col2[2]-col2[1]*col0[2];
        scalar A02 = col0[1]*col1[2]-col1[1]*col0[2];

        scalar det = col0[0]*A00-col1[0]*A01+col2[0]*A02;

        if (det == 0) return target;

        target[0][0] = A00;
        target[0][1] = -A01;
        target[0][2] = A02;

        target[1][0] = -(col1[0]*col2[2]-col2[0]*col1[2]);
        target[1][1] = col0[0]*col2[2]-col2[0]*col0[2];
        target[1][2] = -(col0[0]*col1[2]-col1[0]*col0[2]);

        target[2][0] = col1[0]*col2[1]-col2[0]*col1[1];
        target[2][1] = -(col0[0]*col2[1]-col2[0]*col0[1]);
        target[2][2] = col0[0]*col1[1]-col1[0]*col0[1];


        /*
        scalar t0 = col1[1]*col2[2]-col2[1]*col1[2];
        scalar t1 = col0[1]*col2[2]-col2[1]*col0[2];
        scalar t2 = col0[1]*col1[2]-col1[1]*col0[2];

        scalar det = col0[0]*t0-col1[0]*t1+col2[0]*t2;

        if (det == 0) return target;

        scalar det_inv = ((scalar)1)/det;

  

        target[0][0] = t0*det_inv;
        target[0][1] = -t1*det_inv;
        target[0][2] = t2*det_inv;
        target[1][0] = -(col1[0]*col2[2]-col2[0]*col1[2]);
        target[1][1] = (col0[0]*col2[2]-col2[0]*col0[2]);
        target[1][2] = -(col0[0]*col1[2]-col1[0]*col0[2]);
        target[2][0] = (col1[0]*col2[1]-col2[0]*col0[1]);
        target[2][1] = -(col0[0]*col2[1]-col2[0]*col0[1]);
        target[2][2] = (col0[0]*col1[1]-col1[0]*col0[1]);
        target*=det_inv;
*/
        return target;
    }

    scalar mat3::determinant() const {
        return  col0[0]*(col1[1]*col2[2]-col2[1]*col1[2])-col1[0]*(col0[1]*col2[2]-col2[1]*col0[2])+col2[0]*(col0[1]*col1[2]-col1[1]*col0[2]);
    }

    mat3 mat3::transpose() const{
        mat3 target(0);
        target[0][0] = (*this)[0][0];
        target[0][1] = (*this)[1][0];
        target[0][2] = (*this)[2][0];

        target[1][0] = (*this)[0][1];
        target[1][1] = (*this)[1][1];
        target[1][2] = (*this)[2][1];

        target[2][0] = (*this)[0][2];
        target[2][1] = (*this)[1][2];
        target[2][2] = (*this)[2][2];

        return target;
    }

    mat3& mat3::operator=(const quaternion &q) {
        col0[0] = 1-2*(q.j*q.j+q.k*q.k);
        col0[1] = 2*(q.i*q.j+q.k*q.r);
        col0[2] = 2*(q.i*q.k - q.j*q.r);
        col1[0] = 2*(q.i*q.j - q.k*q.r);
        col1[1] = 1 - 2*(q.i*q.i  + q.k*q.k);
        col1[2] = 2*(q.j*q.k + q.i*q.r);
        col2[0] = 2*(q.i*q.k + q.j*q.r);
        col2[1] = 2*(q.j*q.k - q.i*q.r);
        col2[2] = 1 - 2*(q.i*q.i  + q.j*q.j);
        return *this;
    }

    mat3 &mat3::operator/=(const scalar &f) {
        col0/=f;
        col1/=f;
        col2/=f;
        return *this;
    }

    mat3 &mat3::operator*=(const scalar &f) {
        col0*=f;
        col1*=f;
        col2*=f;
        return *this;
    }

    mat3 &mat3::operator+=(const scalar &f) {
        col0+=f;
        col1+=f;
        col2+=f;
        return *this;
    }

    mat3 &mat3::operator-=(const scalar &f) {
        col0-=f;
        col1-=f;
        col2-=f;
        return *this;
    }
}

