#include "canvas.h"
#include <stdlib.h>

canvas* Canvas_Create(int width, int height) {
    canvas* c = malloc(sizeof *c);
    if (!c) return NULL;
    c->width = width;
    c->height = height;
    c->pixels = calloc(width * height, sizeof *c->pixels);
    if (!c->pixels) {free(c); return NULL;}
    return c;
}