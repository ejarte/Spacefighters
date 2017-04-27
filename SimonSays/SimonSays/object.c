#include "object.h"
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
	Collision* collision;		// struct pointer containing collision dat

	double mass;				// Object mass
};
 
Object* createObject(int type, int x, int y, int w, int h, double facingAngle, double facingIMGOffset, Sprite *s, Animation *a)
{
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

/* Returns a pointer to the center position, useful for linking one point to this object. */
SDL_Point* object_getPosPtr(Object* o)
{
	return o->pos_center;
}

/* links the center point to another pointer useful for attaching this object onto another */
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

/* Returns a pointer to the facing angle useful for linking one point to this object. */
double* object_getFacingAnglePtr(Object* o)
{
	return o->facingAnglePtr;
}

/* links the facing angle to a pointer, useful when linking two objects together */	
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

/* Used to link this object to another index */
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

/* Adds delta_x and delta_y to the objects delta x and y*/
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