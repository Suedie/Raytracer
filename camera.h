#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"

static const float VIEWPORT_DISTANCE = 1.0f;


typedef struct {
    vector3 position;
    vector3 direction;
    vector3 up_direction;

    float viewport_width;
    float viewport_height;
    float viewport_distance;
} camera;

camera create_default_camera(void);
vector3 canvas_to_viewport (int width, int height, int x, int y, camera c);


#endif