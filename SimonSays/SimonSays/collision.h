#pragma once

#include "libraries.h"


typedef struct Collision_Type_Box Collision_Box;

Collision_Box* createCollisionBox(SDL_Point* p, int w, int h, int x_offset, int y_offset);
void destroyCollisionBox(Collision_Box* c);
bool collision_boxIntersection(Collision_Box* c1, Collision_Box* c2);
void collision_boxPrint(Collision_Box* c);
void collision_boxRender(SDL_Renderer* renderer, Collision_Box* c);