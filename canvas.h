#include <stdint.h>


typedef struct {
    int red;
    int green;
    int blue;
} pixel;

typedef struct {
    int width;
    int height;
    pixel *pixels;
} canvas;

canvas* canvas_create(int width, int height);
void put_pixel(canvas* canvas, int x, int y, pixel colour);