/*******************************************************************************************
 *
 *   raylib [core] example - Basic 3d example
 *
 *   Welcome to raylib!
 *
 *   To compile example, just press F5.
 *   Note that compiled executable is placed in the same folder as .c file
 *
 *   You can find all basic examples on C:\raylib\raylib\examples folder or
 *   raylib official webpage: www.raylib.com
 *
 *   Enjoy using raylib. :)
 *
 *   This example has been created using raylib 1.0 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
 *
 *   Copyright (c) 2013-2023 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib.h"
#include "camera.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#define POINTS_AMMOUNT 8

static void UpdateDrawFrame(void);

FoxCamera camera;
Vector3 points[POINTS_AMMOUNT] = {
    {0, 0, 0},
    {1, 0, 0},
    {1, 1, 0},
    {0, 1, 0},
    {0, 0, 1},
    {1, 0, 1},
    {1, 1, 1},
    {0, 1, 1}};

int main()
{
    NewFoxCamera(&camera);
    const int screenWidth = 450;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "[Fox Engine]");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }
#endif

    CloseWindow();

    return 0;
}

// Update and draw game frame
static void UpdateDrawFrame(void)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);


    render(camera);

    if(IsKeyPressed(KEY_UP))
    {
        camera.position.y++;
    }

    if(IsKeyPressed(KEY_DOWN))
    {
        camera.position.y--;
    }
    if(IsKeyPressed(KEY_W))
    {
        camera.position.z++;
    }

    if(IsKeyPressed(KEY_S))
    {
        camera.position.z--;
    }

    DrawText("This is a raylib example", 10, 40, 20, DARKGRAY);

    DrawFPS(10, 10);

    EndDrawing();
}