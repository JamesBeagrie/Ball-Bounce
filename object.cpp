#include <vector>
#include "raylib.h"
#include "mathlib.h"
#include "windowlib.h"
#include "object.h"

void Object::update() {
    for(auto& edge : e) {
        //Test
        edge.update();
    }
}

void Object::draw(Context* context) {
    for(auto& edge : e) {
        vec2 v1_ = formatWindowVec2(context, edge.v1 + centre);
        vec2 v2_ = formatWindowVec2(context, edge.v2 + centre);
        DrawLine(static_cast<int>(v1_.x), static_cast<int>(v1_.y), static_cast<int>(v2_.x), static_cast<int>(v2_.y), SKYBLUE);
    }
}

void Object::checkCollision(CollisionPacket* collisionPackage) {
    for(auto& e_ : e) {
        Edge eSpaceEdge = Edge((e_.v1 + centre) / collisionPackage->eRadius,(e_.v2 + centre) /collisionPackage->eRadius);
        checkEdge(collisionPackage, eSpaceEdge, &e_);
    }
}