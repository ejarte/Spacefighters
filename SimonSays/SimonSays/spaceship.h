#pragma once

#include "libraries.h"
#include "object.h"

typedef struct Spaceship_type Spaceship;


Spaceship *createSpaceship(Object *body);
Spaceship* copySpaceship(Spaceship* srcs, int x, int y, double facing);
void destroySpaceship(Spaceship* s);
void spaceship_setBody(Spaceship *s, Object* body);
Object *spaceship_getBody(Spaceship *s);

// Position

int spaceship_getX(Spaceship* s);
int spaceship_getY(Spaceship* s);

// Facing Angle
void spaceship_setFacingAngle(Spaceship*s, double angle);
void spaceship_setFacingToPoint(Spaceship* s, SDL_Point p);

// Speed
void spaceship_setDrag(Spaceship* s, double drag);
void spaceship_setAcceleration(Spaceship* s, double acc);
void spaceship_setMaxSpeed(Spaceship* s, double max);
void spaceship_setSpeedX(Spaceship* s, double speed);
void spaceship_setSpeedY(Spaceship* s, double speed);
double spaceship_getSpeedX(Spaceship* s);
double spaceship_getSpeedY(Spaceship* s);
void spaceship_accelerateX(Spaceship *s);
void spaceship_accelerateY(Spaceship* s);
void spaceship_deaccelerateX(Spaceship *s);
void spaceship_deaccelerateY(Spaceship *s);
bool spaceship_isMobile(Spaceship* s);
void spaceship_enableMobility(Spaceship *s);
void spaceship_disableMobility(Spaceship *s);

// Actions
void spaceship_onDeath(Spaceship *s);