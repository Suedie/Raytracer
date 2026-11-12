#ifndef MATRIX_H
#define MATRIX_H

#include "vector3.h"

typedef struct {
    vector3 right;
    vector3 up;
    vector3 forward;
} matrix3x3;

matrix3x3 matrix_vector_mult(matrix3x3 a, vector3 b);

#endif