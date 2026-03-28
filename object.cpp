#include <vector>
#include "raylib.h"
#include "mathlib.h"
#include "windowlib.h"
#include "object.h"
#include "objectlib.h"

void Object::update() {
    if(!isDead) {
        for(auto& edge : e) {
            //Test
            edge->update();
        }
    }
}

void Object::collisionResponse(CollisionResponseData* data) {}

void Object::draw(Context* context) {
    if(!isDead) {
        for(auto& edge : e) {
            vec2 v1_ = formatWindowVec2(context, edge->v1 + centre);
            vec2 v2_ = formatWindowVec2(context, edge->v2 + centre);
            DrawLine(static_cast<int>(v1_.x), static_cast<int>(v1_.y), static_cast<int>(v2_.x), static_cast<int>(v2_.y), edge->color);
        }
    }
}

void Object::checkCollision(CollisionPacket* collisionPackage) {
    if(!isDead) {
        for(auto& edge : e) {
            Edge eSpaceEdge = Edge((edge->v1 + centre) / collisionPackage->eRadius,(edge->v2 + centre) /collisionPackage->eRadius);
            checkEdge(collisionPackage, eSpaceEdge, edge.get(), this);
        }
    }
}

void Circle::update() {
    if(!isDead) {
        for(auto& edge : e) {
            //Test
            edge->update();
        }

        rotationSpeed = e.front()->v1.len() / 10000.0f;
        rotateAround(this, centre, rotationSpeed);
    }
}