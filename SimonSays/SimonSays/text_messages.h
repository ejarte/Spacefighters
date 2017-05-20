#pragma once

#include "libraries.h"
#include "interface_lib.h"
#include "definition.h"

void init_text_messages();
void addMessageToDisplay(SDL_Renderer* rend, char* msg, int time_seconds);
void addPlayerMessageToDisplay(SDL_Renderer* rend, int p_id, char* msg, int time_seconds);
void addPlayerEmoteMessageToDisplay(SDL_Renderer* rend, int p_id, char* msg, int time_seconds);
void renderMessageDisplay(SDL_Renderer* rend);