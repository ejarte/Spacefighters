#include "game.h"
#include "spaceship.h"
#include "graphics.h"
#include "sprite.h"

// Background
SDL_Rect background_rect;
SDL_Texture* background_texture;

// Sprites
Spaceship *spaceship[10];
SDL_Texture* spaceship_texture;
SDL_Rect spaceship_rect;

Sprite *spaceship_sprite;
SDL_Rect spaceship_rect;		// Spaceship rect

SDL_Rect tempRect;				// Clip rect

void initGame()
{
	// Background
	background_texture = IMG_LoadTexture(renderer, "images/bakgrund_himmel.gif");
	background_rect.x = background_rect.y = 0;
	SDL_GetRendererOutputSize(renderer, &background_rect.w, &background_rect.h);

	// Sprites

	/*
	spaceship_sprite = createSprite("images/explosion1.png", 64, 64, 5, 5);
	sprite_setRowFrameCount(spaceship_sprite, 0, 5);
	sprite_setRowFrameCount(spaceship_sprite, 1, 5);
	sprite_setRowFrameCount(spaceship_sprite, 2, 5);
	sprite_setRowFrameCount(spaceship_sprite, 3, 5);
	sprite_setRowFrameCount(spaceship_sprite, 4, 5);
	*/

	spaceship_sprite = createSprite("images/wind_eff_001.png", 5, 6);
	sprite_setRowFrameCount(spaceship_sprite, 0, 1);
	sprite_setRowFrameCount(spaceship_sprite, 1, 1);
	sprite_setRowFrameCount(spaceship_sprite, 2, 1);
	sprite_setRowFrameCount(spaceship_sprite, 3, 1);
	sprite_setRowFrameCount(spaceship_sprite, 4, 1);
	sprite_setRowFrameCount(spaceship_sprite, 5, 1);


	spaceship_rect.x = background_rect.w/2 - 99/2;
	spaceship_rect.y = background_rect.h / 2 - 154/2;
	spaceship_rect.w = 99;
	spaceship_rect.h = 99;
}

bool hasRunOnce = false;

void gameLoop()
{
	if (!hasRunOnce) {
		hasRunOnce = true;
		initGame();
	}
	gameRender();
}

int frameTime_t = 0;
int frame_row = 0;
int frame_col = 0;

void gameRender()
{
	// Adjuct background to screen dimensions
	SDL_GetRendererOutputSize(renderer, &background_rect.w, &background_rect.h);
	
	// Update screen

	SDL_RenderClear(renderer); 
	SDL_RenderCopy(renderer, background_texture, NULL, &background_rect);
	
	frameTime_t++;
	if (frameTime_t == 10)
	{
		frame_col++;
		if (frame_col == 5) {
			frame_col = 0;
			frame_row++;
			if (frame_row == 6) {
				frame_row = 0;
			}
		}
		frameTime_t = 0;
	}

	printf("%d\n", frame_col);
	SDL_Rect rect = sprite_getClipRect(spaceship_sprite, frame_col, frame_row);


	SDL_RenderCopy(renderer, sprite_getTexture(spaceship_sprite), &rect, &spaceship_rect);
	SDL_RenderPresent(renderer);
}