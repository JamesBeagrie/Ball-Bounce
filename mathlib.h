#ifndef MATHLIB_H
#define MATHLIB_H

#include <math.h>

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

class edge {
    public:
    vec2 v1;
    vec2 v2;
    vec2 n;
    float d;
    //float mu;

    edge(vec2 v1_, vec2 v2_);
    bool isFrontFacingTo(const vec2& v) const;
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
    edge* nearestEdge;
};

float signedDistanceTo(vec2 &p, edge e);

bool checkPointInEdge(vec2 p, edge e);

void checkEdge(CollisionPacket* colPackage, const edge& e, edge* edgePtr);

#endif