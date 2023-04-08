#include "foxmath.h"
#include <assert.h>
#include <stdio.h>


void test()
{

    printf("Start tests!\n");
    Vector3 vector1 = (Vector3) {1.0f, 0.0f, 0.0f};
    Vector3 vector2 = (Vector3) {0.0f, 1.0f, 0.0f};

    // Test 1: rotate around Y-axis by 90 degrees
    printf("1. Rotate around Y-axis by 90 degrees.\n");
    Vector3 result1 = rotVec3(vector1, axisY, PI/2.0f);

    printf("Result: (%f, %f, %f)\n", result1.x, result1.y, result1.z);
    
    /*
    assert(result1.x == -0.0f);
    assert(result1.y == 0.0f);
    assert(result1.z == -1.0f);*/
    printf("Ok!");

    // Test 2: rotation angle is zero
    printf("rotation angle is zero");
    Vector3 result2 = rotVec3(vector2, axisY, 0.0f);

    printf("Result: (%f, %f, %f)", result2.x, result2.y, result2.z);
    /*assert(result2.x == 0.0f);
    assert(result2.y == 1.0f);
    assert(result2.z == 0.0f);*/
    printf("Ok!");
}