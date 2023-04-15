#ifndef FOXSDF_H
#define FOXSDF_H

#include "foxmath.h"

typedef enum SDFType
{
    SDF_SPHERE = 0,
    SDF_PLANE = 1,
    SDF_BOX = 2,
    SDF_TORUS = 3
} SDFType;
typedef struct rayModifer
{
    bool modifys;
    Vector3 position;
    Vector3 rotation;
    float scaler;
} rayModifer;
typedef struct SDFObject
{
    SDFType type;
    Vector3 postion;
    Color color;
    Vector3 scale;
    rayModifer modifer;

} SDFObject;
typedef struct SDFReturn
{
    SDFObject object;
    float dist;
    SDFObject rayEffect;
    float effectDist;

} SDFReturn;

float boxcheapSDF(Vector3 point, Vector3 center, Vector3 scale);
float sphereSDF(Vector3 point, Vector3 sphere, float radius);
float planeSDF(Vector3 point, float y);
float torusSDF(Vector3 point, Vector3 postion, Vector2 size);

#endif