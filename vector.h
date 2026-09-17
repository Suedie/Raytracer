#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    float x, y, z;
} vector3;

vector3 vector_add(vector3 a, vector3 b);
vector3 vector_sub(vector3 a, vector3 b);
vector3 vector_scale(float sclar, vector3 v);
vector3 vector_dot_multiplication(vector3 a, vector3 b);

#endif