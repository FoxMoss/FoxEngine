#ifndef FOXMATH_H
#define FOXMATH_H

#include "raylib.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

float length(Vector3 vector);
float length2d(Vector2 vector);
Vector3 mulVec3(Vector3 x, float y);
float dotVec3(Vector3 x, Vector3 y);
Vector3 addVec3(Vector3 x, Vector3 y);
Vector3 subVec3(Vector3 x, Vector3 y);
Vector3 maxVec3(Vector3 x, Vector3 y);
Vector3 absVec3(Vector3 x);
typedef enum Axis
{
    axisX = 0,
    axisY = 1,
    axisZ = 2
} Axis;

Vector3 rotVec3(Vector3 x, Axis axis, float rot);
float vmax(Vector3 v);
void normalize(Vector3 *vector);
float clamp(float x, float min, float max);

#endif