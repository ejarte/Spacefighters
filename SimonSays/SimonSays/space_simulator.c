#include "space_simulator.h"
#include "states.h"
#include "graphics_lib.h"
#include "events.h"

#define SPACEHIP_PATH	"images/spaceship.png"

SDL_Rect spaceship_rect;
SDL_Texture* spaceship_texture;

void setupSpaceSimulator()
{
	SDL_Surface *screen;
	screen = 
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	loadTexture(SPACEHIP_PATH, &spaceship_texture);
	// Configure rect
	spaceship_rect.x = screenW / 2;
	spaceship_rect.y = screenH / 2;
	spaceship_rect.w = 99;
	spaceship_rect.h = 154;
	//SDL_QueryTexture(spaceship_texture, NULL, NULL, &spaceship_rect.w, &spaceship_rect.h);
	// Setup next sequence
	//draw image
	//SDL_FillRect(window, NULL, 0);
	SDL_BlitSurface(SPACEHIP_PATH, &spaceship_rect, window, NULL);

	//SDL_Flip(window);

	setNextState(STATE_RUN_SPACE_SIM);
}

void runSpaceSimulator()
{
	//SDL_RendererClear(renderer);
	SDL_RenderCopy(renderer, spaceship_texture, NULL, &spaceship_rect);
	SDL_RenderPresent(renderer);
}