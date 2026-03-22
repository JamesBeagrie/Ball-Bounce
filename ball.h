#ifndef BALL_H
#define BALL_H

#include "raylib.h"
#include "object.h"
#include "mathlib.h"

class Ball {
    public:
    vec2 p;
    vec2 v;
    vec2 g = {0.0f, -1.0f};
    vec2 r;
    float m = 1.0f;
    float e = 0.0f;
    const float unitsPerMeter = 100.0f;
    int collisionRecursionDepth;
    
    Ball(vec2 p_, vec2 v_, vec2 r_);

    void update(Object* obj);
    void draw(Context* global_context);

    private:
    vec2 collideWithWorld(Object* obj, CollisionPacket* collisionPackage, const vec2& pos, const vec2& vel, vec2* finalVelocity, int collisionRecursionDepth);
    void checkEdge(CollisionPacket* colPackage, const edge &e);
    void updateCollisions(Object* obj, CollisionPacket* collisionPackage, const vec2& pos, const vec2& vel, const vec2& radius);
    void updateCollisionData(CollisionPacket* collisionPackage, const vec2& pos, const vec2& vel);
    float calculateEnergy();
};

#endif