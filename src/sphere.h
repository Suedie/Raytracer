#ifndef SPHERE_H
#define SPHERE_H

#include "canvas.h"
#include "vector3.h"


typedef struct {
    vector3 centre;
    float radius;
    float radius_sqr;
    pixel colour;
    float specular;
    float reflective;
} sphere;

sphere construct_sphere(vector3 center_pos, float radius, pixel colour, float specular, float reflective);
void set_radius(sphere *s, float radius);

#endif