/*	Author(s):	Tiago Redaelli
*	Modified:	14-04-2017
*	Version:	0.02
*/

#ifndef EVENTS_H
#define EVENTS_H

#include "libaries.h"

#define STATE_RELEASED					99		// Flag for Released Key/Button
#define STATE_PRESSED					98		// Flag for Pressed Key/Button

bool isTextEventEnabled();
bool textEvent();
char* getTextInput();
void disableTextInput();
void enableTextInput();
void lookState();

SDL_Point p;			//musens position

//variabler och funktioner kopplat till knapparna som hanteras i event.c
/*
char yellowPath[30];
char greenPath[30];
char bluePath[30];
char redPath[30];
*/
void initNormal();
void checkButtonClicked();

SDL_Point getMousePos();
int getMousex();
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