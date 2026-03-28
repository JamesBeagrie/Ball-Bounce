#include <math.h>
#include "mathlib.h"
#include "object.h"
#include <utility>
#include <memory>

void rotateAround(Object* obj, vec2 c, float rotation) { // Anticlockwise rotation
    float rotationCos = cos(rotation);
    float rotationSin = sin(rotation);

    for (auto& edge : obj->e) {
        // Just does matrix multiplication without matrix class right now

        edge->v1 = edge->v1 - c;
        edge->v2 = edge->v2 - c;

        edge->v1 = {rotationCos * edge->v1.x - rotationSin * edge->v1.y, rotationSin * edge->v1.x + rotationCos * edge->v1.y};
        edge->v2 = {rotationCos * edge->v2.x - rotationSin * edge->v2.y, rotationSin * edge->v2.x + rotationCos * edge->v2.y};

        edge->v1 = edge->v1 + c;
        edge->v2 = edge->v2 + c;

        edge->d1 = edge->d1 - c;
        edge->d2 = edge->d2 - c;

        edge->d1 = {rotationCos * edge->d1.x - rotationSin * edge->d1.y, rotationSin * edge->d1.x + rotationCos * edge->d1.y};
        edge->d2 = {rotationCos * edge->d2.x - rotationSin * edge->d2.y, rotationSin * edge->d2.x + rotationCos * edge->d2.y};

        edge->d1 = edge->d1 + c;
        edge->d2 = edge->d2 + c;
    }
}

//needs to be reworked for new versions
void createPolygon(Object* obj, int sides, vec2 c, float radius) {
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

//needs to be reworked for new versions
void createWaveBowl(Object* obj, vec2 c, float width, float height, int segments) {
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

void createCircle(Object* obj, vec2 c, float ballRadius, float r, int segments, int holeSegments) {
    for (int i = 0; i < segments; i++) {
        vec2 p1 = {c.x + r * sinf(2.0f * M_PI * i / segments), 
            c.y + r * cosf(2.0f * M_PI * i / segments)};
        vec2 p2 = {c.x + r * sinf(2.0f * M_PI * (i+1.0f) / segments), 
            c.y + r * cosf(2.0f * M_PI * (i+1.0f) / segments)};

        vec2 d1 = -(p1 - c) * 2.0f;
        vec2 d2 = -(p2 - c) * 2.0f;

        d1.normalise();
        d2.normalise();

        if (i < segments - holeSegments) {
            obj->e.push_back(std::make_unique<Edge>(p1,p2,d1,d2, SKYBLUE));
        } else {
            obj->e.push_back(std::make_unique<DetectorEdge>(p1,p2,d1,d2, RED, true, true));
        }
    }
}


void createCircleHell(std::vector<Object>* environment, vec2 c, float ballRadius, float startingRadius, float gap, int segments, int holeSegments, int circleCount) {
    for (int i = 0; i < circleCount; i++) {
        Object obj;
        obj.rotationSpeed = 3.0f * (i+1.0f) / 500.0f;
        createCircle(&obj, c, 0.0f, startingRadius + (i * gap), segments, holeSegments);
        environment->push_back(std::move(obj));
    }
}