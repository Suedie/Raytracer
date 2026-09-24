#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    float x, y, z;
} vector3;

vector3 vector_add(vector3 a, vector3 b);
vector3 vector_sub(vector3 a, vector3 b);
vector3 vector_scale(float scalar, vector3 v);
float vector_dot(vector3 a, vector3 b);
float vector_length(vector3 a);
vector3 vector_normalize(vector3 a);

#endif