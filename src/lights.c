#include "lights.h"
#include <stdlib.h>


lights lights_create(void) {
    point_light *pl = NULL;
    int point_light_count = 0;
    int point_light_capacity = 0;
    directional_light dl = {{0.0f, 0.0f, 0.0f}, 0.0f};
    ambient_light al = {0.0f};
    lights l = {pl, point_light_count, point_light_capacity, dl, al};
    return l;
}

void lights_add_point(lights *l, point_light pl) {
    if (l->point_light_count >= l->point_light_capacity) {
        int new_cap;
        if (l->point_light_capacity <= 0) {
            new_cap = 4;
        } else {
            new_cap = l->point_light_capacity * 2;
        }

        point_light *new_point_lights = realloc(l->point_lights, new_cap * sizeof(*l->point_lights));
        if (!new_point_lights) {
            return;
        }
        l->point_lights = new_point_lights;
        l->point_light_capacity = new_cap;
    }

    l->point_lights[l->point_light_count] = pl;
    l->point_light_count++;
}

void lights_set_directional(lights *l, directional_light directional) {
    l->directional = directional;
}

void lights_set_ambient (lights *l, ambient_light ambient) {
    l->ambient = ambient;
}
