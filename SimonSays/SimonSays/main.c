/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO

#include "events.h";
#include "graphics.h"
#include "state_handler.h"
#include "game_state.h"
#include "audio.h"
#include "world.h"
#include "game.h"

int main(int argc, char* args[])
{
	initWindow();
	initEventHandler();
	game_init();
	initWorld();

	//initNormal();
	//spaceShipSetup();
	//initSky();

	// Audio
	initAudio();
	SDL_Delay(50);
	//playMusic("audio/music/SPACE.mp3", -1);


	bool run = true;

	setNextState(STATE_GAME_RUNNING);
	
	while (run)	// körs tills användaren trycker på X uppe i fönstret
	{
		refreshEventHandler();		// mappar användarinput
		if (getNextState() == STATE_EXIT) {
			run = false;
		}
		else {
			executeNextState();
		}
		// Syncronize frame rate
		SDL_Delay(20);
	}
	return 0;
}
