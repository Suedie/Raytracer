#ifndef SCENE_H
#define SCENE_H

#include "sphere.h"
#include "light.h"

typedef struct {
    sphere *spheres;
    int sphere_count;
    int sphere_capacity;

    lights l;
} scene;

scene *scene_create (void);
void scene_add_sphere (scene *s, sphere sp);

#endif