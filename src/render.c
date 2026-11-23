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
    double c = (ox * ox + oy * oy + oz * oz) - s.radius_sqr;

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

static bool is_occluded(vector3 origin, scene *s, vector3 direction, float t_min, float t_max, int *cache) {
    if (cache && *cache >= 0) {
        intersect intersection = render_intersect_ray_sphere(origin, direction, s->spheres[*cache]);
        if (intersection.hit) {
            if ((intersection.t1 >= t_min && intersection.t1 <= t_max) || (intersection.t2 >= t_min && intersection.t2 <= t_max)) {
                return true;
            }
        } else {
            *cache = -1;
        }
    }
    for (int i = 0; i < s->sphere_count; i++) {
        if (cache && *cache == i) {
            continue;
        }
        intersect intersection = render_intersect_ray_sphere(origin, direction, s->spheres[i]);
        if (!intersection.hit) {
            continue;
        }
        
        if ((intersection.t1 >= t_min && intersection.t1 <= t_max) || (intersection.t2 >= t_min && intersection.t2 <= t_max)) {
            if (cache) {
                *cache = i;
            }
            return true;
        }
    }

    return false;
}

static vector3 reflect_ray(vector3 reflection, vector3 normal) {
    return vector3_sub(vector3_scale(2, vector3_scale(vector3_dot(normal, reflection), normal)), reflection);
}

float render_compute_lighting(scene *s, vector3 point, vector3 normal, vector3 view, float specular, int shadow_cache[]) {
    float intensity = 0.0f;

    //Ambient
    intensity += s->scene_lights.ambient.intensity;

    //Directional
    vector3 light_direction = s->scene_lights.directional.direction;
    int *cache = NULL;
    if (shadow_cache) {
        cache = &shadow_cache[0];
    }
    bool in_shadow = is_occluded(point, s, light_direction, 0.001f, INFINITY, cache);
    float n_dot_l = vector3_dot(normal, light_direction);
    if  (n_dot_l > 0 && !in_shadow) {
        intensity += s->scene_lights.directional.intensity * n_dot_l / (vector3_length(normal) * vector3_length(light_direction));
    }

    for (int i = 0; i < s->scene_lights.point_light_count; i++) {
        light_direction = vector3_sub(s->scene_lights.point_lights[i].position, point);
        if (shadow_cache) {
            cache = &shadow_cache[i + 1];
        }
        bool in_shadow = is_occluded(point, s, light_direction, 0.001f, 1.0f, cache);
        if (in_shadow) {
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

pixel render_trace_ray (vector3 origin, scene *s, vector3 direction, float t_min, float t_max, int recursion_depth, int shadow_cache[]) {
    closest_intersect result = closest_intersecting_sphere(origin, s, direction, t_min, t_max);
    float closest_t = result.closest_t;
    sphere *closest_sphere = result.closest_sphere;

    if (closest_sphere == NULL) {
        return BACKGROUND_COLOUR;
    }

    vector3 point = vector3_add(origin, vector3_scale(closest_t, direction));
    vector3 normal = vector3_sub(point, closest_sphere->centre);
    normal = vector3_scale(1.0f / vector3_length(normal), normal);
    pixel local_colour = pixel_scalar_multiply(render_compute_lighting(s, point, normal, vector3_scale(-1.0f, direction), closest_sphere->specular, shadow_cache), closest_sphere->colour);

    float reflection = closest_sphere->reflective;
    if (reflection <= 0.0f || recursion_depth <= 0) {
        return local_colour;
    }

    vector3 reflected_ray = reflect_ray(vector3_scale(-1.0f, direction), normal);
    pixel reflected_colour = render_trace_ray(point, s, reflected_ray, 0.001f, INFINITY, recursion_depth - 1, NULL);

    return pixel_add(pixel_scalar_multiply(1.0f - reflection, local_colour), pixel_scalar_multiply(reflection, reflected_colour));
}

void render_scene_to_canvas (canvas *cv, camera *cam, scene *s, bool subsampling) {
    vector3 camera_forward = vector3_normalize(cam->direction);
    vector3 camera_right = vector3_normalize(vector3_cross(vector3_normalize(cam->up_direction), camera_forward));
    vector3 camera_up = vector3_cross(camera_forward, camera_right);
    matrix3x3 camera_rotation = (matrix3x3) {camera_right, camera_up, camera_forward};

    #pragma omp parallel for 
    for (int y = -cv->height / 2; y < cv->height / 2; y++) {
        int shadow_cache[s->scene_lights.point_light_count + 1];
        for (int i = 0; i <= s->scene_lights.point_light_count; i++) {
            shadow_cache[i] = -1;
        }
        if (subsampling) {
            int offset = y & 2;
            int x = (-cv->width / 2) + offset;
            vector3 direction = matrix_vector_mult(camera_rotation,camera_viewport_coord_from_canvas(cv->width, cv->height, x, y, *cam));
            pixel left = render_trace_ray(cam->position, s, direction, 1, INFINITY, 3, shadow_cache);
            pixel_put(cv, x, y, left);

            for (; x < cv->width / 2; x += 2) {
                direction = matrix_vector_mult(camera_rotation,camera_viewport_coord_from_canvas(cv->width, cv->height, x + 2, y, *cam));
                pixel right = render_trace_ray(cam->position, s, direction, 1, INFINITY, 3, shadow_cache);
                pixel_put(cv, x + 2, y, right);

                if (left.red == right.red && left.green == right.green && left.blue == right.blue) {
                    pixel_put(cv, x + 1, y, left);
                } else {
                    direction = matrix_vector_mult(camera_rotation,camera_viewport_coord_from_canvas(cv->width, cv->height, x + 1, y, *cam));
                    pixel mid = render_trace_ray(cam->position, s, direction, 1, INFINITY, 3, shadow_cache);
                    pixel_put(cv, x + 1, y, mid);
                }

                left = right;
            }
        } else {
            for (int x = -cv->width / 2; x < cv->width / 2; x++) {
            vector3 direction = matrix_vector_mult(camera_rotation,camera_viewport_coord_from_canvas(cv->width, cv->height, x, y, *cam));
            pixel colour = render_trace_ray(cam->position, s, direction, 1, INFINITY, 3, shadow_cache);
            pixel_put(cv, x, y, colour);
            }
        }        
    }
}
