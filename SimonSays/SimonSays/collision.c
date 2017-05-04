#include "collision.h"

SDL_Rect collision_getRect(struct Collision c, int x, int y)
{
	SDL_Rect r = { x - (c.w / 2), y - (c.h / 2), c.w, c.h };
	return r;
}

bool collision_circleIntersection(struct Collision c1, int x1, int y1, struct Collision c2, int x2, int y2)
{
	return (double)c1.r + c2.r >  distanceBetweenPointsCoordinates(x1, x2, y1, y2);
}

bool collision_boxIntersection(struct Collision c1, int x1, int y1, struct Collision c2, int x2, int y2)
{
	// Rect A och B är överflödiga går att optimera, kopierat från lazyFoo.
	SDL_Rect A = collision_getRect(c1, x1, y1);
	SDL_Rect B = collision_getRect(c2, x2, y2);

	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h; 

	//Calculate the sides of rect B
	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
		return false;

	if (topA >= bottomB)
		return false;

	if (rightA <= leftB)
		return false;

	if (leftA >= rightB)
		return false;

	//If none of the sides from A are outside B
	return true;
}

void collision_boxRender(SDL_Renderer* renderer, struct Collision* c, int x, int y)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect rect = collision_getRect(*c, x, y);
	SDL_RenderFillRect(renderer, &rect);
}