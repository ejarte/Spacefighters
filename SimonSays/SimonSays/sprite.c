/*	Author(s):	Tiago Redaelli
*	Modified:	18-04-2017
*	Version:	0.02
* 
*	Documentation of API is in the sprite.h file.
*/

#include "sprite.h"

struct Sprite_type {
	int frameWidth;
	int frameHeight;
	int col;
	int row;
	int* numOfFrames;
	int textureWidth;
	int textureHeight;			
	SDL_Texture* texture;			// Texture 
	SDL_Rect** clip;				// Frame
};

Sprite *createSprite(SDL_Renderer* renderer, char* filepath, int columns, int rows, SDL_Color colorKey)
{
	Sprite *s = malloc(sizeof(Sprite));
	SDL_Surface *s_loadedSurface = IMG_Load(filepath);
	if (s_loadedSurface == NULL) {
		printf("ERROR: Unable to load texture %s. SDL_Image Error: %s\n", filepath, IMG_GetError());
	}
	else {
		SDL_SetColorKey(s_loadedSurface, SDL_TRUE, SDL_MapRGB(s_loadedSurface->format, colorKey.r, colorKey.g, colorKey.b));
		s->texture = SDL_CreateTextureFromSurface(renderer, s_loadedSurface);
		if (s->texture == NULL) {
			printf("SDL_Error: %s\n", SDL_GetError());
		}

		SDL_FreeSurface(s_loadedSurface);
	}
	s->col = columns;
	s->row = rows;
	SDL_QueryTexture(s->texture, NULL, NULL, &(s->textureWidth), &(s->textureHeight));
	s->frameWidth = s->textureWidth / columns;
	s->frameHeight = s->textureHeight / rows;
	s->clip = malloc(columns * sizeof(SDL_Rect));
	s->numOfFrames = malloc(rows * sizeof(int));

	for (int r = 0; r < rows; r++) {		// Default number of frames initiated per row
		s->numOfFrames[r] = columns;
	}

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
	if (ptr_sprite->texture != NULL) {
		SDL_DestroyTexture(ptr_sprite->texture);
	}
	for (int c = 0; c < ptr_sprite->col; c++) {
		free(ptr_sprite->clip[c]);
	}
	free(ptr_sprite->clip);
	free(ptr_sprite->numOfFrames);
	free(ptr_sprite);
}

void sprite_setRowFrameCount(Sprite *ptr_sprite, int row, int value)
{
	if (row >= ptr_sprite->row || row < 0) {
		printf("ERROR: IndexOutOfBounds (row): %d.\n", row);
		return;
	}
	if (value >= ptr_sprite->col || value < 0) {
		printf("ERROR: IndexOutOfBounds (value): %d.\n", value);
		return;
	}
	ptr_sprite->numOfFrames[row] = value;
}

int sprite_getRowFrameCount(Sprite *ptr_sprite, int row)
{
	if (row >= ptr_sprite->row || row < 0) {
		printf("ERROR: IndexOutOfBounds (row): %d.\n", row);
		return 0;
	}
	return ptr_sprite->numOfFrames[row];
}

SDL_Rect sprite_getClipRect(Sprite *ptr_sprite, int col, int row)
{
	if (row >= ptr_sprite->row || row < 0) {
		printf("ERROR: sprite_getClipRect, IndexOutOfBounds (row): %d.\n", row);
	}
	if (col >= ptr_sprite->col || col < 0) {
		printf("ERROR: sprite_getClipRect, IndexOutOfBounds (col): %d.\n", col);
	}
	return ptr_sprite->clip[col][row];
}

void sprite_RenderCopy(SDL_Renderer* renderer, Sprite *ptr_sprite, int col, int row, SDL_Rect dsrect)
{
	// Renders to screen
	SDL_Rect srect = sprite_getClipRect(ptr_sprite, col, row);
	SDL_RenderCopy(renderer, ptr_sprite->texture, &srect, &dsrect);
}


SDL_Texture *sprite_getTexture(Sprite *ptr_sprite)
{
	if (ptr_sprite->texture == NULL) {
		printf("ERROR: sprite_getTexture, No media loaded.\n");
	}
	return ptr_sprite->texture;
}

int sprite_getRows(Sprite  *ptr_sprite)
{
	return ptr_sprite->row;
}

int sprite_getColumns(Sprite  *ptr_sprite)
{
	return ptr_sprite->col;
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
