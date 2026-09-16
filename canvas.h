#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h>


typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} pixel;

typedef struct {
    int width;
    int height;
    pixel *pixels;
} canvas;

canvas* canvas_create(int width, int height);
void put_pixel(canvas* canvas, int x, int y, pixel colour);

#endif