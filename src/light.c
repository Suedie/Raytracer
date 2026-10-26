#include "light.h"
#include <stdlib.h>
#include "vector.h"


lights create_lights(void) {
    point_light *pl = NULL;
    int point_light_count = 0;
    int point_light_capacity = 0;
    directional_light dl = {{0.0f, 0.0f, 0.0f}, 0.0f};
    ambient_light al = {0.0f};
    lights l = {pl, point_light_count, point_light_capacity, dl, al};
    return l;
}

void light_add_point(lights *l, point_light p) {
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

void light_set_directional(lights *l, directional_light dl) {
    l->dl = dl;
}

void light_set_ambient (lights *l, ambient_light al) {
    l->al = al;
}

float light_compute(lights *l, vector3 p, vector3 n) {
    float intensity = 0.0f;
    intensity += l->al.intensity;
    vector3 L = l->dl.direction;
    float n_dot_l = vector3_dot(n, L);
    if  (n_dot_l > 0) {
        intensity += l->dl.intensity * n_dot_l / (vector3_length(n) * vector3_length(L));
    }

    for (int i = 0; i < l->point_light_count; i++) {
        L = vector3_sub(l->pl[i].position, p);
        n_dot_l = vector3_dot(n, L);
        if  (n_dot_l > 0) {
            intensity += l->pl[i].intensity * n_dot_l / (vector3_length(n) * vector3_length(L));
        }
    }

    return intensity;
}