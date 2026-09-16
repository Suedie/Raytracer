#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"

typedef struct {
    vector3 position;
    vector3 direction;
    vector3 up_direction;

    float viewport_width;
    float viewport_height;
    float viewport_distance;
} camera;


#endif