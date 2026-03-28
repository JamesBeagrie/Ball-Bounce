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
    bool isDead;
    float rotationSpeed;

    void draw(Context* context);

    void collisionResponse(CollisionResponseData* data);

    void checkCollision(CollisionPacket* collisionPackage);
    virtual void update();
};

class Circle : public Object {
    public:
    float rotationSpeed;
    void update() override;
};

#endif