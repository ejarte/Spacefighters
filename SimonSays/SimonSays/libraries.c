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

double distanceBetweenPointsCoordinates(int x1, int x2, int y1, int y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}