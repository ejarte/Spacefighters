/*	Author(s): Tiago Redaelli, Jacob Ekedahl
	Last modified: 2017-04-25
	
	To-do:
	1) Adding collision to asteroids
	2) Adding hitpoints to asteroids
	3) Adding item drops to asteroids
	4) Generating dx and dy based on angle
	5) Add a weight variable to vary likelyhood of lower/higher speeds
*/

#include "world.h"
#include "graphics.h"
#include "object.h"
#include "animation.h"
#include "sprite.h"
#include "events.h"
#include "spaceship.h"
#include "projectile.h"

#define LEFT			0
#define RIGHT			1
#define TOP				2
#define BOT				3
#define MIN_SPEED_XY	1
#define TOP_SPEED_XY	6
#define MIN_SCALE		1
#define MAX_SCALE		5
#define ASTEROID_MASS	5

Sprite* spr_asteroid_gray;
Animation* asteroid_anim[12];

void initWorld()
{
	// Sprite
	spr_asteroid_gray = createSprite(renderer, "images/asteroid_01.png", 8, 8, createColor(0, 0, 0, 0));

	// Animation
	for (int r = 0; r < 8; r++) {
		asteroid_anim[r] = createAnimation(8, 7);			// Creates an asteroid with 8 frames and a frame time of 7
		for (int c = 0; c < 8; c++) {
			anim_addFrameColRow(asteroid_anim[r], c, r);	// adds columns 0 to 7 to at a given row the last created animation 
		}
	}
}

void spawnProjectile(Spaceship* source, int x, int y, int projSpeed, double angle)
{
	Object* lastCreatedObj = createObject(OBJ_TYPE_PROJECTILE, x, y, sprite_getFrameWidth(spr_asteroid_gray) / 10, sprite_getFrameHeight(spr_asteroid_gray) / 10, 0, 0, spr_asteroid_gray, asteroid_anim[rand() % 8]);
	x = (double)projSpeed * cos(angle);
	y = (double)projSpeed * sin(angle);
	object_setDeltaX(lastCreatedObj, x);
	object_setDeltaY(lastCreatedObj, y);
	object_setCollisionCircleDiameter(lastCreatedObj, 5, 0, 0);
	// Create projectile data
	createProjectile(lastCreatedObj, source, 1);
}

void spawnNormalProjectile(Spaceship* source)
{
	// SDL_Point getPolarProjectionPoint(SDL_Point source, double distance, double angle_rad);
	double angle;
	int x, y, projSpeed;
	SDL_Point pSource = spaceship_getPosition(source);
	projSpeed = 12;												
	angle = angleBetweenPointsRad(pSource, getMousePos());
	x = (double) projSpeed * cos(angle);					
	y = (double) projSpeed * sin(angle);	
	//double facing = object_getFacingAngle(spaceship_getBody(source));
	//pSource = getPolarProjectionPoint(pSource, 100, degreesToRadians(facing));
	spawnProjectile(source, pSource.x, pSource.y, projSpeed, angle);
}

// NEED FIX 

void spawnProjectileSpecial_1(Spaceship* source)
{
	SDL_Point p;
	Object* o = spaceship_getBody(source);
	int x = object_getDeltaX(o);
	int y = object_getDeltaY(o);
	//double angle = pointToAngle(x, y);
	double angle = object_getFacingAngle(spaceship_getBody(source));
	int projSpeed = 12;
	p.x = object_getX(o);
	p.y = object_getY(o);

	for (int i = 0; i < 4; i++) {
		spawnProjectile(source, p.x, p.y, projSpeed, (angle + M_PI/4) + M_PI / 2 * i);
	}
}

// Remoev later
void spawnAteroidTest()
{
	printf("Möte\n");

	SDL_Point p1 = { 200, 350 };
	SDL_Point p2 = { 800, 350 };
	Object* lastCreatedObj;

	lastCreatedObj = createObject(OBJ_TYPE_ASTEROID, p1.x, p1.y, sprite_getFrameWidth(spr_asteroid_gray) / 4, sprite_getFrameHeight(spr_asteroid_gray) / 4, 0, 0, spr_asteroid_gray, asteroid_anim[rand() % 8]);
	object_setDeltaX(lastCreatedObj, 2);
	object_setDeltaY(lastCreatedObj, 0);
	object_setCollisionCircleDiameter(lastCreatedObj, 22, 0, 0);
	object_setMass(lastCreatedObj, 10); //massa på asteroid1

	lastCreatedObj = createObject(OBJ_TYPE_ASTEROID, p2.x, p2.y, sprite_getFrameWidth(spr_asteroid_gray) / 4, sprite_getFrameHeight(spr_asteroid_gray) / 4, 0, 0, spr_asteroid_gray, asteroid_anim[rand() % 8]);
	object_setDeltaX(lastCreatedObj, -4);
	object_setDeltaY(lastCreatedObj, 0);
	object_setCollisionCircleDiameter(lastCreatedObj, 22, 0, 0);
	object_setMass(lastCreatedObj, 20);
}

void spawnEnteringAsteroid()
{
	int side, dx, dy, screen_w, screen_h, speed, k;
	double facingAngle, scale, targetAngle;
	SDL_Point rdmPoint;
	SDL_Point spawnPoint;

	side = rand() % 4;
	facingAngle = rand() % 360;
	scale = rand() % MAX_SCALE + MIN_SCALE;
	screen_w = getWindowWidth();
	screen_h = getWindowHeight();

	// distance from/to world edge
	// used to spawn the asteroid outside the world
	k = 100; 

	// Asteroid spawn coordinates
	if (side == LEFT) {
		spawnPoint.x = 0 - k/2;
		spawnPoint.y = k + rand() % screen_h;
	}
	else if (side == RIGHT) {
		spawnPoint.x = screen_w + k/2;
		spawnPoint.y = k + rand() % screen_h;
	}
	else if (side == TOP) {
		spawnPoint.x = k + rand() % screen_w;
		spawnPoint.y = 0 - k/2;
	}
	else if (side == BOT) {
		spawnPoint.x = k + rand() % screen_w;
		spawnPoint.y = screen_h + k/2;
	}

	speed = rand() % TOP_SPEED_XY + MIN_SPEED_XY;	
	rdmPoint.x = rand() % (screen_w - 2*k);						// A random point on the world
	rdmPoint.y = rand() % (screen_h - 2*k);
	targetAngle = angleBetweenPointsRad(spawnPoint, rdmPoint);	// Angle between spawn point and random point
	dx = (double)speed * cos(targetAngle);						// velocity vector
	dy = (double)speed * sin(targetAngle);

	Object* lastCreatedObj = createObject(OBJ_TYPE_ASTEROID, spawnPoint.x, spawnPoint.y, sprite_getFrameWidth(spr_asteroid_gray) / 4, sprite_getFrameHeight(spr_asteroid_gray) / 4, 0, 0, spr_asteroid_gray, asteroid_anim[rand() % 8]);
	object_setDeltaX(lastCreatedObj, dx);
	object_setDeltaY(lastCreatedObj, dy);
	object_setCollisionCircleDiameter(lastCreatedObj, 22, 0, 0);
	object_setMass(lastCreatedObj, 5);
}

/* Used by mostly spaceship to detect when it is trying to leave */
bool isInsideWorld(Object* o)
{
	int w = object_getWidth(o)/2;
	int h = object_getHeight(o)/2;
	int x = object_getX(o);
	int y = object_getY(o);
	int window_w = getWindowWidth();
	int window_h = getWindowHeight();
	int topX = x - w;
	int topY = y - h;
	int botX = x + w;
	int botY = y + h;
	return (topX > 0 && topY > 0 && botX < window_w && botY < window_h);
}

/* Used by misc objects to detect when they have guaranteedly left the world*/
bool hasLeftWorld(Object* o) 
{
	int w = object_getWidth(o) / 2;
	int h = object_getHeight(o) / 2;
	int x = object_getX(o);
	int y = object_getY(o);
	int topX = x - w;
	int topY = y - h;
	int botX = x + w;
	int botY = y + h;
	return (topX < - 100 || topY < - 100 || botX > getWindowWidth() + 100 || botY > getWindowHeight() + 100);
}