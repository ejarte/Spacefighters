#pragma once

#include "audio.h"

void initAudio()
{
	SDL_Init(SDL_INIT_AUDIO);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		printf("Error, Sound cannot be loaded");
}