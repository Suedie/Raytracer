#include "canvas.h"
#include <stdint.h>
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

pixel pixel_create(int red, int green, int blue) {
    if (red < 0)        red = 0;
    if (red > 255)      red = 255;
    if (green < 0)      green = 0;
    if (green > 255)    green = 255;
    if (blue < 0)       blue = 0;
    if (blue > 255)     blue = 255;

    pixel p = {(uint8_t) red, (uint8_t) green, (uint8_t) blue};
    return p;
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

