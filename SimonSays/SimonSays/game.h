#pragma once

#include "libraries.h"
#include "definition.h"
#include "object.h"
#include "events.h"
#include "state_handler.h"
#include "world.h"
#include "particle.h"
#include "graphics.h"
#include "text_commands.h"
#include "interface_lib.h"

struct Label playerNameLabel[MAX_PLAYERS];
TTF_Font* font_roboto_black;

void game_init();
void game_execute(); //den exekverar allt annat som skall göras, i vilken ordning
void game_events();
void game_update();
void game_render();

// Support functions
void startRound();
