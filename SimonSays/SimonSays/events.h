/*	Author(s):	Tiago Redaelli
*	Modified:	14-04-2017
*	Version:	0.02
*/

#ifndef EVENTS_H
#define EVENTS_H

#include "libraries.h"

#define STATE_RELEASED					99		// Flag for Released Key/Button
#define STATE_PRESSED					98		// Flag for Pressed Key/Button

int getWindowHeight();
int getWindowWidth();

bool isTextEventEnabled();
bool textEvent();
char* getTextInput();
void disableTextInput();
void enableTextInput();

// Mouse
SDL_Point getMousePos();
int getMouseX();
int getMouseY();

int getTimeStamp(int flag, SDL_Scancode sc);

bool mouseEventHeld(SDL_Scancode sc);
bool mouseEventReleased(SDL_Scancode sc);
bool mouseEventPressed(SDL_Scancode sc);

bool keyEventHeld(SDL_Scancode sc);
bool keyEventReleased(SDL_Scancode sc);
bool keyEventPressed(SDL_Scancode sc);

bool quitEventTriggered();

void refreshEventHandler();
void initEventHandler();	

#endif