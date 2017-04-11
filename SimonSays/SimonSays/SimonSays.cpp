/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include "stdafx.h"

int main(int argc, char* args[])
{
	bool quit = false;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = NULL;

	//Skapar ett fönster i fullskärmläge
	window = SDL_CreateWindow("SimonSays", 100, 100, 600, 400, SDL_WINDOW_SHOWN);
	
	if (window == NULL)
	{
		printf("Error, Window can't be desplayed");
		return(0); //avslutar programmet
	}

	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Event mainEvent;

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
		SDL_RenderPresent(renderer);
	}

	return 0;

}