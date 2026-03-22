#include "raylib.h"
#include "ball.h"
#include "object.h"
#include <math.h>
#include <iostream>
#include "mathlib.h"
#include "context.h"
#include "objectlib.h"
#include "windowlib.h"

int main(void)
{
    Object obj;
    obj.centre = {0.0f,0.0f};
    Context global_context;
    global_context.cameraFollowType = FollowType::ball_delayed;
    global_context.cameraPos = {0.0f,0.0f};

    Ball ball({0.0f,0.0f}, {0.0f,0.0f}, {10.0f,10.0f}); // Pos, Vel, Radius
    bool update = true;

    InitWindow(800, 600, "Ball Bounce");
    SetTargetFPS(60);

    createWaveBowl({0.0f,0.0f}, 1000.0f, 200.0f, 200, &obj);

    while (!WindowShouldClose())
    {
        // Calculate update
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            vec2 mousePos = reverseFormatWindowVec2(&global_context, static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY()));
            ball.p = mousePos;
            ball.v = {0.0f,0.0f};
        }               

        switch(global_context.cameraFollowType) {
            case FollowType::ball:
                global_context.cameraPos = ball.p;
                break;
            case FollowType::ball_delayed:
                global_context.cameraPos = global_context.cameraPos + (ball.p - global_context.cameraPos)/10.0f;
                break;
            default:
            global_context.cameraPos = {0.0f,0.0f};
        }

        if (IsKeyPressed(32)) {
            update = false;
        }
        if (update) {
            ball.update(&obj);
        }

        // End update

        BeginDrawing();
        ClearBackground(BLACK);

        // Start image generation

        obj.draw(&global_context);
        ball.draw(&global_context);
        screenText();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}