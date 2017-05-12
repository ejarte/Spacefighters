#include "world.h"

int myIndex = 0;

void world_spawnSpaceship(struct Player* p, int x, int y, double facingAng)
{
	double facing = 0;
	double facingOff = 0;
	int w = 112 / 3;
	int h = 75 / 3;
	int i = myIndex++;

	//p->alive = true;
	//p->mobile = true;
	//p->spaceship = &object[i];
	//p->speed_active = false;
	object_setup(&object[i], i, OBJ_TYPE_SPACESHIP, x, y, w, h, facing, facingOff);
	object[i].acc = SPEED_ACC_DEFAULT;
	object[i].speed_max = SPEED_MAX_DEFAULT;
	object[i].drag = DRAG_SPACESHIP;
	object[i].hp = LIFE_SPACESHIP;
	object[i].dmg_on_impact = 0;

	printf("Created spaceship at: %d %d (Obj %d).\n", x, y, i);


	//p->spaceship = &object[i];
	//p->shipIndex = i;
	//object_setCollisionBox(&object[i], 25, 25);
}