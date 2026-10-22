#ifndef SPHERE_H
#define SPHERE_H

#include "canvas.h"
#include "vector.h"


typedef struct {
    vector3 centre;
    float radius;
    pixel colour;
} sphere;


#endif