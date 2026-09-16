#include "camera.h"

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