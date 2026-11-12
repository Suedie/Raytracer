#include "render.h"
#include "camera.h"
#include "canvas.h"
#include "matrix3x3.h"
#include "sphere.h"
#include "vector3.h"
#include "scene.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include "lights.h"

//Changed from float to double because imprecision would make the giant sphere reflect on itself.
//In future should switch back to float, replace giant sphere with floor plane, as float is
//GPU optimised
intersect render_intersect_ray_sphere (vector3 origin, vector3 direction, sphere s) {
    double radius = s.radius;
    /*vector3 center_to_origin = vector3_sub(origin, s.centre);
    
    float a = vector3_dot(direction, direction);
    float b = 2 * vector3_dot(center_to_origin, direction);
    float c = vector3_dot(center_to_origin, center_to_origin) - radius * radius;
    */

    double ox = (double) origin.x - s.centre.x;
    double oy = (double) origin.y - s.centre.y;
    double oz = (double) origin.z - s.centre.z;
    double dx = direction.x;
    double dy = direction.y;
    double dz = direction.z;

    double a = dx * dx + dy * dy + dz * dz;
    double b = 2.0 * (ox * dx + oy * dy + oz * dz);
    double c = (ox * ox + oy * oy + oz * oz) - radius * radius;

    double discriminant = (b * b) - (4.0 * a * c);
    if (discriminant < 0.0) {
        return (intersect) {INFINITY, INFINITY, false};
    }

    float t1 = (float) (-b + sqrt(discriminant)) / (2.0 * a);
    float t2 = (float) (-b - sqrt(discriminant)) / (2.0 * a);

    return (intersect) {t1, t2, true};
}

static closest_intersect closest_intersecting_sphere(vector3 origin, scene *s, vector3 direction, float t_min, float t_max) {
    float closest_t = INFINITY;
    sphere *closest_sphere = NULL;
    for (int i = 0; i < s->sphere_count; i++) {
        intersect intersection = render_intersect_ray_sphere(origin, direction, s->spheres[i]);
        if (!intersection.hit)  continue;

        if (intersection.t1 >= t_min && intersection.t1 <= t_max && intersection.t1 < closest_t) {
            closest_t = intersection.t1;
            closest_sphere = &s->spheres[i];
        }
        if (intersection.t2 >= t_min && intersection.t2 <= t_max && intersection.t2 < closest_t) {
            closest_t = intersection.t2;
            closest_sphere = &s->spheres[i];
        }
    }

    return (closest_intersect) {closest_t, closest_sphere};
}

static vector3 reflect_ray(vector3 reflection, vector3 normal) {
    return vector3_sub(vector3_scale(2, vector3_scale(vector3_dot(normal, reflection), normal)), reflection);
}

float render_compute_lighting(scene *s, vector3 point, vector3 normal, vector3 view, float specular) {
    sphere *blocking_sphere = NULL;
    float intensity = 0.0f;

    //Ambient
    intensity += s->scene_lights.ambient.intensity;

    //Directional
    vector3 light_direction = s->scene_lights.directional.direction;
    blocking_sphere = closest_intersecting_sphere(point, s, light_direction, 0.001f, INFINITY).closest_sphere;
    float n_dot_l = vector3_dot(normal, light_direction);
    if  (n_dot_l > 0 && blocking_sphere == NULL) {
        intensity += s->scene_lights.directional.intensity * n_dot_l / (vector3_length(normal) * vector3_length(light_direction));
    }

    for (int i = 0; i < s->scene_lights.point_light_count; i++) {
        light_direction = vector3_sub(s->scene_lights.point_lights[i].position, point);
        blocking_sphere = closest_intersecting_sphere(point, s, light_direction, 0.001f, 1.0f).closest_sphere;
        if (blocking_sphere != NULL) {
            continue;
        }
        n_dot_l = vector3_dot(normal, light_direction);

        //Diffuse
        if  (n_dot_l > 0) {
            intensity += s->scene_lights.point_lights[i].intensity * n_dot_l / (vector3_length(normal) * vector3_length(light_direction));
        }

        //Specular
        if (specular != -1.0f) {
            vector3 reflection = reflect_ray(light_direction, normal);
            float r_dot_v = vector3_dot(reflection, view);
            if (r_dot_v > 0) {
                intensity += s->scene_lights.point_lights[i].intensity * powf(r_dot_v / (vector3_length(reflection) * vector3_length(view)), specular);
            }
        }

    }
    return intensity;
}

pixel render_trace_ray (vector3 origin, scene *s, vector3 direction, float t_min, float t_max, int recursion_depth) {
    closest_intersect result = closest_intersecting_sphere(origin, s, direction, t_min, t_max);
    float closest_t = result.closest_t;
    sphere *closest_sphere = result.closest_sphere;

    if (closest_sphere == NULL) {
        return BACKGROUND_COLOUR;
    }

    vector3 point = vector3_add(origin, vector3_scale(closest_t, direction));
    vector3 normal = vector3_sub(point, closest_sphere->centre);
    normal = vector3_scale(1.0f / vector3_length(normal), normal);
    pixel local_colour = pixel_scalar_multiply(render_compute_lighting(s, point, normal, vector3_scale(-1.0f, direction), closest_sphere->specular), closest_sphere->colour);

    float reflection = closest_sphere->reflective;
    if (reflection <= 0.0f || recursion_depth <= 0) {
        return local_colour;
    }

    vector3 reflected_ray = reflect_ray(vector3_scale(-1.0f, direction), normal);
    pixel reflected_colour = render_trace_ray(point, s, reflected_ray, 0.001f, INFINITY, recursion_depth - 1);

    return pixel_add(pixel_scalar_multiply(1.0f - reflection, local_colour), pixel_scalar_multiply(reflection, reflected_colour));
}

void render_scene_to_canvas (canvas *cv, camera *cam, scene *s) {
    vector3 camera_forward = vector3_normalize(cam->direction);
    vector3 camera_right = vector3_normalize(vector3_cross(vector3_normalize(cam->up_direction), camera_forward));
    vector3 camera_up = vector3_cross(camera_forward, camera_right);
    matrix3x3 camera_rotation = (matrix3x3) {camera_right, camera_up, camera_forward};

    for (int y = -cv->height / 2; y < cv->height / 2; y++) {
        for (int x = -cv->width / 2; x < cv->width / 2; x++) {
            vector3 direction = matrix_vector_mult(camera_rotation,camera_viewport_coord_from_canvas(cv->width, cv->height, x, y, *cam));
            pixel colour = render_trace_ray(cam->position, s, direction, 1, INFINITY, 3);
            pixel_put(cv, x, y, colour);
        }
    }
}
