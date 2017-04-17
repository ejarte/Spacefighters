#pragma once

#include "libraries.h"

typedef struct Sprite_type Sprite;

Sprite *createSprite(char* filepath, int columns, int rows);
void destroySprite(Sprite *ptr_sprite);
void sprite_setRowFrameCount(Sprite *ptr_sprite, int row, int value);
int sprite_getRowFrameCount(Sprite *ptr_sprite, int row);
SDL_Rect sprite_getClipRect(Sprite *ptr_sprite, int col, int row);
int sprite_getFrameWidth(Sprite *ptr_sprite);
int sprite_getFrameHeight(Sprite *ptr_sprite);
int sprite_getTextureWidth(Sprite *ptr_sprite);
int sprite_getTextureHeight(Sprite *ptr_sprite);
SDL_Texture *sprite_getTexture(Sprite *ptr_sprite);