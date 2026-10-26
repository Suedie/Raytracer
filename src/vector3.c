#include "vector3.h"
#include <math.h>

vector3 vector3_add(vector3 a, vector3 b) {
    float x = a.x + b.x;
    float y = a.y + b.y;
    float z = a.z + b.z;

    return (vector3) {x, y, z};
}

vector3 vector3_sub(vector3 a, vector3 b) {
    float x = a.x - b.x;
    float y = a.y - b.y;
    float z = a.z - b.z;

    return (vector3) {x, y, z};
}

vector3 vector3_scale(float scalar, vector3 v) {
    float x = scalar * v.x;
    float y = scalar * v.y;
    float z = scalar * v.z;

    return (vector3) {x, y, z};
}

float vector3_dot(vector3 a, vector3 b) {
    float x = a.x * b.x;
    float y = a.y * b.y;
    float z = a.z * b.z;

    return (x + y + z);
}

float vector3_length(vector3 a) {
    return sqrtf(vector3_dot(a, a));
}

vector3 vector3_normalize(vector3 a) {
    float len = vector3_length(a);
    return vector3_scale(1.0f / len, a);
}