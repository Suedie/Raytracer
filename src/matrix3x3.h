#ifndef MATRIX_H
#define MATRIX_H

#include "vector3.h"

typedef struct {
    vector3 ma;
    vector3 mb;
    vector3 mc;
} matrix3x3;

matrix3x3 matrix_vector_mult(matrix3x3 a, vector3 b);

#endif