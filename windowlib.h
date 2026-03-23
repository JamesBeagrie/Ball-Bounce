#ifndef WINDOWLIB_H
#define WINDOWLIB_H

#include "mathlib.h"
#include "context.h"

void screenText();

vec2 formatWindowVec2(Context* context, const vec2& v);
vec2 reverseFormatWindowVec2(Context* context, float x, float y);

#endif