#pragma once

#include "libraries.h"
#include "object.h"
typedef struct Spaceship_type Spaceship;

Spaceship *createSpaceship();
void spaceship_setBody(Spaceship *s, Object* body);
Object *spaceship_getBody(Spaceship *s);