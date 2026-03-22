#ifndef CONTEXT_H
#define CONTEXT_H

enum class FollowType
{
    ball,
    ball_delayed,
    mouse,
    mouse_delayed,
    none,
};

class Context
{
    public:
    FollowType cameraFollowType;
    vec2 cameraPos;
};

#endif