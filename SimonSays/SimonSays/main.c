/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include "main.h"

int main(int argc, char* args[])
{
	initWindow();
	initImages();

	while (quit == false)	//k�rs tills anv�ndaren trycker p� X uppe i f�nstret
	{
		eventLoop();		//kollar efter anv�ndarens input
		drawScreen();		//ritar upp bilder m.m. p� f�nstret
	}

	clearPointers();

	return 0;

}