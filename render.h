#ifndef RENDER_H
#define RENDER_H

#include "vector.h"
#include "camera.h"
#include "scene.h"
#include <stdbool.h>

static const vector3 BACKGROUND_COLOUR = {255.0f, 255.0f, 255.0f};

typedef struct {
    float t1;
    float t2;
    bool hit;
} intersect;

intersect intersect_ray_sphere (vector3 origin, vector3 direction, sphere s);
vector3 TraceRay (camera c, scene s, vector3 direction, float t_max);

#endif