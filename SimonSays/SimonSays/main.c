/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include "main.h"


int main(int argc, char* args[])
{
	initWindow();
	initEventHandler();

	run_program = true;

	while (run_program)	// k�rs tills anv�ndaren trycker p� X uppe i f�nstret
	{
		refreshEventHandler();		// mappar anv�ndarinput
		lookEvents();				//kollar inputs fr�n anv�ndaren och g�r n�got ifall det �r true - events.c

		initImages();				//initierar bilder
		drawScreen();				//ritar upp bilder m.m. p� f�nstret
		clearImages();				//rensar bilderna fr�n ram
	}

	clearPointers();		//Tar bort pekarna ur minnet f�r s�kerhets skull

	return 0;

}
