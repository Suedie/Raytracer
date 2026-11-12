#ifndef CAMERA_H
#define CAMERA_H

#include "vector3.h"

static const float VIEWPORT_DISTANCE = 1.0f;


typedef struct {
    vector3 position;
    vector3 direction;
    vector3 up_direction;

    float viewport_width;
    float viewport_height;
    float viewport_distance;
} camera;

camera camera_create_default(void);
vector3 camera_viewport_coord_from_canvas (int width, int height, int x, int y, camera c);
void move_forward(camera *cam);
void move_backward(camera *cam);
void move_right(camera *cam);
void move_left(camera *cam);

#endif