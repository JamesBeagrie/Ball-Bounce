#include "raylib.h"
#include "object.h"
#include "ball.h"
#include "mathlib.h"
#include <iostream>
#include <iomanip>
#include "windowlib.h"

Ball::Ball(vec2 p_, vec2 v_, vec2 r_) : p(p_), v(v_), r(r_) {}

Ball::Ball() : p({0.0f,0.0f}), v({0.0f,0.0f}), r({0.0f,0.0f}) {}

float Ball::calculateEnergy() {
    const float KE = 0.5f * m * v.squaredLength();
    const float GPE = p.y * g.y * m;
    return GPE + KE;
}

void Ball::draw(Context* context) {
    vec2 drawPos = formatWindowVec2(context, p);
    DrawCircle(static_cast<int>(drawPos.x), static_cast<int>(drawPos.y), static_cast<float>(r.x), SKYBLUE);
}

vec2 Ball::collideWithWorld(std::vector<std::unique_ptr<Object>>& environment, CollisionPacket* collisionPackage, const vec2& pos, const vec2& vel, vec2* finalVelocity, int collisionRecursionDepth) {
    const float epsilon = 1e-7f;
    const float vLen = vel.len();

    if (collisionRecursionDepth > 50) return pos;
    if (vLen < epsilon) return pos;

    collisionPackage->velocity = vel;
    collisionPackage->normalizedVelocity = vel;
    collisionPackage->normalizedVelocity.normalise();
    collisionPackage->basePoint = pos;
    collisionPackage->foundCollision = false;

    for (auto& obj : environment) {
        obj->checkCollision(collisionPackage);
    }

    if (collisionPackage->foundCollision == false)  {
        return pos + vel;
    }

    // start of edge check
    CollisionResponseData collisionResponseData;
    collisionPackage->nearestEdge->collisionResponse(&collisionResponseData);

    if (collisionResponseData.deleteOwnObj) {
        std::cout << "Hit Detector Edge" << std::endl;
        collisionPackage->nearestObj->isDead = true;
        collisionRecursionDepth++;
        return collideWithWorld(environment, collisionPackage, pos, vel, finalVelocity, collisionRecursionDepth);
    }
    // end of edge check

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
    return collideWithWorld(environment, collisionPackage, newBasePoint, newVelocityVector, finalVelocity, collisionRecursionDepth);
}

void Ball::updateCollisions(std::vector<std::unique_ptr<Object>>& environment, CollisionPacket* collisionPackage, const vec2& pos, const vec2& vel, const vec2& radius) {
    collisionPackage->R2Position = pos;
    collisionPackage->R2Velocity = vel;
    collisionPackage->eRadius = radius;

    vec2 eSpacePosition = collisionPackage->R2Position / collisionPackage->eRadius;
    vec2 eSpaceVelocity = collisionPackage->R2Velocity / collisionPackage->eRadius;

    vec2 finalVelocity = eSpaceVelocity;
    vec2 finalPosition = collideWithWorld(environment, collisionPackage, eSpacePosition,eSpaceVelocity, &finalVelocity, 0);
    
    updateCollisionData(collisionPackage, finalPosition, finalVelocity);
}

void Ball::updateCollisionData(CollisionPacket* collisionPackage, const vec2& pos, const vec2& vel) {
    p = pos * collisionPackage->eRadius;
    v = vel * collisionPackage->eRadius;
}

void Ball::update(std::vector<std::unique_ptr<Object>>& environment) {
    v = v + g;
    CollisionPacket collisionPackage;
    updateCollisions(environment, &collisionPackage, p, v, r);
    float e2 = calculateEnergy();
    //std::cout << std::fixed << std::setprecision(8) << "Energy: " << e2 << std::endl;
}