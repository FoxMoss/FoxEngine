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

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

FoxCamera camera;

const int screenWidth = 900;
const int screenHeight = 900;

void UpdateDrawFrame(void);

Vector3 newPos;

Image imageBuffer;
Texture displayTexture;

int main(void)
{
    // return 0;
    //  Initialization
    //--------------------------------------------------------------------------------------
    NewFoxCamera(&camera);

    InitWindow(screenWidth, screenHeight, "[foxmoss]");

    SetTargetFPS(120);

    imageBuffer = GenImageColor(screenWidth, screenHeight, BLACK);
    displayTexture = LoadTextureFromImage(imageBuffer);
    DisableCursor();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    CloseWindow();

    return 0;
}
void UpdateDrawFrame(void)
{
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