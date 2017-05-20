#pragma once

#include "graphics.h"


void initWindow()
{
	targetW = 1280;
	targetH = 720;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);	// Audio!!!
	SDL_Surface* screen;

	SDL_Rect displayBounds;
	if (SDL_GetDisplayBounds(0, &displayBounds) != 0) {
		SDL_Log("SDL_GetDisplayBounds failed: %s", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("SimonSays", 100, 100, targetW, targetH, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);	// SDL_WINDOW_FULLSCREEN_DESKTOP);

	if (window == NULL) {
		printf("Error, Window can't be desplayed\n");
		exit(-1);
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// Vad gör detta här? D
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		printf("Error, Sound cannot be loaded");

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_GetRendererOutputSize(renderer, &screenW, &screenH);

}

void resize()
{
	SDL_GetRendererOutputSize(renderer, &screenW, &screenH);
}