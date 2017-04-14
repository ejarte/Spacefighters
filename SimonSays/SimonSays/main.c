/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include "main.h"
#include "graphics_lib.h"

int main(int argc, char* args[])
{
	initWindow();
	initEventHandler();
	initNormal();

	run_program = true;

	while (run_program)	// körs tills användaren trycker på X uppe i fönstret
	{
		refreshEventHandler();		// mappar användarinput
		lookState();

		initImages();				//initierar bilder
		drawScreen();				//ritar upp bilder m.m. på fönstret
		clearImages();				//rensar bilderna från ram
	}

	clearPointers();		//Tar bort pekarna ur minnet för säkerhets skull

	return 0;

}
