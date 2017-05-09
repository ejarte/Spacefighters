#include "events.h"
#include "graphics.h"
#include "state_handler.h"
#include "audio.h"
#include "game.h"
#include "definition.h"
#include "intro_menu.h"

struct PlayerInfo
{
	int number;

}; typedef Spelare;

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		printf("SDL_Init: %s\n", SDL_GetError());
		exit(-1);
	}
	else printf("SDL Initialized...\n");

	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}
	else printf("TTF Initialized...\n");

	if (SDLNet_Init() == -1) {
		printf("NET_Init: %s\n", SDLNet_GetError());
	}
	else
	{
		printf("NET Initialized...\n");
	}

	initWindow();
	initEventHandler();
	init_introMenu();
	//initCommands();

	// Seed random
	srand(time(NULL));

	// Audio
	initAudio();
	game_init();
	SDL_Delay(50);
	//playMusic("audio/music/SPACE.mp3", -1);

	bool run = true;
	//setNextState(STATE_MAIN_MENU);
	setNextState(STATE_GAME_RUNNING);
	
	int startTime;
	const int frameRate = 30;				//Set desired frame rate per second
	int desiredFrameMs = 1000 / frameRate;	//Calculates time for each frame
	int waitTime;
	int cycle = 0;							// Cycle

	while (run)	
	{
		cycle++;
		curTime = SDL_GetTicks();	
		startTime = curTime;
		refreshEventHandler();	// maps user input
		if (getNextState() == STATE_EXIT) {
			run = false;
		}
		else {
			executeNextState();
		}
		// Synchronize frame rate
		waitTime = desiredFrameMs - (SDL_GetTicks() - startTime);
		if (waitTime >= 0)
			SDL_Delay(waitTime);
		else printf("Warning: You are currently running slower then 30 fps. (Cycle: %d.)\n", cycle);
	}
	return 0;
}
