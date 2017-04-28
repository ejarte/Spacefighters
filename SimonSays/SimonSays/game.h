#pragma once

#include "libraries.h"

void game_init();
void game_execute(); //den exekverar allt annat som skall göras, i vilken ordning
void game_events();
void game_update();
void game_render();