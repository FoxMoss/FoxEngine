#include "camera.h"

void NewFoxCamera(FoxCamera *cam)
{
    cam->position = (Vector3){0, 5, 0};
    cam->rotation = (Vector3){0, 0, 0};
    cam->invWidth = 1 / (float)WIDTH;
    cam->invHeight = 1 / (float)HEIGHT;
    cam->fov = 90;
    cam->aspectratio = WIDTH / (float)HEIGHT;
    cam->angle = tan(PI * 0.5 * cam->fov / 180.);
    // this->*framebuffer = malloc(camera.width * camera.height * sizeof(Vector3));
}

SDFReturn smallestDist(Vector3 point, FoxCamera camera, SDFLevel level)
{

    /*SDFObject objects[3] = {{SDF_PLANE, {2, 0, 10}, WHITE, {0, 0, 0}, (rayModifer){false}, false},
                            {SDF_BOX, {9, 4, 10}, BLUE, 5, (rayModifer){false, {-5, 0, 0}, {0, 0, 0}}},
                            {SDF_TORUS, {0, 4, 10}, RED, {3, 0.1, 1}, (rayModifer){false}, false},
                            {SDF_SPHERE, {0, 4, 10}, BLUE, {3, 2, 1}, (rayModifer){false, (Vector3){0, 0, 0}, (Vector3){0, 0, 0}, 1}, true, true}};
*/
    float smallest = INFINITY;
    SDFObject object = level.objects[0];
    SDFObject rayEffect = level.objects[0];
    float effectDist = INFINITY;

    //printf("\n%b\n", level[1][5]);

    float lastSmallest = INFINITY;

    for (int i = 0; i < level.size; i++)
    {
        lastSmallest = smallest;
        // Vector3 calculatedPosition = objects[i].postion;
        switch (level.objects[i].type)
        {
        case SDF_SPHERE:
            smallest = fminf(smallest, sphereSDF(point, level.objects[i].postion, level.objects[i].scale.y));
            break;
        case SDF_PLANE:
            smallest = fminf(smallest, planeSDF(point, level.objects[i].postion.y));
            break;
        case SDF_BOX:
            smallest = fminf(smallest, boxcheapSDF(point, level.objects[i].postion, level.objects[i].scale));
            // amallest += sphereSDF(point, objects[2].postion, objects[2].scale);
            break;
        case SDF_TORUS:
            smallest = fminf(smallest, torusSDF(point, level.objects[i].postion, (Vector2){level.objects[i].scale.x, level.objects[i].scale.y}));
            break;
        default:
            printf("ERROR: Undf object: %i \n", level.objects[i].type);
            break;
        }
        if (lastSmallest != smallest)
        {
            if (level.objects[i].modifer.modifys)
            {
                rayEffect = level.objects[i];
                effectDist = smallest;
                //smallest = fmax(smallest, 0.9);
                //smallest = fmin(lastSmallest, smallest);
            }
            else
            {
                object = level.objects[i];
            }
        }
        
    }

    return (SDFReturn){object, lastSmallest, smallest, rayEffect, effectDist};
}

void render(FoxCamera *cameraP, Image imageBuffer, SDFLevel level)
{
    float xx = 0;
    float yy = 0;
    Color color = BLACK;

    FoxCamera camera = *cameraP;

    SDFReturn cameraDist = smallestDist(camera.position, camera, level);

    if (cameraDist.effectDist < 0.5)
    {
        camera.rotation = addVec3(camera.rotation, cameraDist.rayEffect.modifer.rotation);
        camera.position = addVec3(camera.position, cameraDist.rayEffect.modifer.position);
    }
    cameraP->position = camera.position;
    cameraP->rotation = camera.rotation;
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

            int steps = 10;
            bool portal = false;
            //color = (Color){fabs(raydir.x) * 100, fabs(raydir.y) * 100, 0, 255};
            color = BLACK;
            if (!IsKeyDown(KEY_R))
            {
                steps = 30;
            }
            bool close = 0;
            int k = 0;
            float rotation = 0;
            for (k = 0; k < steps; ++k)
            {
                Vector3 calculatedPosition = addVec3(mulVec3(rotVec3(raydir, axisY, rotation), dist), rayOffset);
                SDFReturn smallestDistData = smallestDist(calculatedPosition, camera, level);

                float distAdd = smallestDistData.dist;
                // printf("dist: %f\n point: (x: %f, y: %f, z: %f)", smallestDist, mulVec3(raydir, dist).x, mulVec3(raydir, dist).y, mulVec3(raydir, dist).z);

                dist += distAdd;
                if (smallestDistData.effectDist < 0.1)
                {
                    portal = true;
                    //rayOffset = addVec3(rayOffset, smallestDistData.rayEffect.modifer.position);
                    //rotation += smallestDistData.rayEffect.modifer.rotation.y;
                    //dist = dist*smallestDistData.rayEffect.modifer.scaler;
                    //Vector3 david = subVec3(rayOffset, smallestDistData.rayEffect.postion);
                    //rayOffset = addVec3(mulVec3(david, smallestDistData.rayEffect.modifer.scaler), rayOffset
                    continue;
                }
                if (distAdd < 0.1)
                {
                    if (smallestDistData.object.reflect)
                    {
                        Vector3 normal = (Vector3){
                            (smallestDist(addVec3(calculatedPosition, (Vector3){0.0001, 0, 0}), camera, level).dist - smallestDist(subVec3(calculatedPosition, (Vector3){0.01, 0, 0}), camera, level).dist),
                            (smallestDist(addVec3(calculatedPosition, (Vector3){0, 0.0001, 0}), camera, level).dist - smallestDist(subVec3(calculatedPosition, (Vector3){0, 0.01, 0}), camera, level).dist),
                            (smallestDist(addVec3(calculatedPosition, (Vector3){0, 0, 0.0001}), camera, level).dist - smallestDist(subVec3(calculatedPosition, (Vector3){0, 0, 0.01}), camera, level).dist)};

                        normalize(&normal);

                        rayOffset = calculatedPosition;

                        raydir = subVec3(raydir, mulVec3(normal, 2 * dotVec3(raydir, normal)));
                        dist = 0;

                        steps += 1;
                        continue;
                    }
                    float lightAmmount = 50;
                    if (smallestDistData.object.type != SDF_PLANE)
                    {

                        Vector3 normal = (Vector3){
                            (smallestDist(addVec3(calculatedPosition, (Vector3){0.0001, 0, 0}), camera, level).dist - smallestDist(subVec3(calculatedPosition, (Vector3){0.01, 0, 0}), camera, level).dist),
                            (smallestDist(addVec3(calculatedPosition, (Vector3){0, 0.0001, 0}), camera, level).dist - smallestDist(subVec3(calculatedPosition, (Vector3){0, 0.01, 0}), camera, level).dist),
                            (smallestDist(addVec3(calculatedPosition, (Vector3){0, 0, 0.0001}), camera, level).dist - smallestDist(subVec3(calculatedPosition, (Vector3){0, 0, 0.01}), camera, level).dist)};

                        normalize(&normal);

                        // Vector3 pos = absVec3(addVec3(mulVec3(raydir, dist), camera.position));

                        lightAmmount = fmin(fmax((-dotVec3(normal, (Vector3){-1, -1, 0}) + 0.5) * 255 / 2, 0) + 50, 255);
                        // printf("%f\n", lightAmmount);
                    }
                    else
                    {
                        if (((int)(calculatedPosition.z / 5) % 2) == 0 && ((int)(calculatedPosition.x / 5) % 2) == 0)
                        {
                            lightAmmount = 100;
                        }
                    }

                    color = (Color){smallestDistData.object.color.r*lightAmmount/255, smallestDistData.object.color.g*lightAmmount/255, smallestDistData.object.color.b*lightAmmount/255, 255};
                    break;
                }
                else if (distAdd < 1 && smallestDistData.object.type != SDF_PLANE)
                {
                    steps += 1;
                }
            }
            // ImageDrawRectangle(&imageBuffer, x * SCALEUP, y * SCALEUP, SCALEUP, SCALEUP, (Color) {k, k, k, 255});
            //color = ColorTint((Color){color.r, color.g, color.b, 255}, (Color){color.a, color.a, color.a, 255});

            if (steps == k)
            {
                color = BLANK;
            }

            ImageDrawRectangle(&imageBuffer, x * SCALEUP, y * SCALEUP, SCALEUP, SCALEUP, color);
        }
    }
}
