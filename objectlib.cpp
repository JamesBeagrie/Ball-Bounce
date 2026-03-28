#include <math.h>
#include "mathlib.h"
#include "object.h"
#include <memory>

void createPolygon(int sides, vec2 c, float radius, Object *obj) {
    for(int i = 0; i < sides; i++) {
        vec2 p1 = {c.x + radius * static_cast<float>(sin(static_cast<double>(2.0f * M_PI * i / sides))), 
                    c.y + radius * static_cast<float>(cos(static_cast<double>(2.0f * M_PI * i / sides)))};
        vec2 p2 = {c.x + radius * static_cast<float>(sin(static_cast<double>(2.0f * M_PI * (i+1.0f) / sides))), 
                    c.y + radius * static_cast<float>(cos(static_cast<double>(2.0f * M_PI * (i+1.0f) / sides)))};

        vec2 d1 = {0.0f,0.0f};
        vec2 d2 = {0.0f,0.0f};

        obj->e.push_back(std::make_unique<Edge>(p1,p2,d1,d2));
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
        vec2 d1 = {0.0f,0.0f};
        vec2 d2 = {0.0f,0.0f};

        obj->e.push_back(std::make_unique<Edge>(p1,p2,d1,d2));
    }
}

void createCircleHell(vec2 c, float startingRadius, float gap, float holeAngle, int segments, int holeSegments, int circleCount, std::vector<Object> environment) {

}

void createCircle(Object* obj, vec2 c, float ballRadius, float startingRadius, float gap, float holeAngle, int segments, int holeSegments) {
    for (int i = 0; i < segments; i++) {
        vec2 p1 = {c.x + (startingRadius + gap) * static_cast<float>(sin(static_cast<double>(2.0f * M_PI * i / segments))), 
            c.y + (startingRadius + gap) * static_cast<float>(cos(static_cast<double>(2.0f * M_PI * i / segments)))};
        vec2 p2 = {c.x + (startingRadius + gap) * static_cast<float>(sin(static_cast<double>(2.0f * M_PI * (i+1.0f) / segments))), 
            c.y + (startingRadius + gap) * static_cast<float>(cos(static_cast<double>(2.0f * M_PI * (i+1.0f) / segments)))};

        vec2 d1 = -(p1 - c) / 100.0f;
        vec2 d2 = -(p2 - c) / 100.0f;

        if (i < segments - holeSegments) {
            obj->e.push_back(std::make_unique<Edge>(p1,p2,d1,d2, SKYBLUE));
        } else {
            obj->e.push_back(std::make_unique<DetectorEdge>(p1,p2,d1,d2, RED, true));
        }
    }
}