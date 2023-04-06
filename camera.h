#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "foxmath.h"

#define MAXSTEPS 20
#define WIDTH 450
#define HEIGHT 450

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

void NewFoxCamera (FoxCamera* this)
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

Vector3 objects[1] = {(Vector3){0,-1,10}};

float smallestDist(Vector3 point)
{
    float smallest = INFINITY;
    for (int i = 0; i < 1; i++)
    {
        
        smallest = fminf(smallest, sphereSDF(point, objects[i], 1));
        //smallest = fminf(smallest, planeSDF(point, objects[i].y));
        //smallest = fminf(smallest, boxcheapSDF(point, objects[i], (Vector3) {1,1,1}));
    }
    
    return smallest;
}

void render(FoxCamera camera)
{

    float xx = 0;
    float yy = 0;
    Color color = BLACK;


    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            
            xx = (2 * ((x + 0.5) * camera.invWidth) - 1) * camera.angle * camera.aspectratio;
            yy = (1 - 2 * ((y + 0.5) * camera.invHeight)) * camera.angle;
            color = BLACK;

            Vector3 raydir = {xx, yy, 1};
            normalize(&raydir);

            float dist = 0;

            int steps = 20;

            if(IsKeyDown(KEY_R))
            {
                steps = 70;
            }
            
            for (int k = 0; k < steps; ++k)
            {
                float distAdd = smallestDist(addVec3(mulVec3(raydir, dist), camera.position));
                // printf("dist: %f\n point: (x: %f, y: %f, z: %f)", smallestDist, mulVec3(raydir, dist).x, mulVec3(raydir, dist).y, mulVec3(raydir, dist).z);

                dist += distAdd;
                if (distAdd < 0.1)
                {
                    Vector3 pos = absVec3(mulVec3(raydir, dist));
                    color = (Color){pos.z*10, pos.x*20, pos.y*10, 255};

                    DrawPixel(x, y, color);
                    break;
                }
                
            }
        }
    }
}

#endif
