#pragma once

#include "libraries.h"
#include "definition.h"
#include "object.h"

void world_init();
void world_spawnEnteringAsteroid();
void world_spawnSpaceship(struct Player* p, int x, int y, double facingAng);
bool hasLeftWorld(struct Object* o);
bool isInsideWorld(struct Player* p, int *side);
bool world_spaceshipLost(struct Player* p);

/*

bool isInsideWorld(Object* o);
void initWorld();
void spawnEnteringAsteroid();
void spawnNormalProjectile(Spaceship* source);
void spawnProjectileSpecial_1(Spaceship* source);

*/