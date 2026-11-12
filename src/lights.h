#ifndef LIGHTS_H
#define LIGHTS_H

#include "vector3.h"

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
    point_light *point_lights;
    int point_light_count;
    int point_light_capacity;
    directional_light directional;
    ambient_light ambient;
} lights;

lights lights_create(void);
void lights_add_point(lights *l, point_light pl);
void lights_set_directional(lights *l, directional_light directional);
void lights_set_ambient (lights *l, ambient_light ambient);
float lights_compute(lights *scene_lights, vector3 point, vector3 normal, float specular);

#endif