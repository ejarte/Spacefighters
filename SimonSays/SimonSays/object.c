/*
*	File		:	object.c
*	Author(s)	:	Tiago Redaelli
*	Modified	:	
*	Version		:	0.2
*
*	Support functions for the struct Object and a linked index
*
*	Change-log
*	Jacob:	calculate collision speed
*	Tiago:	changed from dynamic to static memory allocation (v0.2)
*
*/

#include "object.h"
#include "collision.h"

int obj_recycled[MAX_NUM_OBJ];
int obj_recycle_size;

void object_init()
{
	objHead = UNDEFINED;
	objTail = UNDEFINED;
	objIndex_size = 0;
	obj_recycle_size = 0;
	printf("Object Index Initialized...\n");

	for (int i = 0; i < MAX_NUM_OBJ; i++) {
		object[i].next = UNDEFINED;
	}
}

int object_index()
{
	int index;

	// Gets a unique index number

	// First it looks for a recycled number
	if (obj_recycle_size > 0) {
		obj_recycle_size--;
		index = obj_recycled[obj_recycle_size];
	}
	// Otherwise it generates a new one
	else {
		index = objIndex_size++;
	}

	// Links the new index into the chain

	// Add first
	if (objHead == UNDEFINED) {
		objHead = index;
		objHead = index;
		if (objTail == UNDEFINED) {
			objTail = index;
		}
	//	object[index].prev = UNDEFINED;	// define previous node
	}
	// Add after
	else {
		object[objTail].next = index;
		//object[index].prev = objTail;	// define previous node
		objTail = index;
	}
	object[index].next = UNDEFINED;		// define next node

	//printf("%d indexed.\n", index);

	return index;
}

void  object_deindex(int index)	
{

	int prev, next;

	// Recycles the number
	obj_recycled[obj_recycle_size++] = index;

	//printf("Object deindexed: %d\n", index);

	// Removes the index from the linked list chain

	// Remove first
	if (objHead == index) {
		objHead = object[index].next;
	}
	// Remove after
	else {
		int prev = objHead;
		int cur = object[objHead].next;
		while (cur != UNDEFINED) {
			if (index == cur) {
				object[prev].next = object[cur].next;
				// remove tail
				if (index == objTail) {
					objTail = prev;
				}
				break;
			}
			prev = cur;
			cur = object[cur].next;
		}
		object[index].next = UNDEFINED;
	}
}

void object_setup(struct Object* o, int index, int type, int x, int y, int w, int h, double facingAng, double facingImgOffset, struct Sprite *s, struct Animation *a)
{
	o->id_index = index;
	o->id_type = type;
	o->center_x = x;
	o->center_y = y;
	o->prev_x = x;
	o->prev_y = y;
	o->w = w;
	o->h = h;

	o->ptr_center_x = &o->center_x;
	o->ptr_center_y = &o->center_y;

	o->facing = facingAng;
	o->IMG_facingOffset = facingImgOffset;
	o->sprite = s;
	animation_copy(a, &(o->animation));
	o->show = true;
	o->delta_x = 0;
	o->delta_y = 0;
	o->speed_x = 0;
	o->speed_y = 0;
	o->speed_max = DEFAULT_MAX_SPEED;
	o->drag = DEFAULT_DRAG;
	o->acc = DEFAULT_ACC;
	o->collision.enabled = false;
	o->dmg_on_impact;				// used by projectiles
	o->next = UNDEFINED;			// used to iterate through all objects
	o->source_id = UNDEFINED;		// used by projectiles
	o->power_id = UNDEFINED;
}

void object_render(SDL_Renderer* renderer, struct Object* o)
{
	if (o->show) {
		SDL_Rect dsrect = { o->center_x - o->w / 2, o->center_y - o->w / 2, o->w, o->h };
		SDL_Rect srect = sprite_getClipRect(o->sprite, animation_getCurColumn(&(o->animation)), animation_getCurRow(&(o->animation)));
		SDL_Point center = { o->w / 2, o->h / 2 };
		SDL_RenderCopyEx(renderer, o->sprite->texture, &srect, &dsrect, o->facing + o->IMG_facingOffset, &center, SDL_FLIP_NONE);
	
		// Debug reveals collision box
		if (debug_show_collision_box) {
			collision_boxRender(renderer, &o->collision, o->center_x, o->center_y);
		}

	}
}

void object_tick(struct Object* o)
{
	animation_tick(&(o->animation));
}

void object_move(struct Object* o)
{
	o->prev_x = o->center_x;
	o->prev_y = o->center_y;
	o->delta_x *= o->drag;
	o->delta_y *= o->drag;
	o->speed_x *= o->drag;
	o->speed_y *= o->drag;
	int dx = o->delta_x + o->speed_x;
	int dy = o->delta_y + o->speed_y;
	o->center_x += dx;
	o->center_y += dy;
}

bool object_isMoving(struct Object* o)
{
	return o->prev_x != o->center_x || o->prev_y != o->center_y;
}

// Facing

void object_setFacingToPoint(struct Object* o, SDL_Point p)
{
	double dx, dy;
	dx = o->center_x - p.x;
	dy = o->center_y - p.y;
	o->facing = (atan2(dx, dy) * 180.0) / M_PI *-1;
}

// Speed

void object_accelerateSpeedX(struct Object* o)
{
	if (o->speed_x < o->speed_max) {
		o->speed_x += o->acc;
		if (o->speed_x > o->speed_max)
			o->speed_x = o->speed_max;
	}
}

void object_accelerateSpeedY(struct Object* o)
{
	if (o->speed_y < o->speed_max) {
		o->speed_y += o->acc;
		if (o->speed_y > o->speed_max)
			o->speed_y = o->speed_max;
	}
}

void object_deaccelerateSpeedX(struct Object* o)
{
	if (o->speed_x > o->speed_max * -1) {
		o->speed_x -= o->acc;
		if (o->speed_x < -1 * o->speed_max)
			o->speed_x = -1 * o->speed_max;
	}
}

void object_deaccelerateSpeedY(struct Object* o)
{
	if (o->speed_y > o->speed_max * -1) {
		o->speed_y -= o->acc;
		if (o->speed_y < -1 * o->speed_max)
			o->speed_y = -1 * o->speed_max;
	}
}

void object_setCollisionBox(struct Object* o, int w, int h) {
	o->collision.w = w;
	o->collision.h = h;
	o->collision.enabled = true;
	o->collision.type = COLLISION_TYPE_BOX;
	if (w > h)
		o->collision.r = w;
	else o->collision.r = h;
}

void object_setCollisionCircle(struct Object* o, int r)
{
	o->collision.r = r;
	o->collision.w = r;
	o->collision.h = r;
	o->collision.enabled = true;
	o->collision.type = COLLISION_TYPE_CIRCLE;
}

bool object_instersection(struct Object* o1, struct Object* o2)
{
	if (o1->collision.enabled == false ||  o2->collision.enabled == false || o1->show == false || o2->show == false) {
		return false;
	}
	if (o1->collision.type == COLLISION_TYPE_BOX) {
		return collision_boxIntersection(o1->collision, o1->center_x, o1->center_y, o2->collision, o2->center_x, o2->center_y);
	}
	else if (o1->collision.type == COLLISION_TYPE_CIRCLE) {
		return collision_circleIntersection(o1->collision, o1->center_x, o1->center_y, o2->collision, o2->center_x, o2->center_y);
	}
	return false;
}

void object_calculateCollisionSpeed(struct Object* o1, struct Object* o2)
{
	double tempX, tempY;	//sparar värdena temporärt i temp så att andra objektet kan få dess hastighet

	o1->delta_x += o1->speed_x;
	o1->delta_y += o1->speed_y;
	o2->delta_x += o2->speed_x;
	o2->delta_y += o2->speed_y;
	o1->speed_x = 0;
	o1->speed_y = 0;
	o2->speed_x = 0;
	o2->speed_y = 0;
	tempX = o1->delta_x;
	tempY = o1->delta_y;
	o1->delta_x = o2->delta_x;
	o2->delta_x = tempX;
	o1->delta_y = o2->delta_y;
	o2->delta_y = tempY;
	object_move(o1);
	object_move(o2);
}