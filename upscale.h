#ifndef UPSCALE_H
#define UPSCALE_H

#include "raylib.h"

void upscaleImage(Image* buffer, int size);

bool coloreqeq(Color x, Color y);

Color GetImageColorSafe(Image *image, int x, int y);

#endif