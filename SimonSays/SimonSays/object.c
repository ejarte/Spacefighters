#include "object.h"
#include "animation.h"
#include "sprite.h"

struct Collision_Box {
	int left;
	int right; 
	int top;
	int bottom;
	bool enabled;
};

struct Object_type {
	Animation *anim;
	Sprite **sprite;
	SDL_Rect rect;
	int x;
	int y;
	int w;
	int h;
	double scale;
	double facing;
	bool show;
	bool activeAnimation;
	int type;
	int index;
	struct Collision_Box collision;
};

Object* createObject(int type, int x, int y, int w, int h, double facingAngle, Sprite **s, Animation *a, bool show, bool collision)
{
	Object* o = malloc(sizeof(Object));
	o->sprite = s;
	o->type = type;
	o->scale = 1.;
	o->anim = (a);
	o->activeAnimation = show;
	o->show = show;
	o->facing = facingAngle;
	// Dimension
	o->x = x;
	o->y = y;
	o->w = w;
	o->h = h;
	// Collision
	o->collision.enabled = collision;
	o->collision.left = o->x;
	o->collision.right = o->x + o->w;
	o->collision.top = o->y;
	o->collision.bottom = o->y + o->h;
	return o;
}

void destroyObject(Object *o)
{
	free(o);
}

void object_setSprite(Object *o, Sprite **s)
{
	o->sprite = s;
}

void object_setAnimation(Object *o, Animation* a, bool playAnimation)
{
	o->anim = copyAnimationType(a);
	o->activeAnimation = playAnimation;
}

void object_pauseAnimation(Object *o)
{
	o->activeAnimation = false;
}

void object_resumeAnimation(Object *o)
{
	o->activeAnimation = true;
}

void object_tickAnimation(Object *o)
{
	anim_tick(o->anim);
}

/*
void sprite_RenderCopy(SDL_Renderer* renderer, Sprite *ptr_sprite, int col, int row, SDL_Rect dsrect)
{
// Renders to screen
SDL_Rect srect = sprite_getClipRect(ptr_sprite, col, row);
SDL_RenderCopy(renderer, ptr_sprite->texture, &srect, &dsrect);
}
*/

void object_render(SDL_Renderer* renderer, Object *o)
{
	if (o->show) {
		SDL_Rect dsrect = { o->x, o->y, o->w, o->h };
			
			//createRect(o->x, o->y, o->w, o->h);
		Sprite **s = o->sprite;
		Sprite *s2 = *s;
		//
		//SDL_Texture* texture = sprite_getTexture(s2);
		SDL_Rect srect = sprite_getClipRect(s2, anim_getCurCol(o->anim), anim_getCurRow(o->anim));

		SDL_Point center = {o->w/2, o->h/2};

		//SDL_RenderCopy(renderer, sprite_getTexture(s2), &srect, &dsrect);

		//printf("%d", o->facing);
		//o->facing += 3.;

		SDL_RenderCopyEx(renderer, sprite_getTexture(s2), &srect, &dsrect, o->facing, &center, SDL_FLIP_NONE);


		//SDL_RenderCopyEx(renderer, spaceship_getShipTexture(s1), &rects[frame], &spaceship_rect, 180., &center, flip); //ritar ut skeppet i fönstret

		//sprite_RenderCopy(renderer, s2, anim_getCurCol(o->anim), anim_getCurRow(o->anim), disp_rect);
	}
}

void object_addToFacingAngle(Object *o, double angle)
{
	o->facing += angle;
}

void object_setFacingAngle(Object *o, double angle)
{
	o->facing = angle;
}

double object_getFacingAngle(Object *o)
{
	return o->facing;
}

void object_setPosX(Object *o, int x)
{

	o->x = x;
	o->collision.left = o->x;
	o->collision.right = o->x + o->w;
}

void object_setPosY(Object *o, int y)
{
	o->y = y;
	o->collision.top = o->y;
	o->collision.bottom = o->y + o->h;
}

int object_getPosX(Object *o)
{
	return o->x;
}

int object_getPosY(Object *o)
{
	return o->y;
}

void object_setWidth(Object *o, int w)
{
	o->w = w;
	o->collision.right = o->x + o->w;
}

void object_setHeight(Object *o, int h)
{
	o->h = h;
	o->collision.bottom = o->y + o->h;
}

int object_getWidth(Object *o)
{
	return o->w;
}

int object_getHeight(Object *o)
{
	return o->h;
}

void object_setScale(Object *o, float scale)
{
	if (scale < 0.1)
		scale = 0.1;

	if (scale > 5.) {
		scale = 5.;
	}

	int w = o->w;
	int h = o->h;
	o->w = o->w*scale;
	o->h = o->h*scale;
	o->x = o->x + (w - o->w) / 2;
	o->y = o->y + (h - o->h) / 2;

	o->scale = scale;
}

float object_getScale(Object *o)
{
	return o->scale;
}

void object_show(Object *o)
{
	o->show = true;
}

void object_hide(Object *o)
{
	o->show = false;
}

bool object_isShown(Object *o)
{
	return o->show;
}

void object_setType(Object *o, int type)
{
	o->type = type;
}

int object_getType(Object *o)
{
	return o->type;
}

void object_setIndex(Object *o, int index)
{
	o->index = index;
}

int object_getIndex(Object *o)
{
	return o->index;
}

bool object_hasCollision(Object *o)
{
	return o->collision.enabled;
}

bool object_setCollision(Object *o, bool flag)
{
	o->collision.enabled = flag;
}

bool object_checkForBoxCollision(Object* o1, Object* o2)
{
	if (o1->collision.right >= o2->collision.left) 
		return true;
	if (o1->collision.left <= o2->collision.right)
		return true;
	if (o1->collision.top <= o2->collision.bottom)
		return true;
	if (o1->collision.bottom >= o2->collision.top)
		return true;

	return false;
}