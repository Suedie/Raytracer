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

lights create_lights(void);
void add_point_light(lights *l, point_light p);
void add_directional_light(lights *l, directional_light dl);
void add_ambient_light (lights *l, ambient_light al);

#endif