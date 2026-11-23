#include "sphere.h"
#include "vector3.h"

sphere construct_sphere(vector3 center_pos, float radius, pixel colour, float specular, float reflective) {
    return (sphere) {center_pos, radius, radius * radius, colour, specular, reflective};
}

void set_radius(sphere *s, float radius) {
    s->radius = radius;
    s->radius_sqr = radius * radius;
}