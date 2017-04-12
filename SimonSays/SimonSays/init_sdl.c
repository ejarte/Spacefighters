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

	yellow_box = NULL;
	yellow_box = IMG_LoadTexture(renderer, "images/yellowsquare.bmp"); //laddar den gula bilden i yellow_box

	yellow_rect.x = 10;
	yellow_rect.y = 10;
	yellow_rect.w = BTNWIDTH;  //Bredd
	yellow_rect.h = BTNHEIGHT;  //Höjd

	green_box = NULL;
	green_box = IMG_LoadTexture(renderer, "images/greensquare.bmp");

	green_rect.x = 120;
	green_rect.y = 10;
	green_rect.w = BTNWIDTH;
	green_rect.h = BTNHEIGHT;

	red_box = NULL;
	red_box = IMG_LoadTexture(renderer, "images/redsquare.bmp");

	red_rect.x = 10;
	red_rect.y = 120;
	red_rect.w = BTNWIDTH;
	red_rect.h = BTNHEIGHT;

	blue_box = NULL;
	blue_box = IMG_LoadTexture(renderer, "images/bluesquare.bmp"); //laddar den gula bilden i yellow_box

	blue_rect.x = 120;
	blue_rect.y = 120;
	blue_rect.w = BTNWIDTH;  //Bredd
	blue_rect.h = BTNHEIGHT;  //Höjd
}
