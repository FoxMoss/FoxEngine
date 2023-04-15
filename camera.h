#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "foxsdf.h"
#include "foxmath.h"
#include <float.h>


#define MAXSTEPS 20
#define WIDTH 150
#define HEIGHT 150
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
} FoxCamera;

void NewFoxCamera(FoxCamera *cam);


SDFReturn smallestDist(Vector3 point, FoxCamera camera);
void render(FoxCamera * camera, Image imageBuffer);

#endif
