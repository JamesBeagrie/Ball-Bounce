#include "raylib.h"
#include "ball.h"
#include "object.h"
#include <math.h>
#include <iostream>
#include "mathlib.h"

void screenText() {
    DrawFPS(5,5);
}

void createPolygon(int sides, vec2 c, double radius, Object *obj) {
    for(int i = 0; i < sides; i++) {
        vec2 p1 = {static_cast<double>(c.x + radius * sin(2.0f * M_PI * i / sides)), 
                    static_cast<double>(c.y + radius * cos(2.0f * M_PI * i / sides))};
        vec2 p2 = {static_cast<double>(c.x + radius * sin(2.0f * M_PI * (i+1.0f) / sides)), 
                    static_cast<double>(c.y + radius * cos(2.0f * M_PI * (i+1.0f) / sides))};
        obj->e.push_back({p1,p2});
    }
}

void createWaveBowl(vec2 c,
                    double width,
                    double height,
                    int segments,
                    Object* obj)
{
    double startX = c.x - width * 0.5;
    double dx = width / segments;

    for (int i = 0; i < segments; i++)
    {
        double x1 = startX + i * dx;
        double x2 = startX + (i + 1) * dx;

        double y1 = c.y + sin((double)i / segments * 4.0 * M_PI) * height;
        double y2 = c.y + sin((double)(i+1) / segments * 4.0 * M_PI) * height;

        vec2 p1 = {x1, y1};
        vec2 p2 = {x2, y2};

        obj->e.push_back({p1, p2});
    }
}

int main(void)
{
    const vec2 center = vec2(400.0, 300.0);

    Object obj;
    // Pos, Vel, Radius
    Ball ball({440,400}, {0.0,0.0}, {10.0,10.0});
    bool update = true;


    InitWindow(800, 600, "raylib works");
    SetTargetFPS(60);

    createPolygon(70,{400,300}, 200, &obj);

    while (!WindowShouldClose())
    {
        // Calculate update

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            vec2 mousePos = {static_cast<double>(GetMouseX()),static_cast<double>(GetMouseY())};
            ball.p = mousePos;
            ball.v = {0.0,0.0};
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

        obj.draw(ball.p - center);
        ball.draw(ball.p - center);
        screenText();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}