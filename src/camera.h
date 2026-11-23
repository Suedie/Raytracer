#ifndef CAMERA_H
#define CAMERA_H

#include "vector3.h"

static const float VIEWPORT_DISTANCE = 1.0f;


typedef struct {
    float yaw;
    vector3 position;
    vector3 direction;
    vector3 up_direction;

    float viewport_width;
    float viewport_height;
    float viewport_distance;
} camera;

camera camera_create_default(void);
vector3 camera_viewport_coord_from_canvas (int width, int height, int x, int y, camera c);
void camera_move_forward(camera *cam, float delta_time);
void camera_move_backward(camera *cam, float delta_time);
void camera_move_right(camera *cam, float delta_time);
void camera_move_left(camera *cam, float delta_time);
void camera_yaw_left(camera *cam, float delta_time);
void camera_yaw_right(camera *cam, float delta_time);

#endif