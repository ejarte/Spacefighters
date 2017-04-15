/*	Author(s):	Tiago Redaelli
*	Modified:	14-04-2017
*	Version:	0.01
*/

#include "states.h"
#include "game_state.h"
#include "space_simulator.h"

int state_next;

void executeNextState()
{
	switch (state_next) {
		case STATE_GAME_RUNNING:		onGameRunning(); break;
		case STATE_SETUP_SPACE_SIM:		setupSpaceSimulator();
		case STATE_RUN_SPACE_SIM:		runSpaceSimulator();
		default: break;
	}
}

void setNextState(int state)
{
	if (state >= 0 && state < STATE_COUNT) {
		state_next = state;
		// DEBUG
		printf("next state = %d\n", state);

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