#include "foxsdf.h"

float boxcheapSDF(Vector3 point, Vector3 center, Vector3 scale)
{
    return vmax(subVec3(absVec3(subVec3(point, center)), scale));
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