#pragma once

#include "libraries.h"
#include "animation.h"
#include "sprite.h"


typedef struct Object_type Object;

Object* createObject(int type, int x, int y, int w, int h, double facingAngle, Sprite **s, Animation *a, bool show, bool collision);
void destroyObject(Object *o);
void object_setSprite(Object *o, Sprite **s);
void object_setAnimation(Object *o, Animation* a, bool playAnimation);
void object_pauseAnimation(Object *o);
void object_resumeAnimation(Object *o);
void object_tickAnimation(Object *o);
void object_render(SDL_Renderer* renderer, Object *o);
void object_addToFacingAngle(Object *o, double angle);
void object_setFacingAngle(Object *o, double angle);
double object_getFacingAngle(Object *o);
void object_setPosX(Object *o, int x);
void object_setPosY(Object *o, int y);
int object_getPosX(Object *o);
int object_getPosY(Object *o);
void object_setWidth(Object *o, int w);
void object_setHeight(Object *o, int h);
int object_getWidth(Object *o);
int object_getHeight(Object *o);
void object_setScale(Object *o, float scale);
float object_getScale(Object *o);
void object_show(Object *o);
void object_hide(Object *o);
bool object_isShown(Object *o);
void object_setType(Object *o, int type);
int object_getType(Object *o);
void object_setIndex(Object *o, int index);
int object_getIndex(Object *o);
bool object_hasCollision(Object *o);
bool object_setCollision(Object *o, bool flag);
bool object_checkForBoxCollision(Object* o1, Object* o2);
