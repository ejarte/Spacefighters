/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO

#include "graphics_lib.h"
#include "game_state.h"

int main(int argc, char* args[])
{
	initWindow();
	initEventHandler();
	initNormal();

	bool run_program = true;

	while (run_program)	// k�rs tills anv�ndaren trycker p� X uppe i f�nstret
	{
		refreshEventHandler();		// mappar anv�ndarinput
		lookState();

		initImages();				//initierar bilder
		drawScreen();				//ritar upp bilder m.m. p� f�nstret
		clearImages();				//rensar bilderna fr�n ram
	}

	clearPointers();		//Tar bort pekarna ur minnet f�r s�kerhets skull

	return 0;

}
