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

static uint8_t clamp_u8 (int value) {
    if (value < 0)      value = 0;
    else if (value > 255)    value = 255;

    return (uint8_t) value;
}

pixel pixel_create(int red, int green, int blue) {
    pixel p = {clamp_u8(red), clamp_u8(green), clamp_u8(blue)};
    return p;
}

pixel pixel_scalar_multiply(float scalar, pixel p) {
    uint8_t red      = clamp_u8((int)(scalar * p.red+ 0.5f));
    uint8_t green    = clamp_u8((int)(scalar * p.green + 0.5f));
    uint8_t blue     = clamp_u8((int)(scalar * p.blue + 0.5f));

    return (pixel){red, green, blue};
}

pixel pixel_add(pixel p, pixel q) {
    uint8_t red = clamp_u8(p.red + q.red);
    uint8_t green = clamp_u8(p.green + q.green);
    uint8_t blue = clamp_u8(p.blue + q.blue);

    return (pixel){red, green, blue};
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

