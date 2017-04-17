/*	Author(s):	Tiago Redaelli
*	Modified:	17-04-2017
*	Version:	0.01
* 
*/

#include "sprite.h"
#include "graphics.h"

struct Sprite_type {
	int frameWidth;
	int frameHeight;
	int col;
	int row;
	int* numOfFrames;
	int textureWidth;
	int textureHeight;
	SDL_Texture* texture;
	SDL_Rect** clip;
};

Sprite *createSprite(char* filepath, int columns, int rows)
{
	Sprite *s = malloc(sizeof(Sprite));
	s->texture = IMG_LoadTexture(renderer, filepath);
	s->col = columns;
	s->row = rows;
	SDL_QueryTexture(s->texture, NULL, NULL, &(s->textureWidth), &(s->textureHeight));
	s->frameWidth = s->textureWidth / columns;
	s->frameHeight = s->textureHeight / rows;
	s->clip = malloc(columns * sizeof(SDL_Rect));
	s->numOfFrames = malloc(rows * sizeof(int));
	for (int c = 0; c < columns; c++) {
		s->clip[c] = malloc(rows * sizeof(SDL_Rect));
		for (int r = 0; r < rows; r++) {
			s->clip[c][r].x = s->frameWidth*c;
			s->clip[c][r].y = s->frameHeight*r;
			s->clip[c][r].w = s->frameWidth;
			s->clip[c][r].h = s->frameHeight;
		}
	}
	if (s->texture == NULL) {
		printf("ERROR: Failed to load sprite texture. createSprite()\n");
	}
	return s;
}

void destroySprite(Sprite *ptr_sprite)
{
	for (int c = 0; c < ptr_sprite->col; c++) {
		free(ptr_sprite->clip[c]);
	}
	free(ptr_sprite->clip);
	free(ptr_sprite->numOfFrames);
	free(ptr_sprite);
}

void sprite_setRowFrameCount(Sprite *ptr_sprite, int row, int value)
{
	ptr_sprite->numOfFrames[row] = value;
}

int sprite_getRowFrameCount(Sprite *ptr_sprite, int row)
{
	return ptr_sprite->numOfFrames[row];
}

SDL_Rect sprite_getClipRect(Sprite *ptr_sprite, int col, int row)
{
	return ptr_sprite->clip[col][row];
}

int sprite_getFrameWidth(Sprite *ptr_sprite)
{
	return ptr_sprite->frameWidth;
}

int sprite_getFrameHeight(Sprite *ptr_sprite)
{
	return ptr_sprite->frameHeight;
}

int sprite_getTextureWidth(Sprite *ptr_sprite)
{
	return ptr_sprite->textureWidth;
}

int sprite_getTextureHeight(Sprite *ptr_sprite)
{
	return ptr_sprite->textureHeight;
}

SDL_Texture *sprite_getTexture(Sprite *ptr_sprite)
{
	return ptr_sprite->texture;
}