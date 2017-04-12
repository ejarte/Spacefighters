/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include "main.h"


int main(int argc, char* args[])
{
	initWindow();

	while (quit == false)	//körs tills användaren trycker på X uppe i fönstret
	{
		eventLoop();		//kollar efter användarens input
		initImages();
		drawScreen();		//ritar upp bilder m.m. på fönstret
		clearImages();
	}

	clearPointers();		//Tar bort pekarna ur minnet för säkerhets skull

	return 0;

}
