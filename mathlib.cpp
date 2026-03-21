#include "mathlib.h"
#include <math.h>
#include <iostream>

bool getLowestRoot(double a, double b, double c, double maxR,double* root) {
    // Check if a solution exists
    double determinant = b*b - 4.0*a*c;
    // If determinant is negative it means no solutions.
    if (determinant < 0.0) return false;
    // calculate the two roots: (if determinant == 0 then
    // x1==x2 but let's disregard that slight optimization)
    double sqrtD = sqrt(determinant);
    double r1 = (-b - sqrtD) / (2*a);
    double r2 = (-b + sqrtD) / (2*a);
    // Sort so x1 <= x2
    if (r1 > r2) {
        double temp = r2;
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

edge::edge(vec2 v1_, vec2 v2_) : v1(v1_), v2(v2_) {
    n = (v2_ - v1_).normal();
    n.normalise();
    d = n.dot(v1_);
}

bool edge::isFrontFacingTo(const vec2& v) const {
    return n.dot(v) > 0.0;
}

double signedDistanceTo(vec2 &p, edge e) {
    return (e.n.dot(p) - e.d);
}

bool checkPointInEdge(vec2 p, edge e) {
    const double EPS = 1e-5;

    vec2 ab = e.v2 - e.v1;

    if (ab.dot(p - e.v1) < -EPS) return false;

    if (ab.dot(p - e.v2) > EPS) return false;

    return true;
}

void checkEdge(CollisionPacket* colPackage, const edge& e) {
    if (e.isFrontFacingTo(colPackage->velocity)) {
        double t0, t1;
        bool embeddedInEdge = false;

        double signedDistToEdge = signedDistanceTo(colPackage->basePoint, e);
        double normalDotVelocity = e.n.dot(colPackage->velocity);

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
                double temp = t1;
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
        double t = 1.0;

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
            double a,b,c;
            double newT;

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
            }
        }
    }
}