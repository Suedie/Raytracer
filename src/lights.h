#ifndef LIGHT_H
#define LIGHT_H

#include "vector.h"

typedef struct {
    vector3 position;
    float intensity;
} point_light;

typedef struct {
    vector3 direction;
    float intensity;
} directional_light;

typedef struct {
    float intensity;
} ambient_light;


typedef struct {
    point_light *pl;
    int point_light_count;
    int point_light_capacity;
    directional_light dl;
    ambient_light al;
} lights;

lights lights_create(void);
void lights_add_point(lights *l, point_light p);
void light_set_directional(lights *l, directional_light dl);
void lights_set_ambient (lights *l, ambient_light al);
float lights_compute(lights *l, vector3 p, vector3 n);

#endif