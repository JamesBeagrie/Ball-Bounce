#include "raylib.h"
#include "object.h"
#include "ball.h"
#include "mathlib.h"
#include <iostream>
#include <iomanip>

double Ball::calculateEnergy() {
    const double KE = 0.5 * m * v.squaredLength();
    const double GPE = -p.y * g.y * m;
    return GPE + KE;
}

void Ball::draw(const vec2& centre) {
    DrawCircleV({(float)p.x - (float)centre.x, (float)p.y - (float)centre.y}, (float)r.x, SKYBLUE);
}

vec2 Ball::collideWithWorld(Object* obj, CollisionPacket* collisionPackage, const vec2& pos, const vec2& vel, vec2* finalVelocity, int collisionRecursionDepth) {
    const double epsilon = 1e-7;
    const double vLen = vel.len();

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

    const double t = collisionPackage->nearestDistance;

    double moveT = t;
    if (moveT * vLen > epsilon) {
        moveT -= epsilon / vLen;
    } else {
        moveT = 0.0;
    }

    vec2 newBasePoint = collisionPackage->basePoint + vel * moveT;

    vec2 slideEdgeNormal = collisionPackage->collisionNormal;
    slideEdgeNormal.normalise();

    *finalVelocity = *finalVelocity - (1.0 + e) * slideEdgeNormal.dot(*finalVelocity) * slideEdgeNormal;

    vec2 newVelocityVector = vel - (1.0 + e) * slideEdgeNormal.dot(vel) * slideEdgeNormal;
    newVelocityVector = newVelocityVector * (1.0 - t);

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
    double e2 = calculateEnergy();
    //std::cout << std::fixed << std::setprecision(8) << "Energy: " << e2 << std::endl;
}