#include "vector.h"
#include "math.h"
#include <math.h>

vector3 vector_add(vector3 a, vector3 b) {
    float x = a.x + b.x;
    float y = a.y + b.y;
    float z = a.z + b.z;

    return (vector3) {x, y, z};
}

vector3 vector_sub(vector3 a, vector3 b) {
    float x = a.x - b.x;
    float y = a.y - b.y;
    float z = a.z - b.z;

    return (vector3) {x, y, z};
}

vector3 vector_scale(float scalar, vector3 v) {
    float x = scalar * v.x;
    float y = scalar * v.y;
    float z = scalar * v.z;

    return (vector3) {x, y, z};
}

float vector_dot(vector3 a, vector3 b) {
    float x = a.x * b.x;
    float y = a.y * b.y;
    float z = a.z * b.z;

    return (x + y + z);
}

float vector_length(vector3 a) {
    return sqrtf(vector_dot(a, a));
}