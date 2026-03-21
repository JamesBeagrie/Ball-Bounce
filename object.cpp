#include <vector>
#include "raylib.h"
#include "object.h"
#include "mathlib.h"

void Object::draw(const vec2& centre) {
    for(auto& edge : e) {
        DrawLineV({(float)edge.v1.x - (float)centre.x, (float)edge.v1.y - (float)centre.y}, {(float)edge.v2.x - (float)centre.x, (float)edge.v2.y - (float)centre.y}, SKYBLUE);
    }
}

void Object::checkCollision(CollisionPacket* collisionPackage) {
    for(auto& e_ : e) {
        edge eSpaceEdge = edge(e_.v1 / collisionPackage->eRadius,e_.v2 /collisionPackage->eRadius);
        checkEdge(collisionPackage, eSpaceEdge);
    }
}