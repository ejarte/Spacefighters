#include "main.h"

void initWindow()
{
	quit = false;

	SDL_Init(SDL_INIT_VIDEO);

	//Skapar ett fönster i fullskärmläge
	window = NULL;
	window = SDL_CreateWindow("SimonSays", 100, 100, 600, 400, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (window == NULL)
	{
		printf("Error, Window can't be desplayed");
		return(0); //avslutar programmet
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void initImages()
{
	//laddar in bilderna
	SDL_GetRendererOutputSize(renderer, &screenW, &screenH);

	if (boxW < boxH)
	{
		boxW = screenW/4;
		boxH = boxW;
	} else
	{
		boxH = screenH/4;
		boxW = boxH;
	}

	yellow_box = NULL;
	yellow_box = IMG_LoadTexture(renderer, "images/yellowsquare.bmp"); //laddar den gula bilden i yellow_box

	yellow_rect.x = screenW / 2 - (boxW);
	yellow_rect.y = 10 + (boxH * 0.2);
	yellow_rect.w = boxW;  //Bredd
	yellow_rect.h = boxH;  //Höjd

	green_box = NULL;
	green_box = IMG_LoadTexture(renderer, "images/greensquare.bmp");

	green_rect.x = 10 + (screenW / 2);
	green_rect.y = 10 + (boxH * 0.2);
	green_rect.w = boxW;
	green_rect.h = boxH;

	red_box = NULL;
	red_box = IMG_LoadTexture(renderer, "images/redsquare.bmp");

	red_rect.x = screenW / 2 - (boxW);
	red_rect.y = 20 + boxH + (boxH * 0.2);
	red_rect.w = boxW;
	red_rect.h = boxH;

	blue_box = NULL;
	blue_box = IMG_LoadTexture(renderer, "images/bluesquare.bmp"); //laddar den gula bilden i yellow_box

	blue_rect.x = 10 + (screenW / 2);
	blue_rect.y = 20 + boxH + (boxH * 0.2);;
	blue_rect.w = boxW;  //Bredd
	blue_rect.h = boxH;  //10 + (screenW / 2)
}
