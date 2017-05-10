/*	Author(s):	Tiago Redaelli, Jacob Ekedahl
	
	File contains API to check if a object is inside world bounds, and creation of various objects and effects into the world.
*/

#include "world.h"
#include "events.h"
#include "graphics.h"

#define AST_MAX_SCALE		5		// Asteroid max scale
#define AST_MIN_SCALE		1		// Asteroid min scale
#define AST_TOP_SPEED_XY	6		// Asteroid max projection speed
#define AST_MIN_SPEED_XY	2		// Asteroid min projection speed

struct Sprite spr_asteroid_gray;			
struct Sprite spr_spaceship_1[4];
struct Sprite spr_powerup_speed;
struct Sprite spr_powerup_hp;
struct Sprite spr_powerup_atk_2;
struct Sprite spr_powerup_atk_3;
struct Sprite spr_explosion_1;
struct Sprite spr_fire;
struct Sprite spr_proj_1[4];
struct Sprite spr_mine[4];
struct Sprite spr_particle[5];
struct Sprite spr_respawn;

struct Animation anim_explosion_1;
struct Animation anim_asteroid_gray[8];
struct Animation anim_spaceship[4];
struct Animation anim_none;
struct Animation anim_mine;
struct Animation anim_respawn;

void world_init()
{
	sprite_setup(&spr_spaceship_1[0], renderer, "images/spaceships/playerShip1_red.png", 1, 1, createColor(0, 0, 0, 0));
	sprite_setup(&spr_spaceship_1[1], renderer, "images/spaceships/playerShip1_blue.png", 1, 1, createColor(0, 0, 0, 0));
	sprite_setup(&spr_spaceship_1[2], renderer, "images/spaceships/playerShip1_green.png", 1, 1, createColor(0, 0, 0, 0));
	sprite_setup(&spr_spaceship_1[3], renderer, "images/spaceships/playerShip1_orange.png", 1, 1, createColor(0, 0, 0, 0));
	sprite_setup(&spr_asteroid_gray, renderer, "images/asteroid_01.png", 8, 8, createColor(0, 0, 0, 0));

	sprite_setup(&spr_powerup_speed, renderer, "images/power-ups/powerupRed_bolt.png", 1, 1, createColor(0, 0, 0, 0));
	sprite_setup(&spr_powerup_hp, renderer, "images/power-ups/pill_green.png", 1, 1, createColor(0, 0, 0, 0));
	sprite_setup(&spr_powerup_atk_2, renderer, "images/power-ups/things_silver.png", 1, 1, createColor(0, 0, 0, 0));
	sprite_setup(&spr_powerup_atk_3, renderer, "images/power-ups/things_gold.png", 1, 1, createColor(0, 0, 0, 0));
	sprite_setup(&spr_explosion_1, renderer, "images/skybusterexplosion.png", 4, 5, createColor(0, 0, 0, 0));

	sprite_setup(&spr_mine[0], renderer, "images/projectiles/mine_red.bmp", 2, 1, createColor(0, 0, 0, 0));
	sprite_setup(&spr_mine[1], renderer, "images/projectiles/mine_blue.bmp", 2, 1, createColor(0, 0, 0, 0));
	sprite_setup(&spr_mine[2], renderer, "images/projectiles/mine_green.bmp", 2, 1, createColor(0, 0, 0, 0));
	sprite_setup(&spr_mine[3], renderer, "images/projectiles/mine_orange.bmp", 2, 1, createColor(0, 0, 0, 0));
	sprite_setup(&spr_proj_1[0], renderer, "images/projectiles/proj_red.bmp", 1, 1, createColor(0, 0, 0, 0));
	sprite_setup(&spr_proj_1[1], renderer, "images/projectiles/proj_blue.bmp", 1, 1, createColor(0, 0, 0, 0));
	sprite_setup(&spr_proj_1[2], renderer, "images/projectiles/proj_green.bmp", 1, 1, createColor(0, 0, 0, 0));
	sprite_setup(&spr_proj_1[3], renderer, "images/projectiles/proj_yellow.bmp", 1, 1, createColor(0, 0, 0, 0));
	sprite_setup(&spr_fire, renderer, "images/projectiles/fire_ship.bmp", 1, 1, createColor(0, 0, 0, 0));
	//sprite_setup(&spr_respawn, renderer, "images/respawn.png", 5, 2, createColor(0, 0, 0, 0));
	

	sprite_setup(&spr_particle[0], renderer, "images/particles/red.bmp", 1, 1, createColor(0, 0, 0, 0));
	sprite_setup(&spr_particle[1], renderer, "images/particles/blue.bmp", 1, 1, createColor(0, 0, 0, 0));
	sprite_setup(&spr_particle[2], renderer, "images/particles/green.bmp", 1, 1, createColor(0, 0, 0, 0));
	sprite_setup(&spr_particle[3], renderer, "images/particles/orange.bmp", 1, 1, createColor(0, 0, 0, 0));
	sprite_setup(&spr_particle[4], renderer, "images/particles/gray.bmp", 1, 1, createColor(0, 0, 0, 0));

	// Explosion animation
	animation_setup(&anim_explosion_1, 4, 5, 2);
	for (int r = 0; r < 5; r++) {
		for (int c = 0; c < 4; c++) {
			animation_addFrameColRow(&anim_explosion_1, c, r);
		}
	}

	// Respawn animation
	/*
	animation_setup(&anim_respawn, 5, 2, 2);
	for (int r = 0; r < 2; r++) {
		for (int c = 0; c < 5; c++) {
			animation_addFrameColRow(&anim_explosion_1, c, r);
		}
	}
	*/

	// Blinking mine animation
	animation_setup(&anim_mine, 2, 1, 14);
	for (int r = 0; r < 1; r++) {
		for (int c = 0; c < 2; c++) {
			animation_addFrameColRow(&anim_mine, c, r);
		}
	}



	// Asteroid animation
	for (int r = 0; r < 8; r++) {
		animation_setup(&anim_asteroid_gray[r], 8, 1, 8);
		for (int c = 0; c < 8; c++) {
			animation_addFrameColRow(&anim_asteroid_gray[r], c, r);
		}
	}
	animation_setup(&anim_none, 1, 1, 9999);
	animation_addFrameColRow(&anim_none, 0, 0);
}

void world_spawnExplosionEffect(int x, int y, int w, int h)
{
	double facing = rand() % 360;
	int i = object_index();
	object_setup(&object[i], i, OBJ_TYPE_EFFECT, x, y, w, h, facing, 0, &spr_explosion_1, &anim_explosion_1);
}

void world_spawnAsteroidExplosion(int x, int y)
{
	SDL_Thread* thread;
	double angle, speed;
	int life, size, newX, newY, dx, dy, i;
	for (int i = 0; i < 300; i++) {
		angle = rand() % 360;
		speed = rand() % 6 + 1;
		life = rand() % 60 + 60;
		size = rand() % 2 + 2;
		newX = rand() % 6 - 7 + x;
		newY = rand() % 6 - 7 + y;
		createParticle(newX, newY, size, size, life, angle, speed, sprite_getTexture(&spr_particle[4]));	
	}

	for (int j = 0; j < rand() % 20 + 10; j++) {
		speed = rand() % 5 + 10;
		angle = (double)(rand() % 360)*M_PI / 180;
		dx = (double)speed * cos(angle);						// velocity vector
		dy = (double)speed * sin(angle);
		i = object_index();
		object_setup(&object[i], i, OBJ_TYPE_EFFECT, x, y, spr_asteroid_gray.frame_w / 15, spr_asteroid_gray.frame_h / 15, rand() % 360, 0, &spr_asteroid_gray, &anim_asteroid_gray[rand() % 8]);
		object[i].delta_x = dx;
		object[i].delta_y = dy;
	}
}

void world_spawnSpaceship(struct Player* p, int x, int y, double facingAng)
{
	double facing = 0;
	double facingOff = 0;
	int w = 112 / 3;
	int h = 75 / 3;
	int i = object_index();
	p->alive = true;
	p->mobile = true;
	p->spaceship = &object[i];
	p->speed_active = false;
	object_setup(&object[i], i, OBJ_TYPE_SPACESHIP, x, y, w, h, facing, facingOff, &spr_spaceship_1[p->color], &anim_none);
	object[i].acc = SPEED_ACC_DEFAULT;
	object[i].speed_max = SPEED_MAX_DEFAULT;
	object[i].drag = DRAG_SPACESHIP;
	object[i].hp = LIFE_SPACESHIP;
	object[i].dmg_on_impact = 0;
	p->spaceship = &object[i];
	p->shipIndex = i;
	object_setCollisionBox(&object[i], 25, 25);
}

void world_createParticleExplosionAngled(int x, int y, double angleCenter, int color)
{
	if (color > 4 || color < 0)
		color = 4;	// gray on invalid input

	double angle, speed;
	int life, size, newX, newY;
	for (int i = 0; i < 20; i++) {
		angle = rand() % 25 + angleCenter + 180;
		speed = rand() % 4 + 1;
		life = rand() % 12 + 7;
		size = rand() % 2 + 2;
		newX = rand() % 6 - 4 + x;
		newY = rand() % 6 - 4 + y;
		createParticle(newX, newY, size, size, life, angle, speed, sprite_getTexture(&spr_particle[color]));
	}
	for (int i = 0; i < 30; i++) {
		angle = rand() % 45 + angleCenter + 180;
		speed = rand() % 5 + 5;
		life = rand() % 3 + 5;
		size = rand() % 2 + 2;
		newX = rand() % 6 - 4 + x;
		newY = rand() % 6 - 4 + y;
		createParticle(newX, newY, size, size, life, angle, speed, sprite_getTexture(&spr_particle[color]));
	}
}

void world_createParticleFlightPath(int color, int x, int y, int dx, int dy)
{
	// angle = radiansToDegrees(pointToAngle(dx, dy));
	double angle, speed;
	int life, size, newX, newY, life_k;
	life_k = sqrt(dx*dx + dy*dy);
	for (int i = 0; i < 25; i++) {
		angle = rand() % 10 + radiansToDegrees(pointToAngle(dx, dy)) + 180;
		speed = rand() % 4 + 1;
		life = rand() % 7 + life_k;
		size = rand() % 2 + 2;
		newX = rand() % 6 - 4 + x;
		newY = rand() % 6 - 4 + y;
		createParticle(newX, newY, size, size, life, angle, speed, sprite_getTexture(&spr_fire));
	}
}

void spawnProjectile(struct Object* source, int color, int x, int y, int w, int h, int dx, int dy, int dmg)
{
	int i = object_index();
	if (color == PL_COLOR_RED) {
		object_setup(&object[i], i, OBJ_TYPE_PROJECTILE, x, y, w, h, 0.0, 0.0, &spr_proj_1[0], &anim_none);
	}
	else if (color == PL_COLOR_BLUE) {
		object_setup(&object[i], i, OBJ_TYPE_PROJECTILE, x, y, w, h, 0.0, 0.0, &spr_proj_1[1], &anim_none);
	}
	else if (color == PL_COLOR_GREEN) {
		object_setup(&object[i], i, OBJ_TYPE_PROJECTILE, x, y, w, h, 0.0, 0.0, &spr_proj_1[2], &anim_none);
	}
	else {
		object_setup(&object[i], i, OBJ_TYPE_PROJECTILE, x, y, w, h, 0.0, 0.0, &spr_proj_1[3], &anim_none);
	}
	object[i].source_id = source->id_index;
	object[i].delta_x = dx;
	object[i].delta_y = dy;
	object[i].dmg_on_impact = dmg;
	object_setCollisionCircle(&object[i], 5);
}

void spawnNormalProjectile(struct Object* source, int color)
{
	SDL_Point p = { source->center_x, source->center_y };
	double angle;
	int dx, dy, w, h, projSpeed, i;
	w = spr_proj_1[0].frame_w / 2;
	h = spr_proj_1[0].frame_h / 2;
	projSpeed = 15;
	angle = angleBetweenPointsRad(p, getMousePos());
	dx = (double)projSpeed * cos(angle);
	dy = (double)projSpeed * sin(angle);
	spawnProjectile(source, color, p.x, p.y, w, h, dx, dy, 1);
}

void spawnShotgunProjectiles(struct Object* source, int color)
{
	SDL_Point p = { source->center_x, source->center_y };
	double angle;
	int dx, dy, w, h, projSpeed, i;
	projSpeed = 15;
	w = spr_proj_1[0].frame_w / 2;
	h = spr_proj_1[0].frame_h / 2;
	angle = angleBetweenPointsRad(p, getMousePos()) - 15 * M_PI / 180;
	for (int i = 0; i < 3; i++) {
		dx = (double)projSpeed * cos(angle);
		dy = (double)projSpeed * sin(angle);
		angle += 15 * M_PI / 180;
		spawnProjectile(source, color, p.x, p.y, w, h, dx, dy, 1);
	}
}

void spawnMineProjectiles(struct Object* source, int color)
{
	SDL_Point p = { source->center_x, source->center_y };
	double angle;
	int dx, dy, w, h, projSpeed, i;
	w = spr_mine[0].frame_h;
	h = spr_mine[0].frame_h;
	projSpeed = 4;
	angle = angleBetweenPointsRad(p, getMousePos());
	dx = (double)projSpeed * cos(angle);
	dy = (double)projSpeed * sin(angle);
	i = object_index();
	if (color == PL_COLOR_RED) {
		object_setup(&object[i], i, OBJ_TYPE_PROJECTILE, p.x, p.y, w, h, 0.0, 0.0, &spr_mine[0], &anim_mine);
	}
	else if (color == PL_COLOR_BLUE) {
		object_setup(&object[i], i, OBJ_TYPE_PROJECTILE, p.x, p.y, w, h, 0.0, 0.0, &spr_mine[1], &anim_mine);
	}
	else if (color == PL_COLOR_GREEN) {
		object_setup(&object[i], i, OBJ_TYPE_PROJECTILE, p.x, p.y, w, h, 0.0, 0.0, &spr_mine[2], &anim_mine);
	}
	else {
		object_setup(&object[i], i, OBJ_TYPE_PROJECTILE, p.x, p.y, w, h, 0.0, 0.0, &spr_mine[3], &anim_mine);
	}
	object[i].source_id = source->id_index;
	object[i].delta_x = dx;
	object[i].delta_y = dy;
	object[i].dmg_on_impact = 5;
	object_setCollisionCircle(&object[i], 5);

}

void spawnPowerUpType(int type)
{
	int side, dx, dy, screen_w, screen_h, speed, k, i;
	double facingAngle, scale, targetAngle;
	SDL_Point rdmPoint;
	SDL_Point spawnPoint;
	side = rand() % 4;
	facingAngle = rand() % 360;
	scale = rand() % AST_MAX_SCALE + AST_MIN_SCALE;
	screen_w = getWindowWidth();
	screen_h = getWindowHeight();

	k = 50; // distance from/to world edge, used to spawn the asteroid outside the world
	if (side == WORLD_LEFT) {
		spawnPoint.x = 0 - k / 2;
		spawnPoint.y = k + rand() % screen_h;
	}
	else if (side == WORLD_RIGHT) {
		spawnPoint.x = screen_w + k / 2;
		spawnPoint.y = k + rand() % screen_h;
	}
	else if (side == WORLD_TOP) {
		spawnPoint.x = k + rand() % screen_w;
		spawnPoint.y = 0 - k / 2;
	}
	else if (side == WORLD_BOT) {
		spawnPoint.x = k + rand() % screen_w;
		spawnPoint.y = screen_h + k / 2;
	}
	speed = rand() % AST_TOP_SPEED_XY + AST_MIN_SPEED_XY;
	rdmPoint.x = rand() % (screen_w - 2 * k);						// A random point on the world
	rdmPoint.y = rand() % (screen_h - 2 * k);
	targetAngle = angleBetweenPointsRad(spawnPoint, rdmPoint);	// Angle between spawn point and random point
	dx = (double)speed * cos(targetAngle);						// velocity vector
	dy = (double)speed * sin(targetAngle);
	i = object_index();
	if (type == POWER_SPEED) {
		object_setup(&object[i], i, OBJ_TYPE_POWERUP, spawnPoint.x, spawnPoint.y, spr_powerup_speed.frame_w / 2, spr_powerup_speed.frame_h / 2, rand() % 360, 0, &spr_powerup_speed, &anim_none);
		object[i].power_id = POWER_SPEED;
	}
	else if (type == POWER_ATK_2) {
		object_setup(&object[i], i, OBJ_TYPE_POWERUP, spawnPoint.x, spawnPoint.y, spr_powerup_atk_2.frame_w / 2, spr_powerup_atk_2.frame_h / 2, rand() % 360, 0, &spr_powerup_atk_2, &anim_none);
		object[i].power_id = POWER_ATK_2;
	}
	else if (type == POWER_ATK_3) {
		object_setup(&object[i], i, OBJ_TYPE_POWERUP, spawnPoint.x, spawnPoint.y, spr_powerup_atk_3.frame_w / 2, spr_powerup_atk_3.frame_h / 2, rand() % 360, 0, &spr_powerup_atk_3, &anim_none);
		object[i].power_id = POWER_ATK_3;
	}
	else if (type == POWER_HP) {
		object_setup(&object[i], i, OBJ_TYPE_POWERUP, spawnPoint.x, spawnPoint.y, spr_powerup_hp.frame_w / 2, spr_powerup_hp.frame_h / 2, rand() % 360, 0, &spr_powerup_hp, &anim_none);
		object[i].power_id = POWER_HP;
	}
	object[i].delta_x = dx;
	object[i].delta_y = dy;
	object[i].hp = LIFE_POWERUP;
	object[i].dmg_on_impact = 0;
	object_setCollisionBox(&object[i], 15, 15);
}

void world_spawnEnteringAsteroid()
{
	int side, dx, dy, screen_w, screen_h, speed, k, i;
	double facingAngle, scale, targetAngle;
	SDL_Point rdmPoint;
	SDL_Point spawnPoint;

	side = rand() % 4;
	facingAngle = rand() % 360;
	scale = rand() % AST_MAX_SCALE + AST_MIN_SCALE;
	screen_w = getWindowWidth();
	screen_h = getWindowHeight();

	k = 50; // distance from/to world edge, used to spawn the asteroid outside the world

			// Asteroid spawn coordinates
	if (side == WORLD_LEFT) {
		spawnPoint.x = 0 - k / 2;
		spawnPoint.y = k + rand() % screen_h;
	}
	else if (side == WORLD_RIGHT) {
		spawnPoint.x = screen_w + k / 2;
		spawnPoint.y = k + rand() % screen_h;
	}
	else if (side == WORLD_TOP) {
		spawnPoint.x = k + rand() % screen_w;
		spawnPoint.y = 0 - k / 2;
	}
	else if (side == WORLD_BOT) {
		spawnPoint.x = k + rand() % screen_w;
		spawnPoint.y = screen_h + k / 2;
	}

	speed = rand() % AST_TOP_SPEED_XY + AST_MIN_SPEED_XY;
	rdmPoint.x = rand() % (screen_w - 2 * k);						// A random point on the world
	rdmPoint.y = rand() % (screen_h - 2 * k);
	targetAngle = angleBetweenPointsRad(spawnPoint, rdmPoint);	// Angle between spawn point and random point
	dx = (double)speed * cos(targetAngle);						// velocity vector
	dy = (double)speed * sin(targetAngle);

	i = object_index();
	object_setup(&object[i], i, OBJ_TYPE_ASTEROID, spawnPoint.x, spawnPoint.y, spr_asteroid_gray.frame_w / 4, spr_asteroid_gray.frame_h / 4, rand() % 360, 0, &spr_asteroid_gray, &anim_asteroid_gray[rand() % 8]);
	object[i].delta_x = dx;
	object[i].delta_y = dy;
	object[i].hp = LIFE_ASTEROID;
	object[i].dmg_on_impact = 1;
	object_setCollisionCircle(&object[i], 20, 20);
}

// Used by misc objects to detect when they have guaranteedly left the world
bool hasLeftWorld(struct Object* o)
{
	int topX = o->center_x - o->w / 2;
	int topY = o->center_y - o->h / 2;
	int botX = o->center_x + o->w / 2;
	int botY = o->center_y + o->h / 2;
	return (topX < -100 || topY < -100 || botX > getWindowWidth() + 100 || botY > getWindowHeight() + 100);
}

// Used by mostly spaceship to detect when it is trying to leave 
bool isInsideWorld(struct Object* o, int *side)
{
	int w = o->w / 2;
	int h = o->h / 2;
	int x = o->center_x;
	int y = o->center_y;
	int window_w = getWindowWidth();
	int window_h = getWindowHeight();
	int topX = x - w;
	int topY = y - h;
	int botX = x + w;
	int botY = y + h;
	bool isInside = true;
	isInside = (topX > 0 && topY > 0 && botX < window_w && botY < window_h);
	if (isInside == false)
	{
		if (x > window_w - 30) {
			*side = WORLD_RIGHT;
		}
		else if (x < 30) {
			*side = WORLD_LEFT;
		}
		else if (y > window_h - 40) {
			*side = WORLD_BOT;
		}
		else if (y < 40) {
			*side = WORLD_TOP;
		}
	}
	return isInside;
}

bool world_spaceshipLost(struct Object* spaceship)
{
	int x = spaceship->center_x;
	int y = spaceship->center_y;
	int window_w = getWindowWidth();
	int window_h = getWindowHeight();
	return (x > window_w || x < 0 || y > window_h || y < 0);
}
