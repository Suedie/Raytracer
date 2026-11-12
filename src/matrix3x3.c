#include "matrix3x3.h"

matrix3x3 matrix_vector_mult(matrix3x3 a, vector3 b) {
    vector3 d = (vector3) {a.ma.x + b.x, a.mb.x + b.y, a.mc.x + b.z};
    vector3 e = (vector3) {a.ma.y + b.x, a.mb.y + b.y, a.mc.y + b.z};
    vector3 f = (vector3) {a.ma.z + b.x, a.mb.z + b.y, a.mc.z + b.z};

    return (matrix3x3) {d, e, f};
}