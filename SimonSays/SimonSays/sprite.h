#pragma once

#include "libraries.h"

typedef struct Sprite_type Sprite;

/**
* Creates a new Sprite Sheet
*
* Returns a pointer to a new sprite sheet almost fully configured. 
*/
Sprite *createSprite(char* filepath, int columns, int rows);					// <--- Creating

/*
* Destroys a Sprite Sheet
* Frees the memory from the Sprite Sheet. 
*/
void destroySprite(Sprite *ptr_sprite);											// <--- Destroying

/* 
* A count of the number of frames on a row. Used in circumstances 
* where all rows don't contain an equal amount of frames.
* Note: It's by default set to the maximum unless changed.
*/
void sprite_setRowFrameCount(Sprite *ptr_sprite, int row, int value);			// <--- Used for cases when all rows don't contain an equal amount of frames

/*
* Returns the number of frames allocated on a row.
*/
int sprite_getRowFrameCount(Sprite *ptr_sprite, int row);						// <--- Can be used for configuring animations

/*
* Renders a sprite frame [col][row] onto a destination rect.
*/
void sprite_RenderCopy(SDL_Renderer* renderer, Sprite *ptr_sprite, int col, int row, SDL_Rect dsrect);  // <--- Renders sprite frame [col][row] onto destination rect


/* 
		You don't really need to use anything below this...
*/


/*
* Returns a clip (rect) of a frame on that coordinate [columns][row]
* Used to render the texture.
*/
SDL_Rect sprite_getClipRect(Sprite *ptr_sprite, int col, int row);				// 

/*
* Returns the stored texture.
*/
SDL_Texture *sprite_getTexture(Sprite *ptr_sprite);							


int sprite_getRows(Sprite  *ptr_sprite);
int sprite_getColumns(Sprite  *ptr_sprite);
int sprite_getFrameWidth(Sprite *ptr_sprite);									
int sprite_getFrameHeight(Sprite *ptr_sprite);
int sprite_getTextureWidth(Sprite *ptr_sprite);
int sprite_getTextureHeight(Sprite *ptr_sprite);
