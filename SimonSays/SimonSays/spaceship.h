#pragma once

#include "libraries.h"

typedef struct Spaceship_type Spaceship;

Spaceship *createSpaceship();
void spaceship_setCameraX(Spaceship *ptr_ship, int x);
int spaceship_getCameraX(Spaceship *ptr_ship);
void spaceship_setCameraY(Spaceship *ptr_ship, int y);
int spaceship_getCameraY(Spaceship *ptr_ship);
void spaceship_setWidth(Spaceship *ptr_ship, int w);
int spaceship_getWidth(Spaceship *ptr_ship);
void spaceship_setHeight(Spaceship *ptr_ship, int h);
int spaceship_getHeight(Spaceship *ptr_ship);
void spaceship_loadShipTexture(Spaceship *ptr_ship, char* path);
SDL_Texture *spaceship_getShipTexture(Spaceship *ptr_ship);
void spaceship_copySpriteSheet(Spaceship *ptr_ship, SDL_Rect** rects, int *rowFrameCount, int columns, int rows);
void spaceship_getRect(Spaceship *ptr_ship, int r, int c);