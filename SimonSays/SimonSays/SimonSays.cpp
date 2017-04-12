/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#define BTNHEIGHT 100
#define BTNWIDTH 100
#include "stdafx.h"

int main(int argc, char* args[])
{
	bool quit = false;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = NULL;

	//Skapar ett fönster i fullskärmläge
	window = SDL_CreateWindow("SimonSays", 100, 100, 600, 400, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	
	if (window == NULL)
	{
		printf("Error, Window can't be desplayed");
		return(0); //avslutar programmet
	}

	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Event mainEvent;

	//laddar in bilderna

	SDL_Texture* yellow_box = NULL;
	yellow_box = IMG_LoadTexture(renderer, "yellowsquare.bmp"); //laddar den gula bilden i yellow_box

	SDL_Rect yellow_rect; //rutan där bilden kommer finnas
	yellow_rect.x = 10;
	yellow_rect.y = 10;
	yellow_rect.w = BTNWIDTH;  //Bredd
	yellow_rect.h = BTNHEIGHT;  //Höjd

	SDL_Texture* green_box = NULL;
	green_box = IMG_LoadTexture(renderer, "greensquare.bmp");

	SDL_Rect green_rect;
	green_rect.x = 120;
	green_rect.y = 10;
	green_rect.w = BTNWIDTH;
	green_rect.h = BTNHEIGHT;

	SDL_Texture* red_box = NULL;
	red_box = IMG_LoadTexture(renderer, "redsquare.bmp");

	SDL_Rect red_rect;
	red_rect.x = 10;
	red_rect.y = 120;
	red_rect.w = BTNWIDTH;
	red_rect.h = BTNHEIGHT;

	SDL_Texture* blue_box = NULL;
	blue_box = IMG_LoadTexture(renderer, "bluesquare.bmp"); //laddar den gula bilden i yellow_box

	SDL_Rect blue_rect; //rutan där bilden kommer finnas
	blue_rect.x = 120;
	blue_rect.y = 120;
	blue_rect.w = BTNWIDTH;  //Bredd
	blue_rect.h = BTNHEIGHT;  //Höjd

	while (quit == false) //körs tills användaren trycker på X uppe i fönstret
	{
		/* Check for new events */
		SDL_PollEvent(&mainEvent);
		{
			/* If a quit event has been sent */
			if (mainEvent.type == SDL_QUIT)
			{
				quit = 1;
			}
		}

		SDL_RenderClear(renderer); //Clears the screen

		//Ritar ut bilderna på fönstret
		SDL_RenderCopy(renderer, yellow_box, NULL, &yellow_rect); //Null eftersom vi inte ska croppa bilden
		SDL_RenderCopy(renderer, green_box, NULL, &green_rect);
		SDL_RenderCopy(renderer, red_box, NULL, &red_rect);
		SDL_RenderCopy(renderer, blue_box, NULL, &blue_rect);

		SDL_RenderPresent(renderer);
	}

	return 0;

}