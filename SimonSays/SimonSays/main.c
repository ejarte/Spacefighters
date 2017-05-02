#include "events.h";
#include "graphics.h"
#include "state_handler.h"
#include "game_state.h"
#include "audio.h"
#include "world.h"
#include "game.h"
#include "text_commands.h"

int main(int argc, char* args[])
{
	initWindow();
	initEventHandler();
	game_init();
	initCommands();

	// seed random - call only once!
	srand(time(NULL));

	//initNormal();
	//spaceShipSetup();
	//initSky();

	// Audio
	initAudio();
	SDL_Delay(50);
	//playMusic("audio/music/SPACE.mp3", -1);

	

	bool run = true;

	setNextState(STATE_GAME_RUNNING);
	
	while (run)	// k�rs tills anv�ndaren trycker p� X uppe i f�nstret
	{
		refreshEventHandler();		// mappar anv�ndarinput
		if (getNextState() == STATE_EXIT) {
			run = false;
		}
		else {
			executeNextState();
		}
		// Syncronize frame rate
		SDL_Delay(20);
	}

	printf("Detta �r ett commit test.\n");

	return 0;
}
