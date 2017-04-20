#include "spaceship.h"
#include "graphics.h"
#include "Object.h"

struct Spaceship_type {

	Object **body;

	// Physics
	float delta_x;
	float delta_y;
	float drag;
	float acc;
	float weight; 

	// Status
	bool mobile;
	float hp;
	float armor;
	float damage;

};

Spaceship *createSpaceship() {
	return (Spaceship*) malloc(sizeof(Spaceship));
}

