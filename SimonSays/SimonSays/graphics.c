#pragma once

#include "graphics.h"

void initWindow()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	SDL_Surface* screen, *image;

	//Skapar ett fönster i fullskärmläge
	window = NULL;
	window = SDL_CreateWindow("SimonSays", 100, 100, 600, 400, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	//window_col

	if (window == NULL) {
		printf("Error, Window can't be desplayed\n");
		exit(-1);
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		printf("Error, Sound cannot be loaded");

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

int getWindowHeight()
{
	return screenH;
}

int getWindowWidth()
{
	return screenW;
}

// Loads a texture with a file

void loadTexture(char *filepath, SDL_Texture **ptr_texture)
{
	*ptr_texture = IMG_LoadTexture(renderer, filepath);
	if ((*ptr_texture) == NULL) 
		printf("ERROR: Failed to load texture: %s", filepath);
}

void renderCopy(SDL_Texture* texture, const SDL_Rect* source, SDL_Rect* dest)
{
	SDL_RenderCopy(renderer, texture, source, dest);
}

void loadFont(const char *filepath, int fontsize, TTF_Font** font)
{
	(*font) = TTF_OpenFont(filepath, fontsize);
	if ((*font) == NULL)
		printf("TTF_ERROR: %s", TTF_GetError());
}

void createTextureText(char *text, TTF_Font *font, SDL_Color textcolor, SDL_Texture **ptr_texture)
{
	SDL_Surface *surface = TTF_RenderText_Solid(font, text, textcolor);
	*ptr_texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

void createTextAndRect(int x, int y, char* text, SDL_Color textcolor, TTF_Font* font, SDL_Texture **ptr_texture, SDL_Rect *ptr_rect)
{
	SDL_Surface *surface = TTF_RenderText_Solid(font, text, textcolor);
	*ptr_texture = SDL_CreateTextureFromSurface(renderer, surface);
	ptr_rect->x = x;
	ptr_rect->y = y;
	ptr_rect->w = surface->w;
	ptr_rect->h = surface->h;
	SDL_FreeSurface(surface);
}
