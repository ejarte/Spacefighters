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

void generateRandomSpeed(int *p_dx, int* p_dy, int side)
{
	int rdm;
	*p_dx = *p_dy = 0;
	while (*p_dx == 0 && *p_dy == 0) {
		*p_dx = rand() % TOP_SPEED_XY;
		if (rand() % 2 == 0)
			*p_dx *= -1;
		*p_dy = rand() % TOP_SPEED_XY;
		if (rand() % 2 == 0)
			*p_dy *= -1;
	}
}

void spawnNormalProjectile(Spaceship* source)
{
	double angle;
	int x, y, projSpeed;
	SDL_Point pSource = spaceship_getPosition(source);

	projSpeed = 12;												
	angle = angleBetweenPointsRad(pSource, getMousePos());
	x = (double) projSpeed * cos(angle);					
	y = (double) projSpeed * sin(angle);	


	// Create Object
	Object* lastCreatedObj = createObject(OBJ_TYPE_PROJECTILE, pSource.x, pSource.y, sprite_getFrameWidth(spr_asteroid_gray) / 10, sprite_getFrameHeight(spr_asteroid_gray) / 10, 0, 0, spr_asteroid_gray, asteroid_anim[rand() % 8]);
	object_setDeltaX(lastCreatedObj, x);
	object_setDeltaY(lastCreatedObj, y);
	object_setCollisionCircleDiameter(lastCreatedObj, 5, 0, 0);
	// Create projectile data
	//createProjectile(lastCreatedObj, source, 1);
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
	rdmPoint.x = rand() % (screen_w - 2*k);			// A random point on the world
	rdmPoint.y = rand() % (screen_h - 2*k);
	targetAngle = angleBetweenPointsRad(spawnPoint, rdmPoint);	// Angle between spawn point and random point
	dx = (double)speed * cos(targetAngle);	// velocity vector
	dy = (double)speed * sin(targetAngle);

	Object* lastCreatedObj = createObject(OBJ_TYPE_ASTEROID, spawnPoint.x, spawnPoint.y, sprite_getFrameWidth(spr_asteroid_gray) / 4, sprite_getFrameHeight(spr_asteroid_gray) / 4, 0, 0, spr_asteroid_gray, asteroid_anim[rand() % 8]);
	object_setDeltaX(lastCreatedObj, dx);
	object_setDeltaY(lastCreatedObj, dy);
	object_setCollisionCircleDiameter(lastCreatedObj, 22, 0, 0);
}

bool isInsideWorld(Object* o)
{
	int w = object_getWidth(o)/2;
	int h = object_getHeight(o)/2;
	int x = object_getX(o);
	int y = object_getY(o);
	int topX = x - w;
	int topY = y - h;
	int botX = x + w;
	int botY = y + h;
	return (topX > 0 && topY > 0 && botX < getWindowWidth() && botY < getWindowHeight());
}