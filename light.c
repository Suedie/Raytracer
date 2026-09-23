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

void add_point_light(lights *l, point_light p);