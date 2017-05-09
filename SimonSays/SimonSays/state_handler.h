/*	Author(s):	Tiago Redaelli
*	Modified:	14-04-2017
*	Version:	0.01
*/

#pragma once

#include "libraries.h"

#define STATE_EXIT				0
#define STATE_GAME_RUNNING		1
#define STATE_MAIN_MENU			2
#define STATE_NETWORK_MENU		3
#define STATE_COUNT				4

void executeNextState();
void setNextState(int state);
int getNextState();