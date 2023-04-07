#ifndef FOXMATH_H
#define FOXMATH_H

#include "raylib.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

float length(Vector3 vector)
{
    float distX = vector.x * vector.x;
    float distY = vector.y * vector.y;
    float distZ = vector.z * vector.z;
    return sqrt(distX + distY + distZ);
}
Vector3 mulVec3(Vector3 x, float y)
{
    return (Vector3){x.x * y, x.y * y, x.z * y};
}
float dotVec3(Vector3 x, Vector3 y)
{
    float dot_product = 0.0;

    dot_product += x.x * y.x;
    dot_product += x.y * y.y;
    dot_product += x.z * y.z;
    return dot_product;
}
Vector3 addVec3(Vector3 x, Vector3 y)
{
    return (Vector3){x.x + y.x, x.y + y.y, x.z + y.z};
}
Vector3 subVec3(Vector3 x, Vector3 y)
{
    return (Vector3){x.x - y.x, x.y - y.y, x.z - y.z};
}
Vector3 maxVec3(Vector3 x, Vector3 y)
{
    return (Vector3){fmax(x.x, y.x), fmax(x.y, y.y), fmax(x.z, y.z)};
}
Vector3 absVec3(Vector3 x)
{
    return (Vector3){fabs(x.x), fabs(x.y), fabs(x.z)};
}
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
float vmax(Vector3 v)
{
    return fmax(fmax(v.x, v.y), v.z);
}
float boxcheapSDF(Vector3 point, Vector3 center, Vector3 scale)
{
    return vmax(subVec3(absVec3(subVec3(point, center)), scale));
}
void normalize(Vector3 *vector)
{
    float len = length(*vector);
    *vector = (Vector3){vector->x / len, vector->y / len, vector->z / len};
}
float clamp(float x, float min, float max)
{
    return fmin(fmax(x, min), max);
}

#endif