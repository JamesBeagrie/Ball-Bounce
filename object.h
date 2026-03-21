#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "raylib.h"
#include "mathlib.h"


class Object {
    public:
    std::vector<edge> e;

    void draw(const vec2& centre);

    void checkCollision(CollisionPacket* collisionPackage);
};

#endif