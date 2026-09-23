#ifndef LIGHT_H
#define LIGHT_H

#include "vector.h"

typedef struct {
    vector3 position;
    float intensity;

} point_light;

typedef struct {
    vector3 direction;
    float intensity;
} directional_light;

typedef struct {
    float intensity;
} ambient_light;

#endif