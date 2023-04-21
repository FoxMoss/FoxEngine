

#include "foxmath.h"

float length(Vector3 vector)
{
    float distX = vector.x * vector.x;
    float distY = vector.y * vector.y;
    float distZ = vector.z * vector.z;
    return sqrt(distX + distY + distZ);
}
float length2d(Vector2 vector)
{
    float distX = vector.x * vector.x;
    float distY = vector.y * vector.y;
    return sqrt(distX + distY);
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

Vector3 rotVec3(Vector3 x, Axis axis, float rot)
{
    
    Vector3 ret = x;
    if (axis == axisY)
    {

        float c = cos(rot);
        float s = sin(rot);
        //  [c -s    [x    [cx + -sz
        //   s  c] *  z] =  sx +  cz]

        // Personal Best!
        // ret.x = x.x * cos(rot) - x.z * sin(rot);
        // ret.z = x.z * sin(rot) + x.x * cos(rot);
        ret.x = ( c * x.x) + (-s * x.z);
        ret.z = ( s * x.x) + ( c * x.z);
    }

    if (axis == axisX)
    {

        float c = cos(rot);
        float s = sin(rot);
        ret.y = ( c * x.y) + (-s * x.z);
        ret.z = ( s * x.y) + ( c * x.z);
    }
    return ret;
}
float vmax(Vector3 v)
{
    return fmax(fmax(v.x, v.y), v.z);
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