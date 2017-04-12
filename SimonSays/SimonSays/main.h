// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define BTNHEIGHT 100
#define BTNWIDTH 100
#include "libaries.h"
#include "init_sdl.h"

SDL_Renderer* renderer;
SDL_Event mainEvent;
SDL_Window* window;
bool quit;

SDL_Rect yellow_rect; //rutan där bilden kommer finnas
SDL_Rect green_rect;
SDL_Rect red_rect;
SDL_Rect blue_rect; //rutan där bilden kommer finnas


// TODO: reference additional headers your program requires here
