#pragma once

#include "libraries.h"
#include "definition.h"

bool collision_circleIntersection(struct Collision c1, int x1, int y1, struct Collision c2, int x2, int y2);
bool collision_boxIntersection(struct Collision c1, int x1, int y1, struct Collision c2, int x2, int y2);
void collision_boxRender(SDL_Renderer* renderer, struct Collision* c, int x, int y);