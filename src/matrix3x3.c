#include "matrix3x3.h"
#include "vector3.h"

vector3 matrix_vector_mult(matrix3x3 a, vector3 b) {
    float cx = a.ma.x * b.x + a.mb.x * b.y + a.mc.x * b.z;
    float cy = a.ma.y * b.x + a.mb.y * b.y + a.mc.y * b.z;
    float cz = a.ma.z * b.x + a.mb.z * b.y + a.mc.z * b.z;

    return (vector3) {cx, cy, cz};
}