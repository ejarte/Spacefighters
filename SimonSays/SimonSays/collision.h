#pragma once

#include "libraries.h"

#define COLLISION_TYPE_BOX		1
#define COLLISION_TYPE_CIRCLE	2

typedef struct Collision_Type Collision;		

Collision* createCollisionBox(SDL_Point* p, int w, int h, int x_offset, int y_offset);
Collision* createCollisionCircle(SDL_Point* p, int d, int x_offset, int y_offset);
void destroyCollision(Collision* c);
bool collision_circleIntersection(Collision* c1, Collision* c2);
bool collision_boxIntersection(Collision* c1, Collision* c2);
void collision_boxRender(SDL_Renderer* renderer, Collision* c);
int collision_getType(Collision* c);
void collision_print(Collision* c);