#pragma once

#include "libraries.h"
#include "object.h"
#include "spaceship.h"

// Object Types existing in the world
#define OBJ_TYPE_GREENWIND			1
#define OBJ_TYPE_SPACESHIP			2
#define OBJ_TYPE_EXPLOSION			3
#define OBJ_TYPE_BLACKHOLE			4
#define OBJ_TYPE_ASTEROID			5
#define OBJ_TYPE_ITEM_HEALTH		6
#define OBJ_TYPE_ITEM_INVUL			7
#define OBJ_TYPE_ITEM_SPEED			8
#define OBJ_TYPE_PROJECTILE			9

#define WORLD_LEFT					0
#define WORLD_RIGHT					1
#define WORLD_TOP					2
#define WORLD_BOT					3

bool isInsideWorld(Object* o);
bool hasLeftWorld(Object* o);
void initWorld();
void spawnEnteringAsteroid();
void spawnNormalProjectile(Spaceship* source);