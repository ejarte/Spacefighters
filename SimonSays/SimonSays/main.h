// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define BTNHEIGHT 100
#define BTNWIDTH 100
#include "libaries.h"
#include "init_sdl.h"

//deklererar variabler
SDL_Renderer* renderer; //variabeln f�r att uppdatera f�nstret
SDL_Event mainEvent;	//variabeln som uppt�cker om anv�ndaren st�nger ned f�nstret
SDL_Window* window;		//f�nstret
bool quit;				//om true s� st�ngs spelloopen av

SDL_Rect yellow_rect; //rutan d�r bilden kommer finnas
SDL_Rect green_rect;
SDL_Rect red_rect;
SDL_Rect blue_rect;


// TODO: reference additional headers your program requires here
