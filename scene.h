#ifndef SCENE_H
#define SCENE_H

#include "sphere.h"
#include "light.h"

typedef struct {
    sphere *spheres;
    int sphere_count;

    point_light *points;
    int point_light_count;
    directional_light dir_light;
    ambient_light ambient;

} scene;

scene *create_scene (void);
void add_sphere_to_scene (scene *scen, sphere spher);

#endif