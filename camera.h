#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "foxsdf.h"
#include "foxmath.h"
#include <float.h>
#include "levels.h"


#define MAXSTEPS 20
#define WIDTH 75
#define HEIGHT 75
#define REAL_TARGET 900
#define SCALEUP REAL_TARGET / HEIGHT


typedef struct FoxCamera
{
    Vector3 rotation;
    Vector3 position;
    Vector3 scale;
    float invWidth;
    float invHeight;
    float fov;
    float aspectratio;
    float angle;
    int maxDist;
} FoxCamera;

void NewFoxCamera(FoxCamera *cam);


SDFReturn smallestDist(Vector3 point, FoxCamera camera, SDFLevel level);
void render(FoxCamera * camera, Image imageBuffer, SDFLevel level);

#endif
