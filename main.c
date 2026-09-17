#include "camera.h"
#include "canvas.h"
#include "sphere.h"
#include "vector.h"
#include "scene.h"
#include "render.h"
#include <SDL2/SDL.h>
#include <stdbool.h>


int main () {

    camera cam = create_default_camera();
    canvas *canv = canvas_create(1920, 1080);
    if (!canv) return 1;

    sphere sphere_red       = (sphere) {(vector3) {0.0f, -1.0f, 3.0f}, 1.0f, pixel_create(255, 0, 0)};
    sphere sphere_blue      = (sphere) {(vector3) {2.0f, 0.0f, 4.0f}, 1.0f, pixel_create(0, 0, 255)};
    sphere sphere_green     = (sphere) {(vector3) {-2.0f, 0.0f, 4.0f}, 1.0f, pixel_create(0, 255, 0)};

    scene *scen = create_scene();
    if (!scen) return 1;

    add_sphere_to_scene(scen, sphere_red);
    add_sphere_to_scene(scen, sphere_blue);

    add_sphere_to_scene(scen, sphere_green);


    render_scene_to_canvas (canv, cam, *scen);


        // ---- display ----
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window   *win = SDL_CreateWindow("Raytracer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        canv->width, canv->height, 0);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture  *tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGB24,
        SDL_TEXTUREACCESS_STATIC, canv->width, canv->height);

    SDL_UpdateTexture(tex, NULL, canv->pixels, canv->width * sizeof(pixel));

    bool running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, NULL, NULL);
        SDL_RenderPresent(ren);
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;

    return 0;
}