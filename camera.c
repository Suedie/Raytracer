#include "camera.h"
#include "vector.h"

camera create_default_camera(void) {
    vector3 position        = {0.0f, 0.0f, 0.0f,};
    vector3 direction       = {0.0f, 0.0f, 1.0f};
    vector3 up_direction    = {0.0f, 1.0f, 0.0f};

    float viewport_width    = 1.0f;
    float viewport_height   = 1.0f;
    float viewport_distance = VIEWPORT_DISTANCE;

    camera c   = (camera) {position, direction, up_direction, viewport_width, viewport_height, viewport_distance};
    return c;
}

vector3 canvas_to_viewport_coordinates (int width, int height, int x, int y, camera c) {
    float viewport_x    = (float) x * (c.viewport_width / (float) width);
    float viewport_y    = (float) y * (c.viewport_height / (float) height);

    return (vector3) {viewport_x, viewport_y, c.viewport_distance};
}