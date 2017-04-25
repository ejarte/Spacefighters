#pragma once

#include "libraries.h"

SDL_Renderer*	renderer; //variabeln för att uppdatera fönstret
SDL_Window*		window;		//fönstret

int screenW;				
int screenH;

SDL_DisplayMode DM;

void initWindow();
