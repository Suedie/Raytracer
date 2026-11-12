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
pixel render_trace_ray (vector3 origin, scene *s, vector3 direction, float t_min, float t_max, int recursion_depth);
void render_scene_to_canvas (canvas *cv, camera *c, scene *s);
float render_compute_lighting(scene *scene, vector3 point, vector3 normal, vector3 view, float specular);

#endif