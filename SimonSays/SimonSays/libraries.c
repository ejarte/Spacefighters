#include "libraries.h"

SDL_Color createColor(int r, int g, int b, int a)
{
	SDL_Color c;
	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return c;
}
