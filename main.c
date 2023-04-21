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
#include "levels.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

FoxCamera camera;
int step = 0;

Vector3 newPos;
Texture2D torus;

const int screenWidth = 900;
const int screenHeight = 900;

void UpdateDrawFrame(void);

Image imageBuffer;


Texture displayTexture;
Font hackfont;

SDFLevel* levels;
int main(void)
{
    // return 0;
    //  Initialization
    //--------------------------------------------------------------------------------------

    NewFoxCamera(&camera);

    InitWindow(screenWidth, screenHeight, "[foxmoss]");


    // Images:
    Image image = LoadImage("resources/torus.png");
    torus = LoadTextureFromImage(image);
    UnloadImage(image);
    hackfont = LoadFont("resources/hack.ttf");

    levels = initLevels();

    imageBuffer = GenImageColor(screenWidth, screenHeight, BLACK);
    displayTexture = LoadTextureFromImage(imageBuffer);
    DisableCursor();

    //level1 = InitLevels();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(30); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    UnloadTexture(displayTexture);
    UnloadImage(imageBuffer);
    UnloadTexture(torus);
    CloseWindow();

    return 0;
}

void gameSequence(SDFLevel level)
{

    newPos = (Vector3){0, 0, 0};

    /*if (IsKeyDown(KEY_UP))
    {
        newPos.y += 0.3;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        newPos.y -= 0.3;
    }*/
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
    newPos = addVec3(newPos, camera.position);

    SDFReturn cameraDist = smallestDist((Vector3){newPos.x, newPos.y, newPos.z}, camera, level);

    if (cameraDist.effectDist < 0.5)
    {
        camera.rotation = addVec3(camera.rotation, cameraDist.rayEffect.modifer.rotation);
        newPos = addVec3(newPos, cameraDist.rayEffect.modifer.position);
    }

    if (cameraDist.dist < 0.1)
    {
        Vector3 normal = (Vector3){
            (smallestDist(addVec3(newPos, (Vector3){0.0001, 0, 0}), camera, level).dist - smallestDist(subVec3(newPos, (Vector3){0.01, 0, 0}), camera, level).dist),
            (smallestDist(addVec3(newPos, (Vector3){0, 0.0001, 0}), camera, level).dist - smallestDist(subVec3(newPos, (Vector3){0, 0.01, 0}), camera, level).dist),
            (smallestDist(addVec3(newPos, (Vector3){0, 0, 0.0001}), camera, level).dist - smallestDist(subVec3(newPos, (Vector3){0, 0, 0.01}), camera, level).dist)};

        normalize(&normal);
        normal = mulVec3(normal, 0.3);
        normal.y = 0;

        newPos = addVec3(newPos, normal);

        /*
        newPos.x = camera.position.x;
        cameraDist = smallestDist((Vector3){newPos.x, newPos.y, newPos.z}, camera, level1);
        if (cameraDist.dist < 0.1)
        {
            newPos.y = camera.position.y;

            cameraDist = smallestDist((Vector3){newPos.x, newPos.y, newPos.z}, camera, level1);
            if (cameraDist.dist < 0.1)
            {
                newPos.z = camera.position.z;

                cameraDist = smallestDist((Vector3){newPos.x, newPos.y, newPos.z}, camera, level1);
            }
        }*/
    }

    camera.position = newPos;
    newPos = (Vector3){0, 0, 0};
    if (cameraDist.dist < 0.1)
    {
        if (cameraDist.object.wins)
        {
            step++;
        }
    }

    // cameraDist = smallestDist(camera.position, camera, level1);

    render(&camera, imageBuffer, level);
    UpdateTexture(displayTexture, imageBuffer.data);
    DrawTexture(displayTexture, 0, 0, WHITE);

    DrawFPS(10, 10);
}

void sequenceStart()
{

    BeginDrawing();

    ClearBackground(BLACK);

    switch (step)
    {
    case 0:
        DrawTextEx(hackfont, "ENTER THE ", (Vector2){300, 155}, 50, 10, RED);
        DrawTextEx(hackfont, "(space to begin)", (Vector2){300, 600}, 30, 5, GRAY);
        DrawTexture(torus, 340, 270, WHITE);
        if (IsKeyPressed(KEY_SPACE))
        {
            step++;

            NewFoxCamera(&camera);
        }
        break;
    case 1:
        gameSequence(levels[0]);
        break;

    default:
        DrawTextEx(hackfont, "END DEMO", (Vector2){300, 155}, 50, 10, RED);
        DrawTextEx(hackfont, "(space to reset)", (Vector2){300, 600}, 30, 5, GRAY);
        if (IsKeyPressed(KEY_SPACE))
        {
            step = 0;
        }
        break;
    }

    EndDrawing();
}
void UpdateDrawFrame(void)
{
    sequenceStart();
}
