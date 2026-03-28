#ifndef MATHLIB_H
#define MATHLIB_H

#include <math.h>
#include "raylib.h"
#include <vector>
#include <memory>

bool getLowestRoot(float a, float b, float c, float maxR,float* root);

class vec2 {
    public:
    float x;
    float y;

    vec2(float x_, float y_);

    vec2();

    float squaredLength() const;

    void setLength(const float l);

    float len() const;

    void normalise();

    float dot(const vec2& other) const;

    vec2 normal();

    vec2 operator - (const vec2& other) const;

    vec2 operator - () const;

    vec2 operator + (const vec2& other) const;

    vec2 operator * (const vec2& other) const;

    vec2 operator / (const vec2& other) const;

    vec2 operator * (const float scalar) const;

    vec2 operator / (const float scalar) const;

    vec2& operator -= (const vec2& other);

    vec2& operator += (const vec2& other);

    vec2& operator *= (const vec2& other);
};

class Edge {
    public:
    vec2 v1;
    vec2 v2;
    vec2 d1;
    vec2 d2;

    Color color;

    vec2 n;
    float d;
    //float mu;

    Edge();
    Edge(vec2 v1_, vec2 v2_);
    Edge(vec2 v1_, vec2 v2_, Color color_);
    Edge(vec2 v1_, vec2 v2_, vec2 d1_, vec2 d2_);
    Edge(vec2 v1_, vec2 v2_, vec2 d1_, vec2 d2_, Color color_);
    void update();
    bool isFrontFacingTo(const vec2& v) const;
};

class DetectorEdge : public Edge {
    public:
    bool invis;
    DetectorEdge();
    DetectorEdge(vec2 v1_, vec2 v2_, vec2 d1_, vec2 d2_, Color color_, bool invis_);
    DetectorEdge(vec2 v1_, vec2 v2_, vec2 d1_, vec2 d2_, Color color_);
    DetectorEdge(vec2 v1_, vec2 v2_, Color color_);
};

class CollisionPacket {
    public:
    vec2 eRadius; // ellipsoid radius
    // Information about the move being requested: (in R2)
    vec2 R2Velocity;
    vec2 R2Position;
    // Information about the move being requested: (in eSpace)
    vec2 velocity;
    vec2 normalizedVelocity;
    vec2 basePoint;
    // Hit information
    bool foundCollision;
    float nearestDistance;
    vec2 intersectionPoint;
    vec2 collisionNormal;
    Edge* nearestEdge;
};

float signedDistanceTo(vec2 &p, Edge e);

bool checkPointInEdge(vec2 p, Edge e);

void checkEdge(CollisionPacket* colPackage, const Edge& e, Edge* edgePtr);

void checkMovingEdge(CollisionPacket* colPackage, const Edge& e, Edge* edgePtr);

#endif