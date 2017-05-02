#pragma once

#include "libraries.h"
#include "definition.h"
#include "object.h"

void world_init();
void world_spawnEnteringAsteroid();
bool hasLeftWorld(struct Object* o);



/*

bool isInsideWorld(Object* o);
void initWorld();
void spawnEnteringAsteroid();
void spawnNormalProjectile(Spaceship* source);
void spawnProjectileSpecial_1(Spaceship* source);

*/