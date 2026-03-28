#ifndef BALL_H
#define BALL_H

#include "raylib.h"
#include "object.h"
#include "mathlib.h"

class Context;

class Ball {
    public:
    vec2 p;
    vec2 v;
    vec2 g = {0.0f, 0.0f};
    vec2 r;
    float m = 1.0f;
    float e = 1.0f;
    static constexpr float unitsPerMeter = 100.0f;
    int collisionRecursionDepth;
    
    Ball(vec2 p_, vec2 v_, vec2 r_);
    Ball();

    void update(std::vector<Object>& environment);
    void draw(Context* context);

    private:
    vec2 collideWithWorld(std::vector<Object>& environment, CollisionPacket* collisionPackage, const vec2& pos, const vec2& vel, vec2* finalVelocity, int collisionRecursionDepth);
    void updateCollisions(std::vector<Object>& environment, CollisionPacket* collisionPackage, const vec2& pos, const vec2& vel, const vec2& radius);
    void updateCollisionData(CollisionPacket* collisionPackage, const vec2& pos, const vec2& vel);
    float calculateEnergy();
};

#endif