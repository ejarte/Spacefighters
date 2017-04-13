/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include "main.h"


int main(int argc, char* args[])
{
	initWindow();
	initEventHandler();

	run_program = true;

	while (run_program)	// körs tills användaren trycker på X uppe i fönstret
	{
		refreshEventHandler();		// mappar användarinput


		// Enables/disables chat on return key
		if (keyEventPressed(SDL_SCANCODE_RETURN)) {
			if (isTextEventEnabled()) {
				puts("Chat disabled.");
				disableTextInput();
			}
			else {
				puts("Chat enabled");
				enableTextInput();
			}
		}

		// if the chat is enabled and a text event was triggered it gets the text input
		if (textEvent()) {
			puts(getTextInput());
		}

		if (mouseEventHeld(SDL_BUTTON_LEFT))
			puts("Held: Left mouse");

		if (mouseEventPressed(SDL_BUTTON_LEFT))
			printf("Left mouse pressed - %d\n", getTimeStamp(STATE_PRESSED, SDL_BUTTON_LEFT));

		
		if (mouseEventReleased(SDL_BUTTON_LEFT))
			printf("Left mouse released - %d\n", getTimeStamp(STATE_RELEASED, SDL_BUTTON_LEFT));

		if (keyEventHeld(SDL_SCANCODE_W))
			puts("Held: W");

		if (keyEventPressed(SDL_SCANCODE_W)) 
			printf("W pressed - %d\n", getTimeStamp(STATE_PRESSED, SDL_SCANCODE_W));

		if (keyEventReleased(SDL_SCANCODE_W)) 
			printf("W released - %d\n", getTimeStamp(STATE_RELEASED, SDL_SCANCODE_W));

		if (quitEventTriggered()) {
			run_program = false;
			puts("quit was sent");
		}

		initImages();
		drawScreen();				//ritar upp bilder m.m. på fönstret
		clearImages();
	}

	clearPointers();		//Tar bort pekarna ur minnet för säkerhets skull

	return 0;

}
