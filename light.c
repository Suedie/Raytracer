#include "light.h"
#include "vector.h"
#include "stdlib.h"

lights create_lights(void) {
    point_light *pl = NULL;
    int point_light_count = 0;
    int point_light_capacity = 0;
    directional_light dl;
    ambient_light al;
}

void add_point_light(lights *l, point_light p) {
    if (l->point_light_count >= l->point_light_capacity) {
        int new_cap;
        if (l->point_light_capacity <= 0) {
            new_cap = 4;
        } else {
            new_cap = l->point_light_capacity * 2;
        }

        point_light *new_point_lights = realloc(l->pl, new_cap * sizeof(*l->pl));
        if (!new_point_lights) {
            return;
        }
        l->pl = new_point_lights;
        l->point_light_capacity = new_cap;
    }

    l->pl[l->point_light_count] = p;
    l->point_light_count++;
}

void add_directional_light(lights *l, directional_light dl) {
    l->dl = dl;
}

void add_ambient_light (lights *l, ambient_light al) {
    l->al = al;
}