#include "spaceship.h"
#include "graphics.h"

struct Spaceship_type {

	// Dimensions and position
	int cameraPosX;
	int cameraPosY;
	int w;
	int h;

	// Sprite
	SDL_Texture *texture_ship;
	SDL_Rect **clip;
	int *clipRowSize;
	int curClipRow;
	int curClipCol;
	int cyclesPerFrame;

	// Physics
	float delta_x;
	float delta_y;
	float drag;
	float acc;
	float weight; 

	// Status
	bool mobile;
	float hp;
	float armor;
	float damage;

};

Spaceship *createSpaceship() {
	return (Spaceship*) malloc(sizeof(Spaceship));
}

void spaceship_setCameraX(Spaceship *ptr_ship, int x)
{
	ptr_ship->cameraPosX = x;
}

int spaceship_getCameraX(Spaceship *ptr_ship)
{
	return ptr_ship->cameraPosX;
}

void spaceship_setCameraY(Spaceship *ptr_ship, int y)
{
	ptr_ship->cameraPosY = y;
}

int spaceship_getCameraY(Spaceship *ptr_ship)
{
	return ptr_ship->cameraPosY;
}

void spaceship_setWidth(Spaceship *ptr_ship, int w)
{
	ptr_ship->w = w;
}

int spaceship_getWidth(Spaceship *ptr_ship)
{
	return ptr_ship->w;
}

void spaceship_setHeight(Spaceship *ptr_ship, int h)
{
	ptr_ship->h = h;
}

int spaceship_getHeight(Spaceship *ptr_ship)
{
	return ptr_ship->h;
}

void spaceship_loadShipTexture(Spaceship *ptr_ship, char* path)
{
	SDL_Surface* local_surface = IMG_Load(path);
	ptr_ship->texture_ship = SDL_CreateTextureFromSurface(renderer, local_surface);
}

SDL_Texture *spaceship_getShipTexture(Spaceship *ptr_ship)
{
	return ptr_ship->texture_ship;
}

void spaceship_copySpriteSheet(Spaceship *ptr_ship, SDL_Rect** rects, int *rowFrameCount, int columns, int rows)
{
	for (int r = 0; r < columns; r++) {
		for (int c = 0; c < rows; c++) {
			ptr_ship->clip[c][r] = rects[c][r];
		}
	}
}

void spaceship_getRect(Spaceship *ptr_ship, int r, int c)
{
	return ptr_ship->clip[c][r];
}

void spaceship_setFrameRow(Spaceship *ptr_ship, int row)
{

}

void spaceship_frameTick(Spaceship *ptr_ship)
{

}