// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define BTNHEIGHT 100
#define BTNWIDTH 100
#include "libaries.h"
#include "init_sdl.h"
#include "events.h"
#include "graphics_lib.h"

//deklererar variabler
bool run_program;		//om false så stängs programet av

SDL_Rect yellow_rect; //rutan där bilden kommer finnas
SDL_Rect green_rect;
SDL_Rect red_rect;
SDL_Rect blue_rect;

void clearImages();

// TODO: reference additional headers your program requires here
