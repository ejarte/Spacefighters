#include "state_handler.h"
#include "game.h"
#include "intro_menu.h"


int state_next;

void executeNextState()
{
	switch (state_next) {
		case STATE_GAME_RUNNING: game_execute(); break;
		case STATE_MAIN_MENU: execute_introMenu(); break;
		default: break;
	}
}

void setNextState(int state)
{
	if (state >= 0 && state < STATE_COUNT) {
		state_next = state;
	}
	else {
		printf("ERROR: Invalid State entry. Program Terminated.\n");
		exit(-1);
	}
}

int getNextState()
{
	return state_next;
}