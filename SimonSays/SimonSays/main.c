/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include "main.h"

int main(int argc, char* args[])
{
	initWindow();
	initImages();

	while (quit == false)	//körs tills användaren trycker på X uppe i fönstret
	{
		eventLoop();		//kollar efter användarens input
		drawScreen();		//ritar upp bilder m.m. på fönstret
	}

	clearPointers();

	return 0;

}