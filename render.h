#ifndef RENDER_H
#define RENDER_H

#include "vector.h"
#include "camera.h"
#include "scene.h"

static const vector3 BACKGROUND_COLOUR = {255.0f, 255.0f, 255.0f};


vector3 TraceRay (camera c, scene s, vector3 direction, float t_max);

#endif