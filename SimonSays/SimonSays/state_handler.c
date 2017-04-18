/*	Author(s):	Tiago Redaelli	
	Modified:	14-04-2017
	Version:	0.01
	
	Funderar på att ändra detta till en kö så att man kan lägga till flera states i följd.
*/

#include "state_handler.h"
#include "game.h"
#include "game_state.h"


int state_next;

void executeNextState()
{
	switch (state_next) {
		case STATE_GAME_RUNNING: onGameRunning(); break;
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