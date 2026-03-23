#ifndef CONTEXT_H
#define CONTEXT_H

#include <vector>
#include "object.h"
#include "ball.h"
#include "mathlib.h"

enum class FollowType {
    ball,
    ball_delayed,
    mouse,
    none,
};

class GameContext {
    public:
    std::vector<Object> environment;
    Ball ball;
};

class Context {
    public:
    FollowType cameraFollowType;
    vec2 cameraPos;
    GameContext gameContext;
};

#endif