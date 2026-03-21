#ifndef BALL_H
#define BALL_H

#include "raylib.h"
#include "object.h"
#include "mathlib.h"

class Ball {
    public:
    vec2 p;
    vec2 v;
    vec2 g = {0.0, 1.0};
    vec2 r;
    double m = 1.0;
    double e = 0.0;
    const double unitsPerMeter = 100.0;
    int collisionRecursionDepth;
    
    Ball(vec2 p_, vec2 v_, vec2 r_) : p(p_), v(v_), r(r_) {}

    void update(Object* obj);
    void draw(const vec2& centre);

    private:
    vec2 collideWithWorld(Object* obj, CollisionPacket* collisionPackage, const vec2& pos, const vec2& vel, vec2* finalVelocity, int collisionRecursionDepth);
    void checkEdge(CollisionPacket* colPackage, const edge &e);
    void updateCollisions(Object* obj, CollisionPacket* collisionPackage, const vec2& pos, const vec2& vel, const vec2& radius);
    void updateCollisionData(CollisionPacket* collisionPackage, const vec2& pos, const vec2& vel);
    double calculateEnergy();
};

#endif