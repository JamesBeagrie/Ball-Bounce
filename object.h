#ifndef OBJECT_H
#define OBJECT_H


#include <vector>
#include <memory>
#include "raylib.h"
#include "mathlib.h"

class Context;

class Object {
    public:
    std::vector<std::unique_ptr<Edge>> e;
    vec2 centre;

    void draw(Context* context);

    void checkCollision(CollisionPacket* collisionPackage);
    void update();
};

#endif