#ifndef GRAPHICS_LIB_H
#define GRAPHICS_LIB_H

#include "libaries.h"

SDL_Renderer*	renderer; //variabeln f�r att uppdatera f�nstret
SDL_Window*		window;		//f�nstret


int screenW;
int screenH;
SDL_DisplayMode DM;

void initWindow();

#endif
