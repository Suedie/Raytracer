#include "light.h"
#include "stdlib.h"
#include "scene.h"
#include "vector.h"


lights create_lights(void) {
    point_light *pl = NULL;
    int point_light_count = 0;
    int point_light_capacity = 0;
    directional_light dl;
    ambient_light al;
    lights l = {pl, point_light_count, point_light_capacity, dl, al};
    return l;
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

void set_directional_light(lights *l, directional_light dl) {
    l->dl = dl;
}

void set_ambient_light (lights *l, ambient_light al) {
    l->al = al;
}

float compute_light(lights *l, vector3 p, vector3 n) {
    float intensity = 0.0f;
    intensity += l->al.intensity;
    vector3 L = l->dl.direction;
    float n_dot_l = vector_dot(n, L);
    if  (n_dot_l > 0) {
        intensity += l->dl.intensity * n_dot_l / (vector_length(n) * vector_length(L));
    }

    for (int i = 0; i < l->point_light_count; i++) {
        L = vector_sub(l->pl[i].position, p);
        n_dot_l = vector_dot(n, L);
        if  (n_dot_l > 0) {
            intensity += l->pl[i].intensity * n_dot_l / (vector_length(n) * vector_length(L));
        }
    }

    return intensity;
}