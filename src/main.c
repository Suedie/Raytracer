#include "camera.h"
#include "canvas.h"
#include "sphere.h"
#include "vector.h"
#include "scene.h"
#include "render.h"
#include <raylib.h>
#include <stdbool.h>
#include "light.h"


int main () {

    camera cam = camera_create_default();
    canvas *canv = canvas_create(1080, 1080);
    if (!canv) return 1;

    sphere sphere_red       = (sphere) {(vector3) {0.0f, -1.0f, 3.0f}, 1.0f, pixel_create(255, 0, 0)};
    sphere sphere_blue      = (sphere) {(vector3) {2.0f, 0.0f, 4.0f}, 1.0f, pixel_create(0, 0, 255)};
    sphere sphere_green     = (sphere) {(vector3) {-2.0f, 0.0f, 4.0f}, 1.0f, pixel_create(0, 255, 0)};
    sphere sphere_yellow    = (sphere) {(vector3) {0.0f, -5001.0f, 0.0f}, 5000.0f, pixel_create(255, 255, 0)};

    scene *scen = scene_create();
    if (!scen) return 1;

    scene_add_sphere(scen, sphere_red);
    scene_add_sphere(scen, sphere_blue);
    scene_add_sphere(scen, sphere_green);
    scene_add_sphere(scen, sphere_yellow);

    point_light pl = {{2.0f, 1.0f, 0.0f}, 0.6f};

    light_add_point(&scen->l, pl);
    light_set_ambient(&scen->l, (ambient_light){0.2f});
    light_set_directional(&scen->l, (directional_light) {{1.0f, 4.0f, 4.0f}, 0.2f});

    render_scene_to_canvas (canv, cam, *scen);

    //Render code
    InitWindow(canv->width, canv->height, "Raytracer");
    SetTargetFPS(60);

    // The canvas pixels are tightly packed 8-bit RGB, so raylib can read them directly
    Image image = {
        .data = canv->pixels,
        .width = canv->width,
        .height = canv->height,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8,
    };
    Texture2D texture = LoadTextureFromImage(image);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(texture, 0, 0, WHITE);
        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();

    return 0;
}