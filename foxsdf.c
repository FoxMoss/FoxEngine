#include "foxsdf.h"

float boxcheapSDF(Vector3 point, Vector3 center, Vector3 scale)
{
    return vmax(subVec3(absVec3(subVec3(point, center)), scale));
}
float sphereSDF(Vector3 point, Vector3 sphere, float radius)
{
    //float c= 15;
    //point.x = fmod(point.x + 0.5*c, 5) - 0.5*c;
    //point.y = fmod(point.y + 0.5*c, 5) - 0.5*c;
    float distX = powf(sphere.x - point.x, 2);
    float distY = powf(sphere.y - point.y, 2);
    float distZ = powf(sphere.z - point.z, 2);
    return sqrt(distX + distY + distZ) - radius;
}
float planeSDF(Vector3 point, float y)
{
    return point.y - y;
}
float torusSDF(Vector3 point, Vector3 postion, Vector2 size)
{
    point = subVec3(point, postion);
    Vector2 q = (Vector2){length2d((Vector2){point.x, point.y}) - size.x, point.z};
    return length2d(q) - size.y;
}