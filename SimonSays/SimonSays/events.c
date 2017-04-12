#include "main.h"

void eventLoop()
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
}