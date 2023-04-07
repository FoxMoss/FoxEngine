#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "foxmath.h"
#include <float.h>

const int MAXSTEPS = 20;
const int WIDTH = 90;
const int HEIGHT = 90;
const int REAL_TARGET = 450;
const int SCALEUP = REAL_TARGET / HEIGHT;

typedef struct FoxCamera
{
    Vector3 rotation;
    Vector3 position;
    float invWidth;
    float invHeight;
    float fov;
    float aspectratio;
    float angle;
} FoxCamera;

void NewFoxCamera(FoxCamera *this)
{
    this->position = (Vector3){0, 0, 0};
    this->rotation = (Vector3){0, 0, 0};
    this->invWidth = 1 / (float)WIDTH;
    this->invHeight = 1 / (float)HEIGHT;
    this->fov = 30;
    this->aspectratio = WIDTH / (float)HEIGHT;
    this->angle = tan(PI * 0.5 * this->fov / 180.);
    // this->*framebuffer = malloc(camera.width * camera.height * sizeof(Vector3));
}

Vector3 objects[1] = {(Vector3){2, -1, 10}};

float smallestDist(Vector3 point)
{
    float smallest = INFINITY;
    for (int i = 0; i < 1; i++)
    {

        smallest = fminf(smallest, sphereSDF(point, objects[i], 1));
        smallest = fminf(smallest, planeSDF(point, objects[i].y));
        // smallest = fminf(smallest, boxcheapSDF(point, objects[i], (Vector3) {1,1,1}));
    }

    return smallest;
}

void render(FoxCamera camera, Image imageBuffer)
{
    float xx = 0;
    float yy = 0;
    Color color = BLACK;

    for (int y = 0; y < WIDTH; y++)
    {
        for (int x = 0; x < HEIGHT; x++)
        {
            xx = (2 * ((x + 0.5) * camera.invWidth) - 1) * camera.angle * camera.aspectratio;
            yy = (1 - 2 * ((y + 0.5) * camera.invHeight)) * camera.angle;
            color = BLACK;

            Vector3 raydir = {xx, yy, 1};
            normalize(&raydir);

            float dist = 0;

            int steps = 20;

            if (!IsKeyDown(KEY_R))
            {
                steps = 50;
            }

            for (int k = 0; k < steps; ++k)
            {
                float distAdd = smallestDist(addVec3(mulVec3(raydir, dist), camera.position));
                // printf("dist: %f\n point: (x: %f, y: %f, z: %f)", smallestDist, mulVec3(raydir, dist).x, mulVec3(raydir, dist).y, mulVec3(raydir, dist).z);

                dist += distAdd;
                if (distAdd < 0.4)
                {
                    Vector3 pos = absVec3(addVec3(mulVec3(raydir, dist), camera.position));
                    color = (Color){pos.z * 10, pos.x * 20, pos.y * 10, 255};
                    break;
                }
            }

            ImageDrawRectangle(&imageBuffer, x * SCALEUP, y * SCALEUP, SCALEUP, SCALEUP, color);
        }
    }
}

#endif
