#include <math.h>
#include "mathlib.h"
#include "object.h"
#include "context.h"

void screenText() {
    DrawFPS(5,5);
}

vec2 formatWindowVec2(Context* global_context, const vec2& v) {
    return {static_cast<float>(GetScreenWidth()) / 2 + v.x - global_context->cameraPos.x, 
            static_cast<float>(GetScreenHeight()) / 2 - v.y + global_context->cameraPos.y};
}

vec2 reverseFormatWindowVec2(Context* global_context, float x, float y) {
    return {x + global_context->cameraPos.x - static_cast<float>(GetScreenWidth()) / 2, 
            - y + global_context->cameraPos.y + static_cast<float>(GetScreenHeight()) / 2};
}