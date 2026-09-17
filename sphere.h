#ifndef SPHERE_H
#define SPHERE_H

#include "canvas.h"
#include "vector.h"


typedef struct {
    vector3 centre;
    pixel colour;
    float radius;

} sphere;

#endif