#include "raylib.h"
#include "camera.h"
#include "levels.h"
#include "upscale.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

FoxCamera camera;
int step = 4;

Vector3 newPos;
Texture2D torus;

const int screenWidth = 900;
const int screenHeight = 900;

void UpdateDrawFrame(void);

Image imageBuffer;
Image stars;
Texture2D starsTexture;

Texture displayTexture;
Font hackfont;
Music music;

SDFLevel *levels;
int main(void)
{
    // return 0;
    NewFoxCamera(&camera);

    InitWindow(screenWidth, screenHeight, "[foxmoss]");

    // Images:
    Image image = LoadImage("resources/torus.png");
    torus = LoadTextureFromImage(image);
    UnloadImage(image);
    hackfont = LoadFont("resources/hack.ttf");

    levels = initLevels();

    imageBuffer = GenImageColor(screenWidth, screenHeight, BLACK);
    stars = GenImageColor(screenWidth, screenHeight, BLACK);
    for (int y = 0; y < screenHeight; y++)
    {
        for (int x = 0; x < screenWidth; x++)
        {
            if (rand() % 100 == 0)
            {
                ImageDrawPixel(&stars, x, y, WHITE);
            }
        }
    }
    ImageBlurGaussian(&stars, 1);

    starsTexture = LoadTextureFromImage(stars);

    displayTexture = LoadTextureFromImage(imageBuffer);
    DisableCursor();

    InitAudioDevice();
    music = LoadMusicStream("resources/desertcave.mp3");
    PlayMusicStream(music);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 30, 1);
#else
    SetTargetFPS(30);


    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }
#endif

    UnloadTexture(displayTexture);
    UnloadImage(imageBuffer);
    UnloadTexture(torus);
    UnloadMusicStream(music);

    CloseAudioDevice();
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
    /*if (newPos.x == 0 && newPos.y == 0 && newPos.z == 0 && mouseDelta.x == 0 && mouseDelta.y == 0)
    {

        DrawTexture(displayTexture, 0, 0, WHITE);
        return;
    }*/
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

    if (cameraDist.dist < 0.3)
    {
        Vector3 normal = (Vector3){
            (smallestDist(addVec3(newPos, (Vector3){0.0001, 0, 0}), camera, level).dist - smallestDist(subVec3(newPos, (Vector3){0.0001, 0, 0}), camera, level).dist),
            (smallestDist(addVec3(newPos, (Vector3){0, 0.0001, 0}), camera, level).dist - smallestDist(subVec3(newPos, (Vector3){0, 0.0001, 0}), camera, level).dist),
            (smallestDist(addVec3(newPos, (Vector3){0, 0, 0.0001}), camera, level).dist - smallestDist(subVec3(newPos, (Vector3){0, 0, 0.0001}), camera, level).dist)};

        normalize(&normal);
        normal = mulVec3(normal, -cameraDist.dist + 0.3);
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
    if (cameraDist.dist < 0.3)
    {
        if (cameraDist.object.wins)
        {
            step++;
        }
    }
    if (cameraDist.effectDist < 0.3)
    {
        if (cameraDist.rayEffect.wins)
        {
            step++;
        }
    }

    // cameraDist = smallestDist(camera.position, camera, level1);

    render(&camera, imageBuffer, level);
    //upscaleImage(&imageBuffer, 18);
    UpdateTexture(displayTexture, imageBuffer.data);

    DrawTexture(displayTexture, 0, 0, WHITE);

}

void sequenceStart()
{
    switch (step)
    {
    case 0:
        if (IsKeyPressed(KEY_SPACE))
        {
            step++;

            NewFoxCamera(&camera);
        }
        break;
    case 1:
        break;
    case 2:
        if (IsKeyPressed(KEY_SPACE))
        {
            step++;

            NewFoxCamera(&camera);
        }
        break;
    case 3:
        break;

    case 4:
        if (IsKeyPressed(KEY_SPACE))
        {
            step++;

            NewFoxCamera(&camera);
        }
        break;

    case 5:
        break;

    default:
        if (IsKeyPressed(KEY_SPACE))
        {
            step = 0;
        }
        break;
    }
    BeginDrawing();

    ClearBackground(BLACK);

    DrawTexture(starsTexture, 0, 0, WHITE);
    switch (step)
    {
    case 0:
        DrawTextEx(hackfont, "ENTER THE ", (Vector2){300, 155}, 50, 10, RED);
        DrawTextEx(hackfont, "(space to begin)", (Vector2){300, 600}, 30, 5, GRAY);
        DrawTexture(torus, 340, 270, WHITE);
        break;
    case 1:
        gameSequence(levels[0]);
        break;
    case 2:
        DrawTextEx(hackfont, "ALL SPACE AND TIME\nCONFORM TO TAMPERING\nOF THE [DOUGHNUT]", (Vector2){100, 100}, 50, 10, RED);

        DrawTextEx(hackfont, "(space to continue)", (Vector2){300, 600}, 30, 5, GRAY);
        break;
    case 3:
        gameSequence(levels[1]);
        break;
    
    case 4:
        DrawTextEx(hackfont, "THE [DOUGHNUT] DOES\nNOT LIKE YOU >:(", (Vector2){100, 100}, 50, 10, RED);
        DrawTextEx(hackfont, "[cube] is friend tho :P\nhave some [cube]", (Vector2){100, 250}, 40, 10, BLUE);

        DrawTextEx(hackfont, "(space to continue)", (Vector2){300, 600}, 30, 5, GRAY);
        break;
    case 5:
        gameSequence(levels[2]);
        break;

    default:
        DrawTextEx(hackfont, "END DEMO", (Vector2){300, 155}, 50, 10, RED);
        DrawTextEx(hackfont, "(space to reset)", (Vector2){300, 600}, 30, 5, GRAY);
        break;
    }

    DrawFPS(10, 10);
    EndDrawing();
}
void UpdateDrawFrame(void)
{
    UpdateMusicStream(music);
    sequenceStart();
}
