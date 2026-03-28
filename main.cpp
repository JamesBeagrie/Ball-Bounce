#include "raylib.h"
#include "ball.h"
#include "object.h"
#include <math.h>
#include <iostream>
#include "mathlib.h"
#include "context.h"
#include "objectlib.h"
#include "windowlib.h"

bool setup(Context* context) {
    Ball ball({0.0f,0.0f}, {0.0f,0.0f}, {10.0f,10.0f});

    //Object obj;
    //obj.centre = {100.0f , 100.0f};
    //createCircle(&obj, {0.0f,0.0f}, 10.0f, 200.0f, 50.0f, 50, 5);
    createCircleHell(&context->gameContext.environment, {0.0f,0.0f}, 10.0f, 200.0f, 50.0f, 50, 5, 100);
    context->gameContext.ball = ball;

    context->cameraFollowType = FollowType::ball_delayed;
    context->cameraPos = {0.0f,0.0f};
    return true;
}

void update(Context* context) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        vec2 mousePos = reverseFormatWindowVec2(context, static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY()));
        context->gameContext.ball.p = mousePos;
        context->gameContext.ball.v = {0.0f,0.0f};
    }               

    switch(context->cameraFollowType) {
        case FollowType::ball:
            context->cameraPos = context->gameContext.ball.p;
            break;
        case FollowType::ball_delayed:
            context->cameraPos = context->cameraPos + (context->gameContext.ball.p - context->cameraPos)/10.0f;
            break;
        default:
        context->cameraPos = {0.0f,0.0f};
    }
    
    for (auto& obj : context->gameContext.environment) {
        obj.update();
    }
    context->gameContext.ball.update(context->gameContext.environment);
}

void draw(Context* context) {
    BeginDrawing();
    ClearBackground(BLACK);
    for (auto& obj : context->gameContext.environment) {
        obj.draw(context);
    }
    context->gameContext.ball.draw(context);
    screenText();
    EndDrawing();
}

int main(void)
{
    
    Context context;

    if (setup(&context)) {
        std::cout << "Setup complete!" << std::endl;
    }

    InitWindow(800, 600, "Ball Bounce");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        update(&context);
        draw(&context);
    }
    CloseWindow();
    return 0;
}