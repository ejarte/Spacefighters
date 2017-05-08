#pragma once

#include "libraries.h"

void initAudio();
/*
	@repeats: amount of times it repeats. -1 to flag as a loop.
*/
void playMusic(char *filepath, int repeats);