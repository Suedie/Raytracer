#include "camera.h"
#include "vector3.h"
#include <math.h>

static const float MOVE_SPEED = 5.0f;
static const float YAW_SPEED = 1.5f;

static void add_yaw(camera *cam, float yaw) {
    cam->yaw += yaw;
    cam->direction = (vector3) {sinf(cam->yaw), cam->direction.y , cosf(cam->yaw)};
}

static vector3 camera_get_right(camera *cam) {
    return vector3_normalize(vector3_cross(vector3_normalize(cam->up_direction), vector3_normalize(cam->direction)));
}

camera camera_create_default(void) {
    float yaw =  0.0f;
    vector3 position        = {0.0f, 0.0f, 0.0f,};
    vector3 direction       = {sinf(yaw), 0.0f, cosf(yaw)};
    vector3 up_direction    = {0.0f, 1.0f, 0.0f};

    float viewport_width    = 1.0f;
    float viewport_height   = 1.0f;
    float viewport_distance = VIEWPORT_DISTANCE;

    camera c   = (camera) {yaw, position, direction, up_direction, viewport_width, viewport_height, viewport_distance};
    return c;
}

vector3 camera_viewport_coord_from_canvas (int width, int height, int x, int y, camera c) {
    float viewport_x    = (float) x * (c.viewport_width / (float) width);
    float viewport_y    = (float) y * (c.viewport_height / (float) height);

    return (vector3) {viewport_x, viewport_y, c.viewport_distance};
}

void camera_move_forward(camera *cam, float delta_time) {
    cam->position = vector3_add(cam->position, vector3_scale(MOVE_SPEED * delta_time, vector3_normalize(cam->direction)));
}

void camera_move_backward(camera *cam, float delta_time) {
    cam->position = vector3_sub(cam->position, vector3_scale(MOVE_SPEED * delta_time, vector3_normalize(cam->direction)));
}

void camera_move_right(camera *cam, float delta_time) {
    cam->position = vector3_add(cam->position, vector3_scale(MOVE_SPEED * delta_time, camera_get_right(cam)));
}

void camera_move_left(camera *cam, float delta_time) {
    cam->position = vector3_sub(cam->position,vector3_scale(MOVE_SPEED * delta_time, camera_get_right(cam)));
}

void camera_yaw_left(camera *cam, float delta_time) {
    add_yaw(cam, -YAW_SPEED * delta_time);
}

void camera_yaw_right(camera *cam, float delta_time) {
    add_yaw(cam, YAW_SPEED * delta_time);
}