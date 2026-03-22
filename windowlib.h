#ifndef WINDOWLIB_H
#define WINDOWLIB_H

#include "mathlib.h"
#include "context.h"

void screenText();

vec2 formatWindowVec2(Context* global_context, const vec2& v);
vec2 reverseFormatWindowVec2(Context* global_context, float x, float y);

#endif