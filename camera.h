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

void NewFoxCamera(FoxCamera *cam)
{
    cam->position = (Vector3){0, 0, 0};
    cam->rotation = (Vector3){0, 0, 0};
    cam->invWidth = 1 / (float)WIDTH;
    cam->invHeight = 1 / (float)HEIGHT;
    cam->fov = 30;
    cam->aspectratio = WIDTH / (float)HEIGHT;
    cam->angle = tan(PI * 0.5 * cam->fov / 180.);
    // this->*framebuffer = malloc(camera.width * camera.height * sizeof(Vector3));
}

typedef enum SDFType
{
    SDF_SPHERE = 0,
    SDF_PLANE = 1
} SDFType;
typedef struct SDFObject
{
    SDFType type;
    Vector3 postion;

} SDFObject;

SDFObject objects[2] = {{SDF_PLANE, {2, -1, 10}}, {SDF_SPHERE, {0, 2, 10}}};

float smallestDist(Vector3 point, FoxCamera camera)
{
    float smallest = INFINITY;

    for (int i = 0; i < sizeof(objects) / sizeof(SDFObject); i++)
    {
        //Vector3 calculatedPosition =addVec3(rotVec3(subVec3(objects[i].postion, camera.position), axisY, camera.rotation.y), camera.position);
        Vector3 calculatedPosition = objects[i].postion;
        switch (objects[i].type)
        {
        case SDF_SPHERE:
            smallest = fminf(smallest, sphereSDF(point, calculatedPosition, 1));
            break;
        case SDF_PLANE:

            smallest = fminf(smallest, planeSDF(point, calculatedPosition.y));
            break;

        default:
            printf("ERROR: Undf object.");
            break;
        }
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
                float distAdd = smallestDist(addVec3(mulVec3(raydir, dist), camera.position), camera);
                // printf("dist: %f\n point: (x: %f, y: %f, z: %f)", smallestDist, mulVec3(raydir, dist).x, mulVec3(raydir, dist).y, mulVec3(raydir, dist).z);

                dist += distAdd;
                if (distAdd < 0.4)
                {
                    Vector3 rayFinalPos = addVec3(mulVec3(raydir, dist), camera.position);
                    Vector3 normal = (Vector3){
                        (smallestDist(addVec3(rayFinalPos, (Vector3){0.01, 0, 0}), camera) - smallestDist(subVec3(rayFinalPos, (Vector3){0.01, 0, 0}), camera)),
                        (smallestDist(addVec3(rayFinalPos, (Vector3){0, 0.01, 0}), camera) - smallestDist(subVec3(rayFinalPos, (Vector3){0, 0.01, 0}), camera)),
                        (smallestDist(addVec3(rayFinalPos, (Vector3){0, 0, 0.01}), camera) - smallestDist(subVec3(rayFinalPos, (Vector3){0, 0, 0.01}), camera))};

                    normalize(&normal);

                    // Vector3 pos = absVec3(addVec3(mulVec3(raydir, dist), camera.position));

                    float lightAmmount = fmax(-dotVec3(normal, (Vector3){-100, 0, 0}), 0);
                    // printf("%f\n", lightAmmount);

                    color = (Color){lightAmmount, lightAmmount, lightAmmount, 255};
                    break;
                }
            }

            ImageDrawRectangle(&imageBuffer, x * SCALEUP, y * SCALEUP, SCALEUP, SCALEUP, color);
        }
    }
}

#endif
