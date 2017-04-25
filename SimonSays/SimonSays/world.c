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
	int side, dx, dy, x, y, screen_w, screen_h, d;
	double facingAngle, scale;
	Object* lastCreatedObj;

	side = rand() % 4;
	facingAngle = rand() % 360;
	scale = rand() % MAX_SCALE + MIN_SCALE;
	screen_w = getWindowWidth();
	screen_h = getWindowHeight();
	d = 150;

	if (side == LEFT) {
		x = 0 - d/2;
		y = d + rand() % (screen_h - d);
		generateRandomSpeed(&dx, &dy, side);
	}
	else if (side == RIGHT) {
		x = screen_w + d/2;
		y = d + rand() % (screen_h - d);
		generateRandomSpeed(&dx, &dy, side);
	}
	else if (side == TOP) {
		x = d + rand() % (screen_w - d);
		y = 0 - d/2;
		generateRandomSpeed(&dx, &dy, side);
	}
	else if (side == BOT) {
		x = d + rand() % (screen_w - d);
		y = screen_h + d/2;
		generateRandomSpeed(&dx, &dy, side);
	}
	printf("Asteroid entered.\n");
	lastCreatedObj = createObject(OBJ_TYPE_ASTEROID, x, y, sprite_getFrameWidth(spr_asteroid_gray) / 4, sprite_getFrameHeight(spr_asteroid_gray) / 4, 0, 0, spr_asteroid_gray, asteroid_anim[rand() % 8]);
	object_setDeltaX(lastCreatedObj, dx);
	object_setDeltaY(lastCreatedObj, dy);
	object_setCollisionCircleDiameter(lastCreatedObj, 22, 0, 0);
}

bool isInsideWorld(Object* o)
{
	Collision* c = object_getCollision(o);
	SDL_Rect collision_rect = collision_getRect(c);

	printf("COL %d %d\n", collision_rect.x, collision_rect.y);

	return false;
}