#include "events.h";
#include "graphics.h"
#include "state_handler.h"
#include "audio.h"
#include "world.h"
#include "game.h"
#include "text_commands.h"

int main(int argc, char* args[])
{
	initWindow();
	initEventHandler();
	game_init();
	//initCommands();

	// seed random - call only once!
	srand(time(NULL));

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
		SDL_Delay(33);
	}

	return 0;
}
