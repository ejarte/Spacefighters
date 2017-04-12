#include "main.h"

void drawScreen()
{
	SDL_RenderClear(renderer); //Clears the screen
							   //Ritar ut bilderna på fönstret
	SDL_RenderCopy(renderer, yellow_box, NULL, &yellow_rect); //Null eftersom vi inte ska croppa bilden
	SDL_RenderCopy(renderer, green_box, NULL, &green_rect);
	SDL_RenderCopy(renderer, red_box, NULL, &red_rect);
	SDL_RenderCopy(renderer, blue_box, NULL, &blue_rect);

	SDL_RenderPresent(renderer);
}