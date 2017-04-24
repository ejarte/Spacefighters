#include "collision.h"

struct Collision_Type_Box {
	SDL_Point* p;
	int x_offset;
	int y_offset;
	int w;
	int h;
};

Collision_Box* createCollisionBox(SDL_Point* p, int w, int h, int x_offset, int y_offset)
{
	Collision_Box* c = malloc(sizeof(Collision_Box));
	printf("Box Collision Created...\n");
	c->w = w;
	c->h = h;
	w /= 2;
	h /= 2;
	c->p = p;
	c->x_offset = x_offset;
	c->y_offset = y_offset;
	return c;
}

void destroyCollisionBox(Collision_Box* c)
{
	free(c);
}

SDL_Rect collision_getRect(Collision_Box* c)
{
	SDL_Rect r = { c->p->x + c->x_offset - (c->w / 2), c->p->y + c->y_offset - (c->h / 2),c->w, c->h };	
	return r;
}

void collision_boxRender(SDL_Renderer* renderer, Collision_Box* c)
{
	SDL_Rect rect = collision_getRect(c);
	SDL_RenderFillRect(renderer, &rect);
}

bool collision_boxIntersection(Collision_Box* c1, Collision_Box* c2)
{
	// Rect A och B är överflödiga går att optimera, kopierat från lazyFoo.
	SDL_Rect A = collision_getRect(c1);
	SDL_Rect B = collision_getRect(c2);

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

// Debug

void collision_boxPrint(Collision_Box* c)
{
	printf("-----------------------------------------\n");
	printf("- Collision Box -------------------------\n");
	printf("-----------------------------------------\n");
	printf("x\t%d\n", c->p->x);
	printf("y\t%d\n", c->p->y);
	printf("w\t%d\n", c->w);
	printf("h\t%d\n", c->h);						
	printf("-----------------------------------------\n");
}
