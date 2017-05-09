#pragma once
#include <stdbool.h>

struct Player {
	char* name;
	int color;
	SDL_Color sdl_color;
	bool alive;
	bool mobile;
	bool connected;
	struct Object* spaceship;
	int death_timestamp;
	int attack_timestamp;
	int rune_speed_timestamp;
	int rune_atk_timestamp;
	int acceleration_timestamp;
	bool speed_active;
	int current_attack_type;
	int shipIndex;

	int killstreak_tot;
	int killstreak_round;
	int kills;
	int deaths;
	int won_rounds;
};

bool messageRec;