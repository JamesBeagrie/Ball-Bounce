#ifndef MATHLIB_H
#define MATHLIB_H

#include <math.h>

bool getLowestRoot(double a, double b, double c, double maxR,double* root);

class vec2 {
    public:
    double x;
    double y;

    vec2(double x_, double y_) : x(x_), y(y_) {}

    vec2() : x(0.0), y(0.0) {}

    double squaredLength() const {
        return x * x + y * y;
    }

    void setLength(const double l) {
        if (x == 0.0 && y == 0.0) { x = 0.0; y = 0.0; return; }
        double len = sqrt(x * x + y * y);
        x = l * x/len;
        y = l * y/len;
        return;
    }

    double len() const {
        return sqrt(x * x + y * y);
    }

    void normalise() {
        if (x == 0.0 && y == 0.0) {
            x = 0.0; 
            y = 0.0;
            return;
        }
        double len = sqrt(x * x + y * y);
        x = x/len; 
        y = y/len;
    }

    double dot(const vec2& other) const {
        return x * other.x + y * other.y;
    }

    vec2 normal() {
        return vec2(-y, x);
    }

    vec2 operator - (const vec2& other) const {
        return vec2(x - other.x, y - other.y);
    }

    vec2 operator - () const {
        return vec2(-x, -y);
    }

    vec2 operator + (const vec2& other) const {
        return vec2(x + other.x, y + other.y);
    }

    vec2 operator * (const vec2& other) const {
        return vec2(x * other.x, y * other.y);
    }

    vec2 operator / (const vec2& other) const {
        return vec2(x / other.x, y / other.y);
    }

    vec2 operator * (const double scalar) const {
        return vec2(x * scalar, y * scalar);
    }

    vec2& operator -= (const vec2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    vec2& operator += (const vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    vec2& operator *= (const vec2& other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }
};

inline vec2 operator*(double scalar, const vec2& v) {
    return vec2(v.x * scalar, v.y * scalar);
}

class edge {
    public:
    vec2 v1;
    vec2 v2;
    vec2 n;
    double d;
    //double mu;

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
    double nearestDistance;
    vec2 intersectionPoint;
    vec2 collisionNormal;
};

double signedDistanceTo(vec2 &p, edge e);

bool checkPointInEdge(vec2 p, edge e);

void checkEdge(CollisionPacket* colPackage, const edge& e);

#endif