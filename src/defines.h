//
// Created by Robin on 2021-05-18.
//
#pragma once
#include <math.h>
#include "stdint.h"
namespace Impact {
    typedef float scalar;
    #define real_sqrt(scalar) sqrtf(scalar)
    #define real_pow(scalar,factor) powf(scalar,factor)
    #define real_abs(scalar) abs(scalar)
    #define EPSILON (0)
}