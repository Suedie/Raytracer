#ifndef RENDER_H
#define RENDER_H

#include "canvas.h"
#include "vector3.h"
#include "camera.h"
#include "scene.h"
#include <stdbool.h>

static const pixel BACKGROUND_COLOUR = {255, 255, 255};

typedef struct {
    float t1;
    float t2;
    bool hit;
} intersect;

typedef struct {
    float closest_t;
    sphere *closest_sphere;
} closest_intersect;

intersect render_intersect_ray_sphere (vector3 origin, vector3 direction, sphere s);
closest_intersect render_closest_intersection(vector3 origin, scene *s, vector3 direction, float t_min, float t_max);
pixel render_trace_ray (vector3 cameraPosition, scene *s, vector3 direction, float t_min, float t_max);
void render_scene_to_canvas (canvas *cv, camera c, scene *s);

#endif