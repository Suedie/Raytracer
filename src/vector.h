#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    float x, y, z;
} vector3;

vector3 vector3_add(vector3 a, vector3 b);
vector3 vector3_sub(vector3 a, vector3 b);
vector3 vector3_scale(float scalar, vector3 v);
float vector3_dot(vector3 a, vector3 b);
float vector3_length(vector3 a);
vector3 vector3_normalize(vector3 a);

#endif