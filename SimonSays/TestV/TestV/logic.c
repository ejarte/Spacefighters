#include "logic.h"
#include "world.h"

void init_logic()
{
	for (int i = 0; i < 4; i++) {
		world_spawnSpaceship(&player[i], 400, 400, 0);
	}
}

void run_logic()
{

}