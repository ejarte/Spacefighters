#pragma once

#include "libraries.h"
#include "definition.h"

int screenW;				
int screenH;

SDL_DisplayMode DM;

void initWindow();
void loadFont(TTF_Font *font, const char* filepath, int fontsize);