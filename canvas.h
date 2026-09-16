#include <stdint.h>


typedef struct {
    int width;
    int height;
    uint32_t* pixels;
} Canvas;

Canvas* canvas_create(int width, int height);