/*******************************************************************************************
 *
 *   raylib [core] example - Basic window
 *
 *   Welcome to raylib!
 *
 *   To test examples, just press F6 and execute raylib_compile_execute script
 *   Note that compiled executable is placed in the same folder as .c file
 *
 *   You can find all basic examples on C:\raylib\raylib\examples folder or
 *   raylib official webpage: www.raylib.com
 *
 *   Enjoy using raylib. :)
 *
 *   Example originally created with raylib 1.0, last time updated with raylib 1.0
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
 *   BSD-like license that allows static linking with closed source software
 *
 *   Copyright (c) 2013-2023 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib.h"
#include "camera.h"
#include "testsmath.c"

FoxCamera camera;

const int screenWidth = 450;
const int screenHeight = 450;

int main(void)
{
    test();
    // return 0;
    //  Initialization
    //--------------------------------------------------------------------------------------
    NewFoxCamera(&camera);

    InitWindow(screenWidth, screenHeight, "[foxmoss]");

    SetTargetFPS(60);

    Image imageBuffer = GenImageColor(screenWidth, screenHeight, BLACK);
    Texture displayTexture = LoadTextureFromImage(imageBuffer);
    DisableCursor();

    Vector3 newPos;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        if (IsKeyDown(KEY_UP))
        {
            newPos.y += 0.3;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            newPos.y -= 0.3;
        }
        if (IsKeyDown(KEY_S))
        {
            newPos.z -= 0.3;
        }
        if (IsKeyDown(KEY_W))
        {
            newPos.z += 0.3;
        }
        if (IsKeyDown(KEY_A))
        {
            newPos.x -= 0.3;
        }
        if (IsKeyDown(KEY_D))
        {
            newPos.x += 0.3;
        }
        Vector2 mouseDelta = GetMouseDelta();
        camera.rotation.y -= mouseDelta.x / 1000;
        camera.rotation.x += mouseDelta.y / 1000;
        newPos = rotVec3(newPos, axisY, camera.rotation.y);
        camera.position = addVec3(newPos, camera.position);
        newPos = (Vector3){0, 0, 0};

        render(camera, imageBuffer);
        UpdateTexture(displayTexture, imageBuffer.data);
        DrawTexture(displayTexture, 0, 0, WHITE);

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}