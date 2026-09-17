#include "camera.h"
#include "canvas.h"
#include "sphere.h"
#include "vector.h"
#include "scene.h"
#include "render.h"


int main () {

    camera cam = create_default_camera();
    canvas *canv = canvas_create(1920, 1080);

    sphere sphere_red       = (sphere) {(vector3) {0.0f, -1.0f, 3.0f}, 1.0f, pixel_create(255, 0, 0)};
    sphere sphere_blue      = (sphere) {(vector3) {2.0f, 0.0f, 4.0f}, 1.0f, pixel_create(0, 0, 255)};
    sphere sphere_green     = (sphere) {(vector3) {-2.0f, 0.0f, 4.0f}, 1.0f, pixel_create(0, 255, 0)};

    scene *scen = create_scene();
    add_sphere_to_scene(scen, sphere_red);
    add_sphere_to_scene(scen, sphere_blue);
    add_sphere_to_scene(scen, sphere_green);

    while (1) {
        render_scene_to_canvas (canv, cam, *scen);
    }
}