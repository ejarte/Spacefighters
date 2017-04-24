#include "object.h"
#include "animation.h"
#include "sprite.h"
#include "collision.h"

//================================================================================================================
//	TO-DO
//================================================================================================================
// - Adjuct rotation between different images, so 0 degrees is always north
// - make scale also change the collision size if set
// - Add delta_x and delta_y for movement on tick
// - Add movementTowardsPolarProjection(facing angle, distance)
// - make x y be the center of the image
// - adjuct so the collision size is centered to the image
// - Make the object indexer be a linked list, so the last object added is also the last object rendered


//================================================================================================================
// Object Class: Struct
//================================================================================================================

struct Object_type {
	Animation *anim;
	Sprite *sprite;
	SDL_Rect rect;
	int topX;
	int topY;
	int w;
	int h;

	double scale;
	double facing;
	bool show;				// Show on screen
	bool activeAnimation;	// Play animation
	int type;				// Type id
	int index;				// Object id

	struct Collision* collision;
	bool collisionEnabled;
};

//================================================================================================================
// Object Class: Allocation
//================================================================================================================
/*
Object* createObject(int type, int x, int y, int w, int h, double facingAngle, Sprite *s, Animation *a, bool show, bool collision)
{
	Object* o = malloc(sizeof(Object));
	o->sprite = s;
	o->type = type;
	o->scale = 1.;
	object_setAnimation(o, a, show);
	o->activeAnimation = show;
	o->show = show;
	o->facing = facingAngle;
	// Index
	o->index = indexObject();
	object[o->index] = o;
	// Dimension
	o->topX = x;
	o->topY = y;
	o->w = w;
	o->h = h;
	// Collision
	// hårdkodat offset
	o->collision = createCollisionBox(0, 0, 0, 0, 18, 18);
	o->collisionEnabled = false;
	return o;
}

// Not complete
Object* createObjectCopy(Object* srcs, int x, int y, double facing)
{
	Object* dest = createObject(srcs->type, x, y, srcs->w, srcs->h, facing, srcs->sprite, srcs->anim, srcs->show, /*srcs->collision.enabled*/// true);
	//dest->scale = srcs->scale;
	//return dest;
//}

// Not complete
/*
void destroyObject(Object *o)
{
	destroyCollisionBox(o->collision);
	free(o);
}

//================================================================================================================
// Object Class: Collision
//================================================================================================================

/* object_setCollisionBoxDimension: Defines the collision box dimensions
	@o			- Object
	@w			- Width
	@h			- Height
	@x_offset	- the offset from topX
	@y_offset	- the offset from topY
	@render		- if true it will render a black box, displaying the collision dimension
/*
void object_setCollisionBoxDimension(Object* o, int w, int h, int x_offset, int y_offset, bool render)
{
	collision_setBox(o->collision, o->topX, o->topY, w, h, x_offset, y_offset, true);
	o->collisionEnabled = true;
}

bool object_hasCollision(Object *o)
{
	return o->collisionEnabled;
}

void object_enableCollision(Object *o)
{
	o->collisionEnabled = true;
}

void object_disableCollision(Object *o)
{
	o->collisionEnabled = false;
}

//================================================================================================================
// Object Class: Sprite | Animation | Rendering
//================================================================================================================

void object_setSprite(Object *o, Sprite *s)
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

/*	object_tick takes a Object and updates the object animation, collision, position */
/*
void object_tick(Object *o)
{
	if (o->activeAnimation)
		anim_tick(o->anim);
	
	// Move collision!
	if (o->collisionEnabled) {
		collision_setPosition(o->collision, o->topX, o->topY);
	}
}

void object_render(SDL_Renderer* renderer, Object *o)
{
	if (o->show) {
		SDL_Rect dsrect = { o->topX, o->topY, o->w, o->h };
		SDL_Rect srect = sprite_getClipRect(o->sprite, anim_getCurCol(o->anim), anim_getCurRow(o->anim));
		SDL_Point center = {o->w/2, o->h/2};
		SDL_RenderCopyEx(renderer, sprite_getTexture(o->sprite), &srect, &dsrect, o->facing, &center, SDL_FLIP_NONE);

		// Debug purpose - render colision box
		collision_boxRender(o->collision, renderer);
	}
}

//================================================================================================================
// Object Class: Facing Angle
//================================================================================================================

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

//================================================================================================================
// Object Class: Position
//================================================================================================================

int* object_getPointerToX(Object *o)
{
	return 0;
}

int* object_getPointerToY(Object *o)
{
	return 0;
}

void object_setPosX(Object *o, int y)
{
	o->topY = y;
}

void object_setPosY(Object *o, int y)
{
	o->topY = y;
}

void object_setPosXY(Object *o, int x, int y)
{
	o->topX = x;
	o->topY = y;
}

int object_getPosX(Object *o)
{
	return o->topX;
}

int object_getPosY(Object *o)
{
	return o->topY;
}

// Dimension

void object_setWidth(Object *o, int w)
{
	o->w = w;
}

void object_setHeight(Object *o, int h)
{
	o->h = h;
}

int object_getWidth(Object *o)
{
	return o->w;
}

int object_getHeight(Object *o)
{
	return o->h;
}

// Not Complete
void object_setScale(Object *o, float scale)
{
	if (scale < 0.1)	// lower limit
		scale = 0.1;

	if (scale > 5.)		// upper limit
		scale = 5.;
	
	// Adjuct
	int w = o->w;
	int h = o->h;
	o->w = o->w*scale;
	o->h = o->h*scale;
	o->topX = o->topX + (w - o->w) / 2;
	o->topY = o->topY + (h - o->h) / 2;
	o->scale = scale;
}

double object_getScale(Object *o)
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

void object_print(Object* o)
{
	printf("-----------------------------------------\n");
	printf("- Object --------------------------------\n");
	printf("-----------------------------------------\n");
	printf("x, y \t\t%d,\t%d \nw, h \t\t%d,\t%d\n", o->topX, o->topY, o->w, o->h);
	printf("scale \t\t%f\n", o->scale);
	printf("facing \t\t%f\n", o->facing);
	if (o->show) printf("show\t\ttrue\n"); else printf("show\t false\n");
	if (o->activeAnimation) printf("animation\tactive\n"); else printf("animation\tinactive\n");
	printf("type_id\t\t%d\n", o->type);
	printf("obj_id \t\t%d\n", o->index);
	//if (o->collision.enabled) 	printf("collision\tenabled\n"); else 	printf("collision\tdisabled\n");
	anim_print(o->anim);
	sprite_print(o->sprite);
	printf("-----------------------------------------\n");
}

// Funkar inte ännu...

bool object_checkForBoxCollision(Object* o1, Object* o2)
{
	/*
	if (o1->collision.right >= o2->collision.left) 
		return true;
	if (o1->collision.left <= o2->collision.right)
		return true;
	if (o1->collision.top <= o2->collision.bottom)
		return true;
	if (o1->collision.bottom >= o2->collision.top)
		return true;
	*//*
	return false;
}
*/