#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "foxsdf.h"
#include <float.h>

const int MAXSTEPS = 20;
const int WIDTH = 150;
const int HEIGHT = 150;
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
    cam->fov = 90;
    cam->aspectratio = WIDTH / (float)HEIGHT;
    cam->angle = tan(PI * 0.5 * cam->fov / 180.);
    // this->*framebuffer = malloc(camera.width * camera.height * sizeof(Vector3));
}


SDFObject objects[3] = {{SDF_PLANE, {2, -1, 10}, WHITE, 0, (rayModifer){false}}, {SDF_BOX, {4, 1, 8}, BLUE, 1, (rayModifer){true, {0,0,1}, {}}}, {SDF_SPHERE, {2, 1, 10}, RED, 1,  (rayModifer){false}}};

SDFReturn smallestDist(Vector3 point, FoxCamera camera)
{
    float smallest = INFINITY;
    SDFObject object;

    for (int i = 0; i < sizeof(objects) / sizeof(SDFObject); i++)
    {
        // Vector3 calculatedPosition = objects[i].postion;
        float lastSmallest = smallest;
        switch (objects[i].type)
        {
        case SDF_SPHERE:
            smallest = fminf(smallest, sphereSDF(point, objects[i].postion, objects[i].scale));
            break;
        case SDF_PLANE:
            smallest = fminf(smallest, planeSDF(point, objects[i].postion.y));
            break;
        case SDF_BOX:
            smallest = fminf(smallest, boxcheapSDF(point, objects[i].postion, (Vector3){objects[i].scale, objects[i].scale, objects[i].scale}));
            // amallest += sphereSDF(point, objects[2].postion, objects[2].scale);
            break;
        default:
            printf("ERROR: Undf object.");
            break;
        }
        if (lastSmallest != smallest)
        {
            object = objects[i];
        }
    }

    return (SDFReturn){object, smallest};
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

            Vector3 raydir = {xx, yy, 1};
            raydir = rotVec3(raydir, axisX, camera.rotation.x);
            raydir = rotVec3(raydir, axisY, camera.rotation.y);
            normalize(&raydir);

            Vector3 rayOffset = camera.position;

            float dist = 0;

            int steps = 20;
            color = (Color){fabs(raydir.x) * 100, fabs(raydir.y) * 100, 0, 255};

            if (!IsKeyDown(KEY_R))
            {
                steps = 30;
            }

            for (int k = 0; k < steps; ++k)
            {
                SDFReturn smallestDistData = smallestDist(addVec3(mulVec3(raydir, dist), rayOffset), camera);
                if(smallestDistData.object.modifer.modifys)
                {
                    rayOffset = addVec3(rayOffset, smallestDistData.object.modifer.position);
                    //k--;
                    continue;
                }
                float distAdd = smallestDistData.dist;
                // printf("dist: %f\n point: (x: %f, y: %f, z: %f)", smallestDist, mulVec3(raydir, dist).x, mulVec3(raydir, dist).y, mulVec3(raydir, dist).z);

                dist += distAdd;
                if (distAdd < 0.1)
                {
                    Vector3 rayFinalPos = addVec3(mulVec3(raydir, dist), camera.position);
                    Vector3 normal = (Vector3){
                        (smallestDist(addVec3(rayFinalPos, (Vector3){0.0001, 0, 0}), camera).dist - smallestDist(subVec3(rayFinalPos, (Vector3){0.01, 0, 0}), camera).dist),
                        (smallestDist(addVec3(rayFinalPos, (Vector3){0, 0.0001, 0}), camera).dist - smallestDist(subVec3(rayFinalPos, (Vector3){0, 0.01, 0}), camera).dist),
                        (smallestDist(addVec3(rayFinalPos, (Vector3){0, 0, 0.0001}), camera).dist - smallestDist(subVec3(rayFinalPos, (Vector3){0, 0, 0.01}), camera).dist)};

                    normalize(&normal);

                    // Vector3 pos = absVec3(addVec3(mulVec3(raydir, dist), camera.position));

                    float lightAmmount = fmax((-dotVec3(normal, (Vector3){-1, -1, 0}) + 0.5) * 255 / 2, 0);
                    // printf("%f\n", lightAmmount);

                    color = (Color){smallestDistData.object.color.r, smallestDistData.object.color.g, smallestDistData.object.color.b, lightAmmount};
                    break;
                }
                else if (distAdd < 1)
                {
                    k -= 2;
                }
            }

            ImageDrawRectangle(&imageBuffer, x * SCALEUP, y * SCALEUP, SCALEUP, SCALEUP, color);
        }
    }
}

#endif
