#pragma once

#include "libraries.h"
#include "definition.h"

void sprite_setup(struct Sprite *s, SDL_Renderer* renderer, char* filepath, int columns, int rows, SDL_Color colorKey);
SDL_Rect sprite_getClipRect(struct Sprite *s, int col, int row);
void sprite_RenderCopy(struct Sprite *s, SDL_Renderer* renderer, int col, int row, SDL_Rect dsrect);
SDL_Texture* sprite_getTexture(struct Sprite *s);


//=====================//
// ~~ GAMMALT NEDAN ~~ // 
//=====================//

/*
typedef struct Sprite_type Sprite;

Sprite *createSprite(SDL_Renderer* renderer, char* filepath, int columns, int rows, SDL_Color colorKey);				// <--- Creating

void destroySprite(Sprite *ptr_sprite);											// <--- Destroying

/
void sprite_setRowFrameCount(Sprite *ptr_sprite, int row, int value);			// <--- Used for cases when all rows don't contain an equal amount of frames

int sprite_getRowFrameCount(Sprite *ptr_sprite, int row);						// <--- Can be used for configuring animations


void sprite_RenderCopy(SDL_Renderer* renderer, Sprite *ptr_sprite, int col, int row, SDL_Rect dsrect);  // <--- Renders sprite frame [col][row] onto destination rect


SDL_Rect sprite_getClipRect(Sprite *ptr_sprite, int col, int row);				// 

SDL_Texture *sprite_getTexture(Sprite *ptr_sprite);							

int sprite_getRows(Sprite  *ptr_sprite);
int sprite_getColumns(Sprite  *ptr_sprite);
int sprite_getFrameWidth(Sprite *ptr_sprite);									
int sprite_getFrameHeight(Sprite *ptr_sprite);
int sprite_getTextureWidth(Sprite *ptr_sprite);
int sprite_getTextureHeight(Sprite *ptr_sprite);
void sprite_print(Sprite *ptr_sprite);

*/