#ifndef OBJECTLIB_H
#define OBJECTLIB_H

void createPolygon(int sides, vec2 c, float radius, Object *obj);
void createWaveBowl(vec2 c, float width, float height, int segments, Object* obj);
void createCircle(Object* obj, vec2 c, float ballRadius, float startingRadius, float gap, float holeAngle, int segments, int holeSegments);

#endif