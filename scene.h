#ifndef SCENE_H
#define SCENE_H

#include "sphere.h"
#include "light.h"

typedef struct {
    sphere *spheres;
    int sphere_count;

    lights l;
} scene;

scene *create_scene (void);
void add_sphere_to_scene (scene *scen, sphere spher);

#endif