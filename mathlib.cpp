#include "mathlib.h"
#include "raylib.h"
#include <math.h>
#include <iostream>
#include <vector>
#include <memory>

CollisionResponseData::CollisionResponseData() : deleteOwnObj(false) {}

bool getLowestRoot(float a, float b, float c, float maxR,float* root) {
    // Check if a solution exists
    float determinant = b*b - 4.0*a*c;
    // If determinant is negative it means no solutions.
    if (determinant < 0.0) return false;
    // calculate the two roots: (if determinant == 0 then
    // x1==x2 but let's disregard that slight optimization)
    float sqrtD = sqrt(determinant);
    float r1 = (-b - sqrtD) / (2*a);
    float r2 = (-b + sqrtD) / (2*a);
    // Sort so x1 <= x2
    if (r1 > r2) {
        float temp = r2;
        r2 = r1;
        r1 = temp;
    }
    // Get lowest root:
    if (r1 > 0 && r1 < maxR) {
        *root = r1;
        return true;
    }
    // It is possible that we want x2 - this can happen
    // if x1 < 0
    if (r2 > 0 && r2 < maxR) {
        *root = r2;
        return true;
    }
    // No (valid) solutions
    return false;
}

Edge::Edge() : v1({0.0f,0.0f}), v2({0.0f,0.0f}), d1({0.0f,0.0f}), d2({0.0f,0.0f}), color(SKYBLUE) {
    n = (v2 - v1).normal();
    n.normalise();
    d = n.dot(v1);
}

Edge::Edge(vec2 v1_, vec2 v2_) : v1(v1_), v2(v2_), d1({0.0f,0.0f}), d2({0.0f,0.0f}), color(SKYBLUE) {
    n = (v2_ - v1_).normal();
    n.normalise();
    d = n.dot(v1_);
}

Edge::Edge(vec2 v1_, vec2 v2_, Color color_) : v1(v1_), v2(v2_), d1({0.0f,0.0f}), d2({0.0f,0.0f}), color(color_) {
    n = (v2_ - v1_).normal();
    n.normalise();
    d = n.dot(v1_);
}

Edge::Edge(vec2 v1_, vec2 v2_, vec2 d1_, vec2 d2_) : v1(v1_), v2(v2_), d1(d1_), d2(d2_), color(SKYBLUE) {
    n = (v2_ - v1_).normal();
    n.normalise();
    d = n.dot(v1_);
}

Edge::Edge(vec2 v1_, vec2 v2_, vec2 d1_, vec2 d2_, Color color_) : v1(v1_), v2(v2_), d1(d1_), d2(d2_), color(color_) {
    n = (v2_ - v1_).normal();
    n.normalise();
    d = n.dot(v1_);
}

void Edge::collisionResponse(CollisionResponseData* data) {}

DetectorEdge::DetectorEdge() : Edge(), invis(false), deleteSelf(false) {}

DetectorEdge::DetectorEdge(vec2 v1_, vec2 v2_, vec2 d1_, vec2 d2_, Color color_, bool invis_, bool deleteSelf_) : Edge(v1_, v2_, d1_, d2_, color_), invis(invis_), deleteSelf(deleteSelf_) {}

DetectorEdge::DetectorEdge(vec2 v1_, vec2 v2_, vec2 d1_, vec2 d2_, Color color_) : Edge(v1_, v2_, d1_, d2_, color_), invis(false), deleteSelf(false) {}

DetectorEdge::DetectorEdge(vec2 v1_, vec2 v2_, Color color_) : Edge(v1_, v2_, color_), invis(false), deleteSelf(false) {}

void DetectorEdge::collisionResponse(CollisionResponseData* collisionResponseData) {
    if (deleteSelf) {
        collisionResponseData->deleteOwnObj = true;
    }
}

bool Edge::isFrontFacingTo(const vec2& v) const {
    return n.dot(v) > 0.0;
}

void Edge::update() {
    v1+=d1;
    v2+=d2;

    n = (v2 - v1).normal();
    n.normalise();
    d = n.dot(v1);
}

float signedDistanceTo(vec2 &p, Edge e) {
    return (e.n.dot(p) - e.d);
}

bool checkPointInEdge(vec2 p, Edge e) {
    const float EPS = 1e-5;

    vec2 ab = e.v2 - e.v1;

    if (ab.dot(p - e.v1) < -EPS) return false;

    if (ab.dot(p - e.v2) > EPS) return false;

    return true;
}

void checkEdge(CollisionPacket* colPackage, const Edge& e, Edge* edgePtr, Object* objPtr) {
    if (e.isFrontFacingTo(colPackage->velocity)) {
        float t0, t1;
        bool embeddedInEdge = false;

        float signedDistToEdge = signedDistanceTo(colPackage->basePoint, e);
        float normalDotVelocity = e.n.dot(colPackage->velocity);

        if (fabs(normalDotVelocity) < 1e-7) {
            if (fabs(signedDistToEdge) >= 1.0) {
                return;
            } else {
                embeddedInEdge = true;
                t0 = 0.0;
                t1 = 1.0;
            }
        } else {
            t0=(-1.0-signedDistToEdge)/normalDotVelocity;
            t1=( 1.0-signedDistToEdge)/normalDotVelocity;

            if (t0 > t1) {
                float temp = t1;
                t1 = t0;
                t0 = temp;
            }

            if (t0 > 1.0 || t1 < 0.0) {
                return;
            }

            if (t0 < 0.0) t0 = 0.0;
            if (t1 < 0.0) t1 = 0.0;
            if (t0 > 1.0) t0 = 1.0;
            if (t1 > 1.0) t1 = 1.0;
        }

        vec2 collisionPoint;
        vec2 collisionNormal;
        bool foundCollision = false;
        float t = 1.0;

        if (!embeddedInEdge) {
            vec2 edgeIntersectionPoint = (colPackage->basePoint - e.n) + colPackage->velocity * t0;

            if (checkPointInEdge(edgeIntersectionPoint, e)) {
                foundCollision = true;
                t = t0;
                collisionPoint = edgeIntersectionPoint;
                collisionNormal = e.n;
            }
        }

        if (foundCollision == false) {
            vec2 base = colPackage->basePoint;
            vec2 velocity = colPackage ->velocity;
            float a,b,c;
            float newT;

            a = velocity.squaredLength();
            b = 2.0*(velocity.dot(base-e.v1));
            c = (e.v1-base).squaredLength() - 1.0;

            if (getLowestRoot(a,b,c, t, &newT)) {
                t = newT;
                foundCollision = true;
                collisionPoint = e.v1;
                collisionNormal = (base + velocity * t - e.v1);
                collisionNormal.normalise();
            }

            b = 2.0*(velocity.dot(base-e.v2));
            c = (e.v2-base).squaredLength() - 1.0;

            if (getLowestRoot(a,b,c, t, &newT)) {
                t = newT;
                foundCollision = true;
                collisionPoint = e.v2;
                collisionNormal = (base + velocity * t - e.v2);
                collisionNormal.normalise();
            }
        }

        if (foundCollision == true) {
            if (colPackage->foundCollision == false || t < colPackage->nearestDistance) {
                colPackage->nearestDistance = t;
                colPackage->intersectionPoint = collisionPoint;
                colPackage->foundCollision = true;
                colPackage->collisionNormal = collisionNormal;
                colPackage->nearestEdge = edgePtr;
                colPackage->nearestObj = objPtr;
            }
        }
    }
}

vec2::vec2(float x_, float y_) : x(x_), y(y_) {}

vec2::vec2() : x(0.0), y(0.0) {}

float vec2::squaredLength() const {
    return x * x + y * y;
}

void vec2::setLength(const float l) {
    if (x == 0.0 && y == 0.0) { x = 0.0; y = 0.0; return; }
    float len = sqrt(x * x + y * y);
    x = l * x/len;
    y = l * y/len;
    return;
}

float vec2::len() const {
    return sqrt(x * x + y * y);
}

void vec2::normalise() {
    if (x == 0.0 && y == 0.0) {
        x = 0.0; 
        y = 0.0;
        return;
    }
    float len = sqrt(x * x + y * y);
    x = x/len; 
    y = y/len;
}

float vec2::dot(const vec2& other) const {
    return x * other.x + y * other.y;
}

vec2 vec2::normal() {
    return vec2(-y, x);
}

vec2 vec2::operator - (const vec2& other) const {
    return vec2(x - other.x, y - other.y);
}

vec2 vec2::operator - () const {
    return vec2(-x, -y);
}

vec2 vec2::operator + (const vec2& other) const {
    return vec2(x + other.x, y + other.y);
}

vec2 vec2::operator * (const vec2& other) const {
    return vec2(x * other.x, y * other.y);
}

vec2 vec2::operator / (const vec2& other) const {
    return vec2(x / other.x, y / other.y);
}

vec2 vec2::operator * (const float scalar) const {
    return vec2(x * scalar, y * scalar);
}

vec2 vec2::operator / (const float scalar) const {
    return vec2(x / scalar, y / scalar);
}

vec2& vec2::operator -= (const vec2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

vec2& vec2::operator += (const vec2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

vec2& vec2::operator *= (const vec2& other) {
    x *= other.x;
    y *= other.y;
    return *this;
}