#pragma once
#include "libaries.h"
#include "definitions.h"

struct SpawnOdds {
	int timestamp;		// timestamp for when it should generate next roll
	int minAmount;		// Min generated amount per roll 
	int maxAmount;		// Max generated amount per roll
	int minInterval;	// Min time until next roll in seconds
	int maxInterval;	// Max time until next roll in seconds
};

struct NeutralObject {
	int type;
	int x;
	int y;
	int dx;
	int dy;
};

struct Object {
	SDL_Point pos;
	SDL_Point speed;
	int max_speed;
	int acc;
	int drag;
	SDL_Point velocity;
	int facing;
};

struct Object object[MAX_NUM_OBJ];

struct SpawnOdds spawnOdds_powerup[NUM_OF_POWERS];
struct SpawnOdds spawnOdds_asteroid;

struct NeutralObject neutralObj[100];
int num_spawned_neutral_obj;

int worldWidth;
int worldHeight;

void init_logic();
void respawnShips();
void setup_spawnOdds(struct SpawnOdds* so, int minAmount, int maxAmount, int minInterval, int maxInterval);
void set_spawnOddsNextRollTime(struct SpawnOdds* so);
void set_worldDimensions(int w, int h);
void generateNeutralObjects();

void TCP_broadcastCreatedNeutralObject(int obj_type, SDL_Point spawn, SDL_Point velocity, int facing);
void TCP_broadcastPlayerDisconected(int connecting_id);
