#pragma once
#include "logic.h"
#include "libaries.h"

#define NA_MAX_SPEED	6
#define NA_MIN_SPEED	2

struct SpawnOdds spawnOdds_powerup[NUM_OF_POWERS];
struct SpawnOdds spawnOdds_asteroid;

int worldHeight;
int worldWidth;


void setup_spawnOdds(struct SpawnOdds* so, int minAmount, int maxAmount, int minInterval, int maxInterval)
{
	so->minAmount = minAmount;
	so->maxAmount = maxAmount;
	so->minInterval = minInterval;
	so->maxInterval = maxInterval;
}

void set_spawnOddsNextRollTime(struct SpawnOdds* so)
{
	so->timestamp = SDL_GetTicks() + (rand() % (so->maxInterval - so->minInterval) + so->minInterval) * 1000;	// When the next roll will occour
}

void set_worldDimensions(int w, int h)
{
	worldWidth = w;
	worldHeight = h;
	printf("World dimensions set to: %d %d.\n", w, h);
}

int odds_getNum(struct SpawnOdds so)
{
	if (so.minAmount == 1 && so.maxAmount == 1)
		return 1;
	return rand(SDL_GetTicks()) % so.maxAmount + 1;
}

void init_logic()
{
	set_worldDimensions(1280, 720);	// DONT TOUCH THIS! Needs to be the same as the window resolution (screenW, screenH)

	setup_spawnOdds(&spawnOdds_powerup[POWER_SPEED], 1, 1, 7, 20);
	setup_spawnOdds(&spawnOdds_powerup[POWER_ATK_2], 1, 1, 12, 20);
	setup_spawnOdds(&spawnOdds_powerup[POWER_ATK_3], 1, 1, 12, 20);
	setup_spawnOdds(&spawnOdds_powerup[POWER_HP], 1, 1, 5, 20);
	setup_spawnOdds(&spawnOdds_asteroid, 1, 1, 5, 12);
	set_spawnOddsNextRollTime(&spawnOdds_powerup[POWER_SPEED]);
	set_spawnOddsNextRollTime(&spawnOdds_powerup[POWER_ATK_2]);
	set_spawnOddsNextRollTime(&spawnOdds_powerup[POWER_ATK_3]);
	set_spawnOddsNextRollTime(&spawnOdds_powerup[POWER_HP]);
	set_spawnOddsNextRollTime(&spawnOdds_asteroid);
}

double angleBetweenPointsRad(SDL_Point p1, SDL_Point p2)
{
	int dx = p1.x - p2.x;
	int dy = p1.y - p2.y;

	double ax = (int)sqrt(dx*dx);	// side of triangle: x-axis
	double by = (int)sqrt(dy*dy);	// side of triangle: y-axis
	double angle = atan2(by, ax);	// funkar för klockan 3-6

									// Adjuct angle depending on quadrant

	if (dx > 0 && dy < 0) //klockan 6-9 - behöver ta reda på skillnaden mellan angle och 90 grader. Dubbla den vinkeln och lägg på angle.
		return (M_PI / 2 - angle) * 2 + angle;
	else if (dx > 0 && dy > 0) //klockan 9-12 - Ta vinkeln - 180 grader
		return M_PI + angle;
	else if (dx < 0 && dy > 0) //klockan 12-3 - Samma som klockan 3-6 fast 0 grader som riktlinje
		return angle - angle * 2;
	return angle;
}

SDL_Point getRdmSpawnPoint(int side)
{
	int k = 50;
	SDL_Point p;
	if (side == WORLD_LEFT) {
		p.x = 0 - k / 2;
		p.y = k + rand() % worldHeight;
	}
	else if (side == WORLD_RIGHT) {
		p.x = worldWidth + k / 2;
		p.y = k + rand() % worldHeight;
	}
	else if (side == WORLD_TOP) {
		p.x = k + rand() % worldWidth;
		p.y = 0 - k / 2;
	}
	else {
		p.x = k + rand() % worldWidth;
		p.y = worldHeight + k / 2;
	}
	return p;
}

SDL_Point getRdmTarget()
{
	int k = 50;
	SDL_Point p;
	p.x = rand(SDL_GetTicks()) % (worldWidth - 2 * k);
	p.y = rand(SDL_GetTicks()) % (worldHeight - 2 * k);
	return p;
}


SDL_Point getRdmVelocityVector(SDL_Point p1, SDL_Point p2, int min, int max)
{
	SDL_Point vel;
	int speed = rand(SDL_GetTicks()) % max + min;
	double angle = angleBetweenPointsRad(p1, p2);
	vel.x = (double)speed * cos(angle);
	vel.y = (double)speed * sin(angle);
	return vel;
}

int getRdmSide()
{
	return rand(SDL_GetTicks()) % 4;
}

int getRdmFacing()
{
	return rand(SDL_GetTicks()) % 360;
}

void TCP_broadcastCreatedNeutralObject(int obj_type, SDL_Point spawn, SDL_Point velocity, int facing)
{
	char data[100];
	s.tcp_buffer[0] = '\0';
	strcpy(s.tcp_buffer, MSG_NEUTRAL_OBJ);
	sprintf(data, "%d %d %d %d %d %d", obj_type, spawn.x, spawn.y, velocity.x, velocity.y, facing);
	strcat(s.tcp_buffer, data);
	s.tcp_len = strlen(s.tcp_buffer) + 1;
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (c[i].tcp_socket_is_free == false) {
			if (SDLNet_TCP_Send(c[i].tcp_socket, (void *)s.tcp_buffer, s.tcp_len) < s.tcp_len) {
				printf("Failed to send neutral object creation: %s\n", SDLNet_GetError());
			}
		}
	}
}

void generateNeutralObjects()
{
	SDL_Point spawn, target, velocity;
	int max, side, dx, dy, facing;

	int curTime = SDL_GetTicks();

	if (spawnOdds_powerup[POWER_SPEED].timestamp <= curTime) {
		set_spawnOddsNextRollTime(&spawnOdds_powerup[POWER_SPEED]);
		max = odds_getNum(spawnOdds_powerup[POWER_SPEED]);

		for (int i = 0; i < max; i++) {
			side = getRdmSide();
			spawn = getRdmSpawnPoint(side);
			target = getRdmTarget();
			velocity = getRdmVelocityVector(spawn, target, NA_MIN_SPEED, NA_MAX_SPEED);
			facing = getRdmFacing();
			printf("Spawned: SPEED at side %d, pos(%d,%d), velocity (%d,%d), facing %d\n", side, spawn.x, spawn.y, velocity.x, velocity.y, facing);
			TCP_broadcastCreatedNeutralObject(POWER_SPEED, spawn, velocity, facing);
		}
	}
	if (spawnOdds_powerup[POWER_ATK_2].timestamp <= curTime) {
		set_spawnOddsNextRollTime(&spawnOdds_powerup[POWER_ATK_2]);
		max = odds_getNum(spawnOdds_powerup[POWER_ATK_2]);
		for (int i = 0; i < max; i++) {
			side = getRdmSide();
			spawn = getRdmSpawnPoint(side);
			target = getRdmTarget();
			velocity = getRdmVelocityVector(spawn, target, NA_MIN_SPEED, NA_MAX_SPEED);
			facing = getRdmFacing();
			printf("Spawned: POWER_ATK_2 at side %d, pos(%d,%d), velocity (%d,%d), facing %d\n", side, spawn.x, spawn.y, velocity.x, velocity.y, facing);
			TCP_broadcastCreatedNeutralObject(POWER_ATK_2, spawn, velocity, facing);
		}
	}
	if (spawnOdds_powerup[POWER_ATK_3].timestamp <= curTime) {
		set_spawnOddsNextRollTime(&spawnOdds_powerup[POWER_ATK_3]);
		max = odds_getNum(spawnOdds_powerup[POWER_ATK_3]);
		for (int i = 0; i < max; i++) {
			side = getRdmSide();
			spawn = getRdmSpawnPoint(side);
			target = getRdmTarget();
			velocity = getRdmVelocityVector(spawn, target, NA_MIN_SPEED, NA_MAX_SPEED);
			facing = getRdmFacing();
			printf("Spawned: POWER_ATK_3 at side %d, pos(%d,%d), velocity (%d,%d), facing %d\n", side, spawn.x, spawn.y, velocity.x, velocity.y, facing);
			TCP_broadcastCreatedNeutralObject(POWER_ATK_3, spawn, velocity, facing);
		}
	}
	if (spawnOdds_powerup[POWER_HP].timestamp <= curTime) {
		set_spawnOddsNextRollTime(&spawnOdds_powerup[POWER_HP]);
		max = odds_getNum(spawnOdds_powerup[POWER_HP]);
		for (int i = 0; i < max; i++) {
			side = getRdmSide();
			spawn = getRdmSpawnPoint(side);
			target = getRdmTarget();
			velocity = getRdmVelocityVector(spawn, target, NA_MIN_SPEED, NA_MAX_SPEED);
			facing = getRdmFacing();
			printf("Spawned: POWER_HP at side %d, pos(%d,%d), velocity (%d,%d), facing %d\n", side, spawn.x, spawn.y, velocity.x, velocity.y, facing);
			TCP_broadcastCreatedNeutralObject(POWER_HP, spawn, velocity, facing);
		}
	}
	if (spawnOdds_asteroid.timestamp <= curTime) {
		set_spawnOddsNextRollTime(&spawnOdds_asteroid);
		max = odds_getNum(spawnOdds_asteroid);
		for (int i = 0; i < max; i++) {
			side = getRdmSide();
			spawn = getRdmSpawnPoint(side);
			target = getRdmTarget();
			velocity = getRdmVelocityVector(spawn, target, NA_MIN_SPEED, NA_MAX_SPEED);
			facing = getRdmFacing();
			printf("Spawned: ASTEROID at side %d, pos(%d,%d), velocity (%d,%d), facing %d\n", side, spawn.x, spawn.y, velocity.x, velocity.y, facing);
			TCP_broadcastCreatedNeutralObject(ASTEROID, spawn, velocity, facing);
		}
	}
}
