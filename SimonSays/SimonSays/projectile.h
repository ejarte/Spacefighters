#pragma once
#include "libraries.h"
#include "object.h"
#include "spaceship.h"

typedef struct Projectile_type Projectile;

Projectile* projectile[MAX_OBJECTS];

Projectile* createProjectile(Object* o, Spaceship* source, double damage);

void destroyProjectile(Projectile *p);

bool projectile_objectIsSource(Object* proj_obj, Object* other_obj);


double projectile_getDamage(Projectile *p);
