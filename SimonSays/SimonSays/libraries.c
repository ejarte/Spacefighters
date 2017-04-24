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

double distanceBetweenPoints(SDL_Point p1, SDL_Point p2)
{
	return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double distanceBetweenPointsCoordinates(int x1, int x2, int y1, int y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}