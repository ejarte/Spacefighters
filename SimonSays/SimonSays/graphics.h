#pragma once

#include "libraries.h"

SDL_Renderer*	renderer; //variabeln för att uppdatera fönstret
SDL_Window*		window;		//fönstret

int screenW;				// Dessa bör flyttas in till graphics_lib.c
int screenH;
SDL_DisplayMode DM;

void initWindow();
int getWindowHeight();
int getWindowWidth();
