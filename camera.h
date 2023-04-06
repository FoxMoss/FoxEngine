#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define MAXSTEPS 4

typedef struct FoxCamera
{
    Vector3 rotation;
    Vector3 position;
    int depth;
    int height;
    int width;
} FoxCamera;

void NewFoxCamera(FoxCamera *this)
{
    this->position = (Vector3){0, 0, 0};
    this->rotation = (Vector3){0, 0, 0};
    this->depth = 5;
    this->height = 450;
    this->width = 450;
    // this->*framebuffer = malloc(camera.width * camera.height * sizeof(Vector3));
}

float length(Vector3 vector)
{
    float distX = powf(vector.x, 2);
    float distY = powf(vector.y, 2);
    float distZ = powf(vector.z, 2);
    return sqrt(distX + distY + distZ);
}

float sphereSDF(Vector3 point, Vector3 sphere, float radius)
{
    float distX = powf(sphere.x - point.x, 2);
    float distY = powf(sphere.y - point.y, 2);
    float distZ = powf(sphere.z - point.z, 2);
    return sqrtf(distX + distY + distZ) - radius;
}

Vector3 normalize(Vector3 vector)
{
    float len = length(vector);
    Vector3 ret = {vector.x / len, vector.y / len, vector.z / len};
    return ret;
}
Vector3 mulVec3(Vector3 x, float y)
{
    return (Vector3){x.x * y, x.y * y, x.z * y};
}
Vector3 addVec3(Vector3 x, Vector3 y)
{
    return (Vector3){x.x + y.x, x.y + y.y, x.z + y.z};
}
void render(FoxCamera camera)
{
    float invWidth = 1 / (float)camera.width;
    float invHeight = 1 / (float)camera.height;
    float fov = 30;
    float aspectratio = camera.width / (float)camera.height;
    float angle = tan(PI * 0.5 * fov / 180.);

    float xx = 0;
    float yy = 0;
    Color color = BLACK;

    for (int y = 0; y < camera.height; ++y)
    {
        for (int x = 0; x < camera.width; ++x)
        {
            xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
            yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
            color = BLACK;

            Vector3 raydir = {xx, yy, 1};
            raydir = normalize(raydir);

            float dist = 0;

            for (int k = 0; k < MAXSTEPS; ++k)
            {
                float smallestDist = sphereSDF(addVec3(mulVec3(raydir, dist), camera.position), (Vector3){0, 1, 10}, 1);
                // printf("dist: %f\n point: (x: %f, y: %f, z: %f)", smallestDist, mulVec3(raydir, dist).x, mulVec3(raydir, dist).y, mulVec3(raydir, dist).z);

                dist += smallestDist;
                if (smallestDist < 0.1)
                {
                    color = (Color){255 - dist * 255 * 0.5, 0, 0, 255};
                    break;
                }
            }

            DrawPixel(x, y, color);
        }
    }
}

#endif
