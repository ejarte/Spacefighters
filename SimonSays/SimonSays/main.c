/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO

#include "events.h";
#include "graphics_lib.h"
#include "state_handler.h"
#include "game_state.h"

int main(int argc, char* args[])
{
	initWindow();
	initEventHandler();
	initNormal();
	spaceShipSetup();

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
		SDL_Delay(30);
	}
	clearPointers();		//Tar bort pekarna ur minnet för säkerhets skull

	return 0;

}
