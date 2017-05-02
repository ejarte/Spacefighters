#include "collision.h"
/*
struct Collision_Type {
	SDL_Point* p;
	int x_offset;
	int y_offset;
	int w;
	int h;
	int r;
	int type;
};

Collision* createCollisionBox(SDL_Point* p, int w, int h, int x_offset, int y_offset)
{
	Collision* c = malloc(sizeof(Collision));
	printf("Box Collision Created...\n");
	c->w = w;
	c->h = h;
	w /= 2;
	h /= 2;
	c->p = p;

	// Offset
	c->x_offset = x_offset;
	c->y_offset = y_offset;

	// Collision Type
	c->type = COLLISION_TYPE_BOX;

	// Sets the radius to the largest dimension
	if (w >= h)
		c->r = w;
	else
		c->r = h;

	return c;
}

Collision* createCollisionCircle(SDL_Point* p, int d, int x_offset, int y_offset)
{
	Collision* c = malloc(sizeof(Collision));
	printf("Circle Collision Created...\n");

	c->w = d;
	c->h = d;
	d /= 2;
	c->r = d;
	c->p = p;
	c->r = d;
	// Offset
	c->x_offset = x_offset;
	c->y_offset = y_offset;
	// Collision Type
	c->type = COLLISION_TYPE_CIRCLE;
}

void destroyCollision(Collision* c)
{
	free(c);
}

int collision_getType(Collision* c)
{
	return c->type;
}

SDL_Rect collision_getRect(Collision* c)
{
	SDL_Rect r = { c->p->x + c->x_offset - (c->w / 2), c->p->y + c->y_offset - (c->h / 2),c->w, c->h };	
	return r;
}

// Optimerbar
bool collision_circleIntersection(Collision* c1, Collision* c2)
{
	return (double)(c1->r + c2->r) > distanceBetweenPointsCoordinates(c2->p->x + c2->x_offset, c1->p->x + c1->x_offset, c2->p->y + c2->y_offset, c1->p->y + c1->y_offset);
}

// Optimerbar
bool collision_boxIntersection(Collision* c1, Collision* c2)
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

// Saknas render för cirklar

void collision_boxRender(SDL_Renderer* renderer, Collision* c)
{
	SDL_Rect rect = collision_getRect(c);
	SDL_RenderFillRect(renderer, &rect);
}

void collision_print(Collision* c)
{
	printf("-----------------------------------------\n");
	printf("- Collision -----------------------------\n");
	printf("-----------------------------------------\n");
	printf("x, y \t\t%d, %d\n", c->p->x, c->p->y);
	printf("-----------------------------------------\n");
}

*/