#pragma once
/*
#include "libraries.h"
#include "animation.h"
#include "sprite.h"

typedef struct Object_type Object;
#define MAX_OBJECTS 1000
Object* object[MAX_OBJECTS];

Object* createObject(int type, int x, int y, int w, int h, double facingAngle, Sprite *s, Animation *a, bool show, bool collision);
Object* createObjectCopy(Object* srcs, int x, int y, double facing);
void destroyObject(Object *o);
void object_setSprite(Object *o, Sprite *s);
void object_setAnimation(Object *o, Animation* a, bool playAnimation);
void object_pauseAnimation(Object *o);
void object_resumeAnimation(Object *o);
void object_tick(Object *o);
void object_render(SDL_Renderer* renderer, Object *o);
void object_addToFacingAngle(Object *o, double angle);
void object_setFacingAngle(Object *o, double angle);
double object_getFacingAngle(Object *o);

// Position
int* object_getPointerToX(Object *o);
int* object_getPointerToY(Object *o);

void object_setPosX(Object *o, int x);
void object_setPosY(Object *o, int y);
void object_setPosXY(Object *o, int x, int y);
int object_getPosX(Object *o);
int object_getPosY(Object *o);
void object_setWidth(Object *o, int w);
void object_setHeight(Object *o, int h);
int object_getWidth(Object *o);
int object_getHeight(Object *o);
void object_setScale(Object *o, float scale);
double object_getScale(Object *o);
void object_show(Object *o);
void object_hide(Object *o);
bool object_isShown(Object *o);
void object_setType(Object *o, int type);
int object_getType(Object *o);
void object_setIndex(Object *o, int index);
int object_getIndex(Object *o);
void object_print(Object* o);
// Collision
void object_setCollisionBoxDimension(Object* o, int w, int h, int x_offset, int y_offset, bool render);
bool object_hasCollision(Object *o);
void object_enableCollision(Object *o);
void object_disableCollision(Object *o);

bool object_checkForBoxCollision(Object* o1, Object* o2);

//
void objectIndex_flagEnabled(bool flag);
void initObjectIndex();
int indexObject();
void objectIndex_deindexInt(int index);
void objectIndex_print();
int getObjectIndexMax();
*/