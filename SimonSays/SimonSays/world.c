/*	Author(s): Tiago Redaelli
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

/*
SDL_Point mouse = getMousePos();
SDL_Point player;
// lägg in funktionalitet fär att hämta x och y direkt från spaceship_
tempObj = spaceship_getBody(spaceship[0]);
player.x = object_getX(tempObj);
player.y = object_getY(tempObj);

//int spaceship_getX(Spaceship* s);
//int spaceship_getY(Spaceship* s);
int bulletSpeed = 15;
double distance = distanceBetweenPoints(mouse, player);
double dx = (double) (mouse.x - player.x)/distance;
double dy = (double) (mouse.y - player.y)/distance;
dx *= bulletSpeed;
dy *= bulletSpeed;

printf("%d %d\n", dx, dy);
tempObj = createObject(OBJ_TYPE_PROJECTILE, player.x, player.y, sprite_getFrameWidth(sprite[5]) / 10, sprite_getFrameHeight(sprite[5]) / 10, 0, 0, sprite[5], animation[9]);
object_setDeltaX(tempObj, dx);
object_setDeltaY(tempObj, dy);
object_setCollisionCircleDiameter(tempObj, 5, 0, 0);
*/

double radiansTodegrees(double radians)
{
	double degrees;
	return radians * 180 / M_PI;
}

double degreesToRadians(double degree)
{
	double radians;
	return degree * (M_PI / 180);
}

double xyToAngle(double dx, double dy)
{
	double tmp, hyp, a, b, angle;

	a = (int)sqrt(dx*dx); //x-axel
	b = (int)sqrt(dy*dy); //y-axel

	angle = atan2(b, a); // funkar för klockan 3-6
	if (dx > 0 && dy < 0) //klockan 6-9 - behöver ta reda på skillnaden mellan angle och 90 grader. Dubbla den vinkeln och lägg på angle.
	{
		angle = atan2(b, a);
		tmp = radiansTodegrees(angle);
		tmp = 90 - tmp;
		tmp = tmp * 2;
		angle = degreesToRadians(tmp) + angle;
	}
	else if (dx > 0 && dy > 0) //klockan 9-12 - Ta vinkeln - 180 grader
	{
		tmp = radiansTodegrees(angle);
		tmp = tmp + 180;
		angle = degreesToRadians(tmp);
	}

	else if (dx < 0 && dy > 0) //klockan 12-3 - Samma som klockan 3-6 fast 0 grader som riktlinje
	{
		tmp = radiansTodegrees(angle);
		angle = angle - degreesToRadians(tmp * 2);
	}

	return angle;
}

void spawnNormalProjectile(Spaceship* source)
{
	int dx, dy, a, b, c, distance, x, y;
	double angle;

	SDL_Point pSource;
	SDL_Point pMouse = getMousePos();
	pSource.x = spaceship_getX(source);
	pSource.y = spaceship_getY(source);
	double projectileSpeed = 15;

	dx = pSource.x - pMouse.x;
	dy = pSource.y - pMouse.y;

	angle = xyToAngle(dx, dy);

	distance = 4; //hastigheten på skotten

	x = (double) distance * cos(angle);
	y = (double)distance * sin(angle);

	/*
	
	    local real x = GetLocationX(source) + dist * Cos(angle * bj_DEGTORAD)
    local real y = GetLocationY(source) + dist * Sin(angle * bj_DEGTORAD)
	*/

	/*
	
	b[i].directionX = b1 - b[i].x;
	b[i].directionY = b2 - b[i].y;

	b[i].vector_unitX = (b[i].directionX) / b[i].v_length;
	b[i].vector_unitY = (b[i].directionY) / b[i].v_length;
	*/

	//dx = (double) dx/ (double) distance*projectileSpeed;
	//dy = (double) dx/ (double) distance*projectileSpeed;

	//printf("%d %d\n", dx, dy);
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