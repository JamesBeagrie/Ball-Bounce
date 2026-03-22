#include <vector>
#include "raylib.h"
#include "mathlib.h"
#include "windowlib.h"
#include "object.h"

void Object::draw(Context* global_context) {
    for(auto& edge : e) {
        vec2 v1_ = formatWindowVec2(global_context, edge.v1 + centre);
        vec2 v2_ = formatWindowVec2(global_context, edge.v2 + centre);
        DrawLine(static_cast<int>(v1_.x), static_cast<int>(v1_.y), static_cast<int>(v2_.x), static_cast<int>(v2_.y), SKYBLUE);
    }
}

void Object::checkCollision(CollisionPacket* collisionPackage) {
    for(auto& e_ : e) {
        edge eSpaceEdge = edge(e_.v1 / collisionPackage->eRadius,e_.v2 /collisionPackage->eRadius);
        checkEdge(collisionPackage, eSpaceEdge, &e_);
    }
}