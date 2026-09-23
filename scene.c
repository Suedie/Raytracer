#include "scene.h"
#include "sphere.h"
#include <stdlib.h>

scene *create_scene (void) {
    scene *scene = malloc(sizeof(*scene));
    if (!scene) {
        return NULL;
    }
    scene->spheres = calloc(0, sizeof(*scene->spheres));
    if (!scene->spheres) {
        free(scene);
        return NULL;
    }
    scene->sphere_count = 0;
    return scene;
}

//TODO add capacity doubling
void add_sphere_to_scene (scene *s, sphere sp) {
    sphere *new_spheres = realloc(s->spheres, (s->sphere_count + 1) * sizeof(*s->spheres));
    if (!new_spheres) {
        return;
    }
    s->spheres = new_spheres;
    s->spheres[s->sphere_count] = sp;
    s->sphere_count++;
}