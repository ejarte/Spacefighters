#include "main.h"

void clearPointers()
{
	//Tar bort pekarna ur minnet för säkerhets skull
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(yellow_box);
	SDL_DestroyTexture(green_box);
	SDL_DestroyTexture(red_box);
	SDL_DestroyTexture(blue_box);
}