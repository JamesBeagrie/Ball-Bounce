#include <math.h>
#include "mathlib.h"
#include "object.h"
#include "context.h"

void screenText() {
    DrawFPS(5,5);
}

vec2 formatWindowVec2(Context* context, const vec2& v) {
    return {static_cast<float>(GetScreenWidth()) / 2 + v.x - context->cameraPos.x, 
            static_cast<float>(GetScreenHeight()) / 2 - v.y + context->cameraPos.y};
}

vec2 reverseFormatWindowVec2(Context* context, float x, float y) {
    return {x + context->cameraPos.x - static_cast<float>(GetScreenWidth()) / 2, 
            - y + context->cameraPos.y + static_cast<float>(GetScreenHeight()) / 2};
}