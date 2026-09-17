#include "render.h"
#include "sphere.h"
#include "vector.h"
#include "scene.h"
#include <math.h>
#include <stdbool.h>

typedef struct {
    float t1;
    float t2;
    bool hit;
} intersect;

intersect intersect_ray_sphere (vector3 origin, vector3 direction, sphere s) {
    float radius = s.radius;
    vector3 center_to_origin; //origin - s.centre;
    
    
}

vector3 trace_ray (vector3 origin, scene s, vector3 direction, float t_min, float t_max) {
    float closest_t = INFINITY;
    sphere *closest_sphere = NULL;
    for (int i = 0; i < s.sphere_count; i++) {
        intersect intersection = intersect_ray_sphere(origin, direction, s.spheres[i]);
        if (!intersection.hit)  continue;

        if (intersection.t1 >= t_min && intersection.t1 <= t_max && intersection.t1 < closest_t) {
            closest_t = intersection.t1;
            closest_sphere = &s.spheres[i];
        }
        if (intersection.t2 >= t_min && intersection.t2 <= t_max && intersection.t2 < closest_t) {
            closest_t = intersection.t2;
            closest_sphere = &s.spheres[i];
        }
    }
    if (closest_sphere == NULL) {
        return BACKGROUND_COLOUR;
    }
    return closest_sphere->colour;
}
