#include "raylib.h"
#include "object.h"
#include "ball.h"
#include "mathlib.h"
#include <iostream>
#include <iomanip>
#include "windowlib.h"

Ball::Ball(vec2 p_, vec2 v_, vec2 r_) : p(p_), v(v_), r(r_) {}

float Ball::calculateEnergy() {
    const float KE = 0.5f * m * v.squaredLength();
    const float GPE = -p.y * g.y * m;
    return GPE + KE;
}

void Ball::draw(Context* global_context) {
    vec2 drawPos = formatWindowVec2(global_context, p);
    DrawCircle(static_cast<int>(drawPos.x), static_cast<int>(drawPos.y), static_cast<float>(r.x), SKYBLUE);
}

vec2 Ball::collideWithWorld(Object* obj, CollisionPacket* collisionPackage, const vec2& pos, const vec2& vel, vec2* finalVelocity, int collisionRecursionDepth) {
    const float epsilon = 1e-7f;
    const float vLen = vel.len();

    if (collisionRecursionDepth > 50) return pos;
    if (vLen < epsilon) return pos;

    collisionPackage->velocity = vel;
    collisionPackage->normalizedVelocity = vel;
    collisionPackage->normalizedVelocity.normalise();
    collisionPackage->basePoint = pos;
    collisionPackage->foundCollision = false;

    obj->checkCollision(collisionPackage);

    if (collisionPackage->foundCollision == false)  {
        return pos + vel;
    }

    const float t = collisionPackage->nearestDistance;

    float moveT = t;
    if (moveT * vLen > epsilon) {
        moveT -= epsilon / vLen;
    } else {
        moveT = 0.0f;
    }

    vec2 newBasePoint = collisionPackage->basePoint + vel * moveT;

    vec2 slideEdgeNormal = collisionPackage->collisionNormal;
    slideEdgeNormal.normalise();

    *finalVelocity = *finalVelocity - slideEdgeNormal * (1.0f + e) * slideEdgeNormal.dot(*finalVelocity);

    vec2 newVelocityVector = vel - slideEdgeNormal * (1.0f + e) * slideEdgeNormal.dot(vel);
    newVelocityVector = newVelocityVector * (1.0f - t);

    collisionRecursionDepth++;
    return collideWithWorld(obj, collisionPackage, newBasePoint, newVelocityVector, finalVelocity, collisionRecursionDepth);
}

void Ball::updateCollisions(Object* obj, CollisionPacket* collisionPackage, const vec2& pos, const vec2& vel, const vec2& radius) {
    collisionPackage->R2Position = pos;
    collisionPackage->R2Velocity = vel;
    collisionPackage->eRadius = radius;

    vec2 eSpacePosition = collisionPackage->R2Position / collisionPackage->eRadius;
    vec2 eSpaceVelocity = collisionPackage->R2Velocity / collisionPackage->eRadius;

    vec2 finalVelocity = eSpaceVelocity;
    vec2 finalPosition = collideWithWorld(obj, collisionPackage, eSpacePosition,eSpaceVelocity, &finalVelocity, 0);
    
    updateCollisionData(collisionPackage, finalPosition, finalVelocity);
}

void Ball::updateCollisionData(CollisionPacket* collisionPackage, const vec2& pos, const vec2& vel) {
    p = pos * collisionPackage->eRadius;
    v = vel * collisionPackage->eRadius;
}

void Ball::update(Object* obj) {
    v = v + g;
    CollisionPacket collisionPackage;
    updateCollisions(obj, &collisionPackage, p, v, r);
    float e2 = calculateEnergy();
    //std::cout << std::fixed << std::setprecision(8) << "Energy: " << e2 << std::endl;
}