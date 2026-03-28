#ifndef OBJECTLIB_H
#define OBJECTLIB_H

void rotateAround(Object* obj, vec2 c, float rotation);
void createPolygon(Object *obj, int sides, vec2 c, float radius);
void createWaveBowl(Object* obj, vec2 c, float width, float height, int segments);
void createCircle(Object* obj, vec2 c, float ballRadius, float r, int segments, int holeSegments);
void createCircleHell(std::vector<Object>* environment, vec2 c, float ballRadius, float startingRadius, float gap, int segments, int holeSegments, int circleCount);

#endif