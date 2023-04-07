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

FoxCamera camera;

const int screenWidth = 450;
const int screenHeight = 450;






int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    NewFoxCamera(&camera);

    InitWindow(screenWidth, screenHeight, "[foxmoss]");

    SetTargetFPS(60);

    Image imageBuffer = GenImageColor(screenWidth, screenHeight, BLACK);
    Texture displayTexture = LoadTextureFromImage(imageBuffer);

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
            camera.position.y++;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            camera.position.y--;
        }
        if (IsKeyDown(KEY_S))
        {
            camera.position.z--;
        }
        if (IsKeyDown(KEY_W))
        {
            camera.position.z++;
        }

        render(camera, imageBuffer);
        UpdateTexture(displayTexture, imageBuffer.data);
        DrawTexture(displayTexture, 0, 0, WHITE);

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}