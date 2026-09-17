#ifndef RENDER_H
#define RENDER_H

#include "canvas.h"
#include "vector.h"
#include "camera.h"
#include "scene.h"
#include <stdbool.h>

static const pixel BACKGROUND_COLOUR = {255, 255, 255};

typedef struct {
    float t1;
    float t2;
    bool hit;
} intersect;

intersect intersect_ray_sphere (vector3 origin, vector3 direction, sphere s);
pixel TraceRay (camera c, scene s, vector3 direction, float t_max);
void render_scene_to_canvas (canvas *canv, camera cam, scene scen);

#endif