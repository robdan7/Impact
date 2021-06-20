//
// Created by Robin on 2021-05-20.
//
#include "mat34.h"

Impact::vec4 Impact::mat34::operator*(const Impact::vec4 &vec) const{
    return {vec.x*col0[0]+vec.y*col1[0]+vec.z*col2[0]+vec.w*col3[0],
            vec.x*col0[1]+vec.y*col1[1]+vec.z*col2[1]+vec.w*col3[1],
            vec.x*col0[2]+vec.y*col1[2]+vec.z*col2[2]+vec.w*col3[2],vec.w};
}

Impact::vec3 Impact::mat34::operator*(const Impact::vec3 &vec) const{
    return {vec.x*col0[0]+vec.y*col1[0]+vec.z*col2[0]+col3[0],
            vec.x*col0[1]+vec.y*col1[1]+vec.z*col2[1]+col3[1],
            vec.x*col0[2]+vec.y*col1[2]+vec.z*col2[2]+col3[2]};
}

Impact::mat34 Impact::mat34::operator*(const Impact::mat34 &other) const{
    mat34 target(0);
    target[0][0] = (*this)[0][0]*other[0][0] + (*this)[1][0]*other[0][1] + (*this)[2][0]*other[0][2];
    target[1][0] = (*this)[0][0]*other[1][0] + (*this)[1][0]*other[1][1] + (*this)[2][0]*other[1][2];
    target[2][0] = (*this)[0][0]*other[2][0] + (*this)[1][0]*other[2][1] + (*this)[2][0]*other[2][2];
    target[3][0] = (*this)[0][0]*other[3][0] + (*this)[1][0]*other[3][1] + (*this)[2][0]*other[3][2]+(*this)[3][0];

    target[0][1] = (*this)[0][1]*other[0][0] + (*this)[1][1]*other[0][1] + (*this)[2][1]*other[0][2];
    target[1][1] = (*this)[0][1]*other[1][0] + (*this)[1][1]*other[1][1] + (*this)[2][1]*other[1][2];
    target[2][1] = (*this)[0][1]*other[2][0] + (*this)[1][1]*other[2][1] + (*this)[2][1]*other[2][2];
    target[3][1] = (*this)[0][1]*other[3][0] + (*this)[1][1]*other[3][1] + (*this)[2][1]*other[3][2]+(*this)[3][1];

    target[0][2] = (*this)[0][2]*other[0][0] + (*this)[1][2]*other[0][1] + (*this)[2][2]*other[0][2];
    target[1][2] = (*this)[0][2]*other[1][0] + (*this)[1][2]*other[1][1] + (*this)[2][2]*other[1][2];
    target[2][2] = (*this)[0][2]*other[2][0] + (*this)[1][2]*other[2][1] + (*this)[2][2]*other[2][2];
    target[3][2] = (*this)[0][2]*other[3][0] + (*this)[1][2]*other[3][1] + (*this)[2][2]*other[3][2]+(*this)[3][2];
    return target;
}

void Impact::mat34::from_rotation(const Impact::quaternion &q, const Impact::vec3 &pos) {
    col0[0] = 1-2*(q.j*q.j+q.k*q.k);
    col0[1] = 2*(q.i*q.j+q.k*q.r);
    col0[2] = 2*(q.i*q.k - q.j*q.r);
    col1[0] = 2*(q.i*q.j - q.k*q.r);
    col1[1] = 1 - 2*(q.i*q.i  + q.k*q.k);
    col1[2] = 2*(q.j*q.k + q.i*q.r);
    col2[0] = 2*(q.i*q.k + q.j*q.r);
    col2[1] = 2*(q.j*q.k - q.i*q.r);
    col2[2] = 1 - 2*(q.i*q.i  + q.j*q.j);
    col3[0] = pos.x;
    col3[1] = pos.y;
    col3[2] = pos.z;
}

Impact::mat34 Impact::mat34::inverse() {
    mat34 target(0);

    scalar det = determinant();
    if (det == 0) return target;

    det = ((scalar)1.0)/det;

    target[0][0] = col1[1]*col2[2]-col2[1]*col1[1];
    target[1][0] = col0[1]*col2[2]-col2[1]*col0[2];
    target[2][0] = col0[1]*col1[2]-col1[1]*col0[2];
    target[3][0] = 0;

    target[0][1] = col1[0]*(col2[2])-col2[0]*(col1[0]);
    target[1][1] = col0[0]*(col2[2])-col2[0]*(col0[2]);
    target[2][1] = col0[0]*(col1[2])-col1[0]*(col0[2]);
    target[3][1] = 0;

    target[0][2] = col1[0]*(col2[1]*col3[3]-col3[1]*col2[3])-col2[0]*(col1[0]*col3[3]-col3[0]*col1[3])+col3[0]*(col1[0]*col2[3]-col3[0]*col1[3]);
    target[1][2] = col0[0]*(col2[1]*col3[3]-col3[1]*col2[3])-col2[0]*(col0[1]*col3[3]-col3[1]*col0[3])+col3[0]*(col0[1]*col2[3]-col2[1]*col0[3]);
    target[2][2] = col0[0]*(col1[1]*col3[3]-col3[1]*col1[3])-col1[0]*(col0[1]*col3[3]-col3[1]*col0[3])+col3[0]*(col0[1]*col1[3]-col1[1]*col0[3]);
    target[3][2] = 0;


    target *=det;
    return target;
}

Impact::scalar Impact::mat34::determinant() {
    scalar A00 = col1[1]*col2[2]-col2[1]*col1[1];
    scalar A01 = col0[1]*col2[2]-col2[1]*col0[2];
    scalar A02 = col0[1]*col1[2]-col1[1]*col0[2];

    return col0[0]*A00-col1[0]*A01+col2[0]*A02;
}

Impact::mat34 &Impact::mat34::operator*=(const Impact::scalar &f) {
    col0*=f;
    col1*=f;
    col2*=f;
    col3*=f;
    return *this;
}

Impact::mat34 &Impact::mat34::operator+=(const Impact::scalar &f) {
    col0+=f;
    col1+=f;
    col2+=f;
    col3+=f;
    return *this;
}

Impact::mat34 &Impact::mat34::operator-=(const Impact::scalar &f) {
    col0-=f;
    col1-=f;
    col2-=f;
    col3-=f;
    return *this;
}

Impact::mat34 &Impact::mat34::operator/=(const Impact::scalar &f) {
    col0/=f;
    col1/=f;
    col2/=f;
    col3/=f;
    return *this;
}
