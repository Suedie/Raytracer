#include "render.h"
#include "camera.h"
#include "canvas.h"
#include "sphere.h"
#include "vector.h"
#include "scene.h"
#include <math.h>
#include <stdbool.h>

intersect intersect_ray_sphere (vector3 origin, vector3 direction, sphere s) {
    float radius = s.radius;
    vector3 center_to_origin = vector_sub(origin, s.centre);
    
    float a = vector_dot(direction, direction);
    float b = 2 * vector_dot(center_to_origin, direction);
    float c = vector_dot(center_to_origin, center_to_origin) - radius * radius;

    float discriminant = (b * b) - (4 * a * c);
    if (discriminant < 0) {
        return (intersect) {INFINITY, INFINITY, false};
    }

    float t1 = (-b + sqrtf(discriminant)) / (2 * a);
    float t2 = (-b - sqrtf(discriminant)) / (2 * a);

    return (intersect) {t1, t2, true};
}

pixel trace_ray (vector3 origin, scene s, vector3 direction, float t_min, float t_max) {
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

void render_scene_to_canvas (canvas *canv, camera cam, scene scen) {
    for (int x = -canv->width / 2; x < canv->width / 2; x++) {
        for (int y = -canv->height / 2; y < canv->height / 2; y++) {
            vector3 direction = canvas_to_viewport(canv->width, canv->height, x, y, cam);
            pixel colour = trace_ray(cam.position, scen, direction, 1, INFINITY);
            put_pixel(canv, x, y, colour);
        }
    }
}
