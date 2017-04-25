#pragma once
#include "libraries.h"
#include "object.h"
#include "spaceship.h"

typedef struct Projectile_type Projectile;

Projectile* projectile[MAX_OBJECTS];

Projectile* createProjectile(Object* o, Spaceship* source, int damage);

void destroyProjectile(Projectile *p);

bool projectile_isSource(Object* proj_obj, Object* other_obj);