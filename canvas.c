#include "canvas.h"
#include <stdlib.h>

canvas* canvas_create(int width, int height) {
    canvas* c = malloc(sizeof *c);
    if (!c) return NULL;
    c->width = width;
    c->height = height;
    c->pixels = calloc(width * height, sizeof *c->pixels);
    if (!c->pixels) {free(c); return NULL;}
    return c;
}

void put_pixel(canvas *canvas, int x, int y, pixel colour) {
    int width = canvas->width;
    int height = canvas->height;

    int screen_x = (width / 2) + x;
    int screen_y = (height / 2) - y;
    if (screen_x < 0 || screen_y < 0 || screen_x >= width || screen_y >= height) {
        return;
    }

    canvas->pixels[screen_x + (screen_y * width)] = colour;
}

