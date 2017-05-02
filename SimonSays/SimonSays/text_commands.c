#include "text_commands.h"
#include "object.h"

/*
#define COMMAND_1 "event horizon"

char* command[100];
int num_commands;

void initCommands()
{
	command[0] = "-tot created obj";
	command[1] = "-object index";
	num_commands = 2;
}

void cmd_0() {
	printf("Total number of created objects: %d.\n", tot_created_obj);
}


bool runCommands(char* str)
{
	if (str[0] != '-')
		return false;

	if (strcmp(str, "-help") == 0) {
		printf("Commands: \n");
		for (int i = 0; i < num_commands; i++) {
			printf("%s\n", command[i]);
		}
		return true;
	}

	if (strcmp(str, command[0]) == 0) {
		cmd_0();
		return true;
	}

	printf("Invalid command\n");
	return false;
}

*/