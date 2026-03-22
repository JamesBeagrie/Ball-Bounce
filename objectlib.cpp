#include <math.h>
#include "mathlib.h"
#include "object.h"

void createPolygon(int sides, vec2 c, float radius, Object *obj) {
    for(int i = 0; i < sides; i++) {
        vec2 p1 = {c.x + radius * static_cast<float>(sin(static_cast<double>(2.0f * M_PI * i / sides))), 
                    c.y + radius * static_cast<float>(cos(static_cast<double>(2.0f * M_PI * i / sides)))};
        vec2 p2 = {c.x + radius * static_cast<float>(sin(static_cast<double>(2.0f * M_PI * (i+1.0f) / sides))), 
                    c.y + radius * static_cast<float>(cos(static_cast<double>(2.0f * M_PI * (i+1.0f) / sides)))};
        obj->e.push_back({p1,p2});
    }
}

void createWaveBowl(vec2 c, float width, float height, int segments, Object* obj) {
    float startX = c.x - width * 0.5;
    float dx = width / segments;

    for (int i = 0; i < segments; i++)
    {
        float x1 = startX + i * dx;
        float x2 = startX + (i + 1) * dx;

        float y1 = c.y + sin((float)i / segments * 4.0 * M_PI) * height;
        float y2 = c.y + sin((float)(i+1) / segments * 4.0 * M_PI) * height;

        vec2 p1 = {x1, y1};
        vec2 p2 = {x2, y2};

        obj->e.push_back({p1, p2});
    }
}