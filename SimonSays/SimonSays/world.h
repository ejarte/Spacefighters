#pragma once

#include "libraries.h"
#include "definition.h"
#include "object.h"

void world_init();
void world_spawnExplosionEffect(int x, int y, int w, int h);
void world_spawnAsteroidExplosion(int x, int y);
void spawnNormalProjectile(struct Object* source, int color);
void spawnShotgunProjectiles(struct Object* source, int color);
void spawnMineProjectiles(struct Object* source, int color);
void world_spawnEnteringAsteroid();
void world_spawnSpaceship(struct Player* p, int x, int y, double facingAng);
bool hasLeftWorld(struct Object* o);
bool isInsideWorld(struct Object* o, int *side);
bool world_spaceshipLost(struct Object* spaceship);
void spawnPowerUpType(int type);
void world_createParticleExplosionAngled(int x, int y, double angleCenter, int color);
void world_createParticleFlightPath(int color, int x, int y, int dx, int dy);