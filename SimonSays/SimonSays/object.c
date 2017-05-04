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

	printf("%d indexed.\n", index);

	return index;
}


void  object_deindex(int index)	
{

	int prev, next;

	// Recycles the number
	obj_recycled[obj_recycle_size++] = index;

	printf("Object deindexed: %d\n", index);

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



/*
#include "animation.h"
#include "sprite.h"
#include "collision.h"


struct Object_type {
	Animation *anim;			// Animation
	Sprite *sprite;				// Sprite
	SDL_Point* pos_center;		// Center position
	double delta_x;				// Change in x axis
	double delta_y;				// Change in y axis
	//int cyclesPerDelta;			// Number of frames before delta x and y is updated
	//int tick;
	//SDL_Point* pos_offset;	// Offset from center position x- and y-axis.		// NOT IMPLEMENTED
	double facingAngle;			// The objects facing angle							
	double* facingAnglePtr;		// A pointer to the object facing angle				
	double facingIMG_offset;	// This is to calibrate the image to the game facing angle so that 0 is always north when using facingAngle.
	int w;						// Object width
	int h;						// Object height
	int type_id;				// Unique object type id
	int obj_id;					// Unique object id, used to find object[i]
	int custom_id;				// Use this to link this to some other index		// NOT IMPLEMENTED OR USED YET
	bool showObj;				// flag to show/hide the object from palyers
	bool activeAnim;			// flag for pausing/resuming current animation
	bool collisionEnabled;		// flag for enabling/disabling collision
	double hp;					// object hit points
	Collision* collision;		// struct pointer containing collision data

	double mass;				// Object mass
};

 
Object* createObject(int type, int x, int y, int w, int h, double facingAngle, double facingIMGOffset, Sprite *s, Animation *a)
{
	// Debug
	tot_created_obj++;

	Object* o = malloc(sizeof(Object));	// Allokerar 
	o->pos_center = malloc(sizeof(SDL_Point));
	o->type_id = type;
	o->pos_center->x = x;
	o->pos_center->y = y;
	
	o->w = w;
	o->h = h;
	o->sprite = s;
	o->facingAngle = facingAngle;
	o->facingAnglePtr = &o->facingAngle;
	o->facingIMG_offset = facingIMGOffset;
	o->showObj = true;
	object_setAnimation(o, a, true);
	// Collision
	o->collisionEnabled = false;
	o->collision = NULL;
	// Facing Angle
	o->facingAngle = facingAngle;
	o->facingAnglePtr = &o->facingAngle;
	o->facingIMG_offset = facingIMGOffset;
	// Delta X & Y 
	//o->cyclesPerDelta = 5; // Cycles required before it updates position
	//o->tick = 0;
	o->delta_x = 0;
	o->delta_y = 0;
	o->hp = HP_INVULNERABLE;
	// Index
	// Ändra denna funktion till att ta emot ett objekt
	o->obj_id = indexObject();
	object[o->obj_id] = o;
	o->custom_id = -1; // unused
	
	o->mass = 1;	// Default mass

	return o;
}

void destroyObject(Object* o)
{
	printf("Object destroyed...\n");
	deindexObject(o);
	free(o);
}

// Dimensions

int object_getWidth(Object *o)
{
	return o->w;
}

int object_getHeight(Object* o)
{
	return o->h;
}

// Position
void object_setPos(Object *o, int x, int y)
{
	o->pos_center->x = x;
	o->pos_center->y = y;
}

void object_setX(Object* o, int x)
{
	o->pos_center->x = x;
}

void object_setY(Object* o, int y)
{
	o->pos_center->y =  y;
}

int object_getX(Object *o)
{
	return o->pos_center->x;
}

int object_getY(Object *o)
{
	return o->pos_center->y;
}

// Returns a pointer to the center position, useful for linking one point to this object. 
SDL_Point* object_getPosPtr(Object* o)
{
	return o->pos_center;
}

// links the center point to another pointer useful for attaching this object onto another 
void object_setPosPtr(Object* o, SDL_Point* p)
{
	o->pos_center = p;
}

// Facing Angle 

void object_addFacingAngle(Object *o, double angle)
{
	o->facingAngle += angle;
	o->facingAnglePtr = &o->facingAngle;
}

void object_setFacingAngle(Object *o, double angle)
{
	o->facingAngle = angle;
	o->facingAnglePtr = &o->facingAngle;
}

double object_getFacingAngle(Object *o)
{
	return o->facingAngle;
}

// Returns a pointer to the facing angle useful for linking one point to this object. 
double* object_getFacingAnglePtr(Object* o)
{
	return o->facingAnglePtr;
}

/* links the facing angle to a pointer, useful when linking two objects together 
void object_setFacingAnglePtr(Object* o, double* p)
{
	o->facingAnglePtr = p;
}

// Status

void object_setLife(Object* o, double life)
{
	o->hp = life;
}

double object_getLife(Object* o)
{
	return o->hp;
}

void object_addLife(Object* o, double life)
{
	o->hp += life;
}

// Collision

void object_disableCollision(Object* o)
{
	o->collisionEnabled = false;
}

void object_enableCollision(Object* o)
{
	o->collisionEnabled = true;
}

void object_setCollisionBoxDimension(Object* o, int w, int h, int x_offset, int y_offset)
{
	// Destroy previous collision box
	if (o->collision != NULL)
		destroyCollision(o->collision);

	// Create a new one
	o->collision = createCollisionBox(o->pos_center, w, h, x_offset, y_offset);
	o->collisionEnabled = true;
}

void object_setCollisionCircleDiameter(Object* o, int d, int x_offset, int y_offset)
{
	// Destroy previous collision box
	if (o->collision != NULL)
		destroyCollision(o->collision);

	// Create a new one
	o->collision = createCollisionCircle(o->pos_center, d, x_offset, y_offset);
	o->collisionEnabled = true;
}

bool object_checkForCollision(Object* o1, Object* o2 )
{
	if (o1->collision == NULL || o2->collision == NULL || o1->collisionEnabled == false || o2->collisionEnabled == false)
		return false;

	if (collision_getType(o1) == COLLISION_TYPE_BOX)
		return collision_boxIntersection(o1->collision, o2->collision);
	// else 
	return collision_circleIntersection(o1->collision, o2->collision);
}

Collision* object_getCollision(Object* o)
{
	return o->collision;
}

// Update

void object_render(SDL_Renderer* renderer, Object *o, bool debugCollision)
{
	if (o->showObj) {
		SDL_Rect dsrect = { o->pos_center->x - o->w/2, o->pos_center->y - o->w / 2, o->w, o->h };
		SDL_Rect srect = sprite_getClipRect(o->sprite, anim_getCurCol(o->anim), anim_getCurRow(o->anim));
		SDL_Point center = { o->w / 2, o->h / 2 };
		double angle = *(o->facingAnglePtr);
		SDL_RenderCopyEx(renderer, sprite_getTexture(o->sprite), &srect, &dsrect, angle + o->facingIMG_offset, &center, SDL_FLIP_NONE);

		// debug render
		//if (debugCollision && o->collision != NULL)
		//	collision_boxRender(renderer, o->collision);
	}
}

void object_tick(Object* o)
{
	// Tickar animationen
	if (o->activeAnim)
		anim_tick(o->anim);
	
	// Förändrar postionen i x och y led
	if (o->delta_x != 0 || o->delta_y != 0) {
		//printf("Delta_x, y: %d %d\n", o->delta_x, o->delta_y);
		object_setPos(o, o->pos_center->x + o->delta_x, o->pos_center->y + o->delta_y);
	}
}

// View

void object_setSprite(Object *o, Sprite *s)
{
	o->sprite = s;
}

void object_setAnimation(Object *o, Animation* a, bool activeAnimation)
{
	o->anim = copyAnimationType(a);
}

Animation* object_getAnimation(Object *o)
{
	return o->anim;
}

void object_pauseAnimation(Object *o)
{
	o->activeAnim = false;
}

void object_resumeAnimation(Object *o)
{
	o->activeAnim = true;
}

void object_show(Object *o)
{
	o->showObj = true;
}

void object_hide(Object *o)
{
	o->showObj = false;
}

// Identification

int object_getTypeId(Object *o)
{
	return o->type_id;
}

int object_getObjId(Object *o)
{
	return o->obj_id;
}

/* Used to link this object to another index 
void object_setCustomId(Object* o, int id)
{
	o->custom_id = id;
}

int object_getCustomId(Object *o)
{
	return o->custom_id;
}

// Delta X & Y

void object_calculateCollisionSpeed(Object* o1, Object *o2)
{
	double tempX, tempY, tempMass;

	tempX = o1->delta_x; //sparar värdena temporärt i temp så att andra objektet kan få dess hastighet
	tempY = o1->delta_y;
	tempMass = 0.5;

	o1->delta_x = o2->delta_x;
	o2->delta_x = tempX;
	o1->delta_y = o2->delta_y;
	o2->delta_y = tempY;
}

void object_setMass(Object* o, double mass) {
	o->mass = mass;
}

double object_getMass(Object* o)
{
	return o->mass;
}

void object_setDeltaX(Object *o, int delta)
{
	o->delta_x = delta;
}

void object_setDeltaY(Object *o, int delta)
{
	o->delta_y = delta;
}

int object_getDeltaX(Object *o)
{
	return o->delta_x;
}

int object_getDeltaY(Object *o)
{
	return o->delta_y;
}

/* Adds delta_x and delta_y to the objects delta x and y
void object_addToDelta(Object* o, int delta_x, int delta_y)
{
	o->delta_x += delta_x;
	o->delta_y += delta_y;
}

void object_clearDeltaXY(Object *o)
{
	o->delta_x = o->delta_y = 0;
}

// Debug
void object_print(Object *o)
{
	// Not implemented
}

//================================================================================================================
// Object Index 
//================================================================================================================

struct ObjectIndex {
	int max;							// The highest indexed value
	int recycled;						// amount of recycled numbers
	int recycledNumber[MAX_OBJECTS];	// Recycled numbers
};

struct ObjectIndex obj_index;

bool object_indexer_enabled = false;

void objectIndex_flagEnabled(bool flag)
{
	object_indexer_enabled = flag;
}

void initObjectIndex()
{
	for (int i = 0; i < MAX_OBJECTS; i++) {
		object[i] = NULL;
	}
	obj_index.max = 0;
	obj_index.recycled = 0;

	tot_created_obj = 0;
}

int getObjectIndexMax()
{
	return obj_index.max;
}

int indexObject()
{
	// If there are recycled numbers use them first
	if (obj_index.recycled > 0) {
		obj_index.recycled--;
		printf("Object indexed: %d\n", obj_index.recycledNumber[obj_index.recycled]);
		return obj_index.recycledNumber[obj_index.recycled];
	}

	// Otherwise generate a new index value 
	if (obj_index.max < MAX_OBJECTS) {
		printf("Object indexed: %d\n", obj_index.max);
		return obj_index.max++;
	}
	printf("ERROR: objectIndex_getIndex_____IndexOutOfBounds\n");
	return -1;
}

void deindexObject(Object *o)
{
	if (o == NULL) {
		printf("Error: deindexObject - nullpointer reference.\n");
		return;
	}
	int index = o->obj_id;
	if (object[index] != NULL) {
		object[index] = NULL;
		obj_index.recycledNumber[obj_index.recycled++] = index;
		printf("Object deindexed: %d\n", index);
	}
	else {
		printf("ERROR: objectIndex_deindexInt_____Attemting to deindex an unallocated index.\n");
	}
}

void objectIndex_deindexInt(int index)
{
	if (object[index] != NULL) {
		object[index] = NULL;
		obj_index.recycledNumber[obj_index.recycled++] = index;
		printf("Object deindexed: %d\n", index);
	}
	else {
		printf("ERROR: objectIndex_deindexInt_____Attemting to deindex an unallocated index.\n");
	}
}

void objectIndex_print()
{
	printf("Object Indexer...\n");
	printf("max = %d\n recycled = %d\n", obj_index.max, obj_index.recycled);
	printf("Objects:\n");
	for (int i = 0; i < obj_index.max; i++) {
		if (object[i] != NULL) {
			printf("object[%d]\n", i);
		}
	}
	printf("Recycled:\n");
	for (int i = 0; i < obj_index.recycled; i++) {
		printf("%d, ", obj_index.recycledNumber[i]);
	}
}

*/