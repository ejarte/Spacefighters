#pragma once

#include "libraries.h"
#include "definition.h"
#include "animation.h"
#include "sprite.h"

int objHead;
int objTail;
int objIndex_size;
struct Object object[MAX_NUM_OBJ];

void object_init();	// Initializes the object index
int object_index();
void  object_deindex(int index);

void object_setup(struct Object* o, int index, int type, int x, int y, int w, int h, double facingAng, double facingImgOffset, struct Sprite *s, struct Animation *a);
void object_render(SDL_Renderer* renderer, struct Object* o);
void object_tick(struct Object* o);
void object_move(struct Object* o);

bool object_isMoving(struct Object* o);
// Facing

void object_setFacingToPoint(struct Object* o, SDL_Point p);

// Speed
void object_accelerateSpeedX(struct Object* o);
void object_accelerateSpeedY(struct Object* o);
void object_deaccelerateSpeedX(struct Object* o);
void object_deaccelerateSpeedY(struct Object* o);

// Collision
void object_setCollisionBox(struct Object* o, int w, int h);
void object_setCollisionCircle(struct Object* o, int r);
bool object_instersection(struct Object* o1, struct Object* o2);

/*
typedef struct Object_type Object;

#define MAX_OBJECTS 1000
#define HP_DEAD				0	// NOT IMPLEMENTED
#define HP_INVULNERABLE		-1	// NOT IMPLEMENTED

int tot_created_obj;

Object* object[MAX_OBJECTS];

Object* createObject(int type, int x, int y, int w, int h, double facingAngle, double facingOffset, Sprite *s, Animation *a);

void destroyObject(Object* o);

// Dimensions

int object_getWidth(Object *o);
int object_getHeight(Object* o);

// Position

void object_setPos(Object *o, int x, int y);

void object_setX(Object* o, int x);

void object_setY(Object* o, int y);

int object_getX(Object *o);

int object_getY(Object *o);

 //Returns a pointer to the center position, useful for linking one point to this object. 
SDL_Point* object_getPosPtr(Object* o);

 //links the center point to another pointer useful for attaching this object onto another 
void object_setPosPtr(Object* o, SDL_Point* p);

// Facing Angle


// Facing Angle \\

void object_addFacingAngle(Object *o, double angle);


void object_setFacingAngle(Object *o, double angle);

double object_getFacingAngle(Object *o);

/* Returns a pointer to the facing angle useful for linking one point to this object. 
double* object_getFacingAnglePtr(Object* o);

/* links the facing angle to a pointer, useful when linking two objects together 
void object_setFacingAnglePtr(Object* o, double* p);

// Status

void object_setLife(Object* o, double life);
double object_getLife(Object* o);
void object_addLife(Object* o, double life);

// Collision

void object_setCollisionBoxDimension(Object* o, int w, int h, int x_offset, int y_offset);

void object_setCollisionCircleDiameter(Object* o, int d, int x_offset, int y_offset);

bool object_checkForCollision(Object* o1, Object* o2);


void object_disableCollision(Object* o);

void object_enableCollision(Object* o);

Collision* object_getCollision(Object* o);

// Update

void object_tick(Object* o);

void object_render(SDL_Renderer* renderer, Object *o, bool debugCollision);

void object_setMass(Object* o, double mass);
double object_getMass(Object* o);
void object_calculateCollisionSpeed(Object* o1, Object *o2);

// Delta X & Y

// Ska vi anv�nda oss av vektorer ist�llet?

void object_setDeltaX(Object *o, int delta);

void object_setDeltaY(Object *o, int delta);

int object_getDeltaX(Object *o);

int object_getDeltaY(Object *o);

void object_clearDeltaXY(Object *o);

// View

void object_setSprite(Object *o, Sprite *s);

void object_setAnimation(Object *o, Animation* a, bool activeAnimation);

Animation* object_getAnimation(Object *o);

void object_pauseAnimation(Object *o);

void object_resumeAnimation(Object *o);

void object_show(Object *o);

void object_hide(Object *o);

// Identification 

int object_getTypeId(Object *o);

int object_getObjId(Object *o);

void object_setCustomId(Object* o, int id);

int object_getCustomId(Object *o);

// Debug
void object_print(Object *o);

// Object Index
void objectIndex_flagEnabled(bool flag);

void initObjectIndex();

int indexObject();

void deindexObject(Object *o);

void objectIndex_deindexInt(int index);

void objectIndex_print();

int getObjectIndexMax();

*/