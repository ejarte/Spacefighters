#include "logic.h"
#include "world.h"

void init_logic()
{
	object_init();

	// Instansierar alla objekt i en plats utanför skärmen
	for (int i = 0; i < MAX_NUM_OBJ; i++) {
		object[i].center_x = -400;
		object[i].center_y = -400;
	}
	// Skapar rymdskeppen
	for (int i = 0; i < 4; i++) {
		world_spawnSpaceship(&player[i], 100+ 100*i, 100 +100*i, 0);
	}
	// printar info om alla objekt (en används ej som du ser och är -400, -400 i position
	for (int i = 0; i < 5; i++) {
		printf("object[%d], %d %d\n", i, object[i].center_x, object[i].center_y);
	}
}

void run_logic()
{
	for (int i = 0; i < 5; i++) {
		// skicka data!
	}
}