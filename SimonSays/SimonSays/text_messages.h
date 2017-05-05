#pragma once

#include "libraries.h"
#include "interface_lib.h"
#include "definition.h"

struct Text_Line {
	struct Label label[10];
	int end_time;
	int size;
};

int current_lines;

int current_lines;
void init_text_messages();
void addPlayerMessageToDisplay(SDL_Renderer* rend, int p_id, char* msg, int time_seconds);
void renderMessageDisplay(SDL_Renderer* rend);