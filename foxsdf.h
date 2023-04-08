#ifndef FOXSDF_H
#define FOXSDF_H

#include "foxmath.h"


float boxcheapSDF(Vector3 point, Vector3 center, Vector3 scale)
{
    return vmax(subVec3(absVec3(subVec3(point, center)), scale));
}

typedef enum SDFType
{
    SDF_SPHERE = 0,
    SDF_PLANE = 1,
    SDF_BOX = 2
} SDFType;
typedef struct rayModifer
{
    bool modifys;
    Vector3 position;
    Vector3 rotation;
} rayModifer;
typedef struct SDFObject
{
    SDFType type;
    Vector3 postion;
    Color color;
    float scale;
    rayModifer modifer;

} SDFObject;
typedef struct SDFReturn
{
    SDFObject object;
    float dist;

} SDFReturn;

float sphereSDF(Vector3 point, Vector3 sphere, float radius)
{
    float distX = powf(sphere.x - point.x, 2);
    float distY = powf(sphere.y - point.y, 2);
    float distZ = powf(sphere.z - point.z, 2);
    return sqrt(distX + distY + distZ) - radius;
}

float planeSDF(Vector3 point, float y)
{
    return point.y - y;
}

#endif