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
void add_sphere_to_scene (scene *scen, sphere spher) {
    sphere *new_spheres = realloc(scen->spheres, (scen->sphere_count + 1) * sizeof(*scen->spheres));
    if (!new_spheres) {
        return;
    }
    scen->spheres = new_spheres;
    scen->spheres[scen->sphere_count] = spher;
    scen->sphere_count++;
}