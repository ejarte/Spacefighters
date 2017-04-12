/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include "main.h"

int main(int argc, char* args[])
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

		initImages();

		SDL_RenderClear(renderer); //Clears the screen

		//Ritar ut bilderna på fönstret
		SDL_RenderCopy(renderer, yellow_box, NULL, &yellow_rect); //Null eftersom vi inte ska croppa bilden
		SDL_RenderCopy(renderer, green_box, NULL, &green_rect);
		SDL_RenderCopy(renderer, red_box, NULL, &red_rect);
		SDL_RenderCopy(renderer, blue_box, NULL, &blue_rect);

		SDL_RenderPresent(renderer);
	}

	//Tar bort pekarna ur minnet för säkerhets skull
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(yellow_box);
	SDL_DestroyTexture(green_box);
	SDL_DestroyTexture(red_box);
	SDL_DestroyTexture(blue_box);

	return 0;

}