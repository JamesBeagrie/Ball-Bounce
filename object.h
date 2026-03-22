#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "raylib.h"
#include "mathlib.h"
#include "context.h"


class Object {
    public:
    std::vector<edge> e;
    vec2 centre;

    void draw(Context* global_context);

    void checkCollision(CollisionPacket* collisionPackage);
};

#endif