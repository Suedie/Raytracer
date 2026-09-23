#include "scene.h"
#include "sphere.h"
#include <corecrt_search.h>
#include <stdlib.h>

scene *create_scene (void) {
    scene *scene = malloc(sizeof(*scene));
    if (!scene) {
        return NULL;
    }
    scene->spheres = NULL;
    scene->sphere_count = 0;
    scene->sphere_capacity = 0;
    return scene;
}

void add_sphere_to_scene (scene *s, sphere sp) {
    if (s->sphere_count >= s->sphere_capacity) {
        int new_cap;
        if (s->sphere_capacity <= 0) {
            new_cap = 4;
        } else {
            new_cap = s->sphere_capacity * 2;
        }

        sphere *new_spheres = realloc(s->spheres, new_cap * sizeof(*s->spheres));
        if (!new_spheres) {
            return;
        }
        s->spheres = new_spheres;
        s->sphere_capacity = new_cap;
    }
    s->spheres[s->sphere_count] = sp;
    s->sphere_count++;
}