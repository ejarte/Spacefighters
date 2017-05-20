#include "text_commands.h"
#include "object.h"
#include "network.h"

#define COMMAND_0 "-setname"

struct Command_t {
	int length;
	char* s;
	char* help;
};

struct Command_t command[10];
int num_commands;

void setupCommand(struct Command_t* cmd, char* str, char* help_msg)
{
	cmd->s = str;
	cmd->length = strlen(str);
	cmd->help = help_msg;
	printf("command: %s %d\n", cmd->s, cmd->length);
}

void initCommands()
{
	setupCommand(&command[0], "-setname", "-setname 'Kaiser Soze'");
	num_commands = 1;
}

void cmd_0(char* cmd) 
{
	char* name = substring(cmd, command[0].length + 1, strlen(cmd));
	TCP_sendNameChange(name);
}

bool runCommands(char* str)
{
	if (str[0] != '-')
		return false;

	if (strcmp(str, "-help") == 0) {
		printf("Commands: \n");
		for (int i = 0; i < num_commands; i++) {
			printf("%s\n", command[i].help);
		}
		return true;
	}
	
	if (strcmp(str, "-start") == 0) {
		printf("Commands: \n");
		startTheGame = true;
	}
	if (strncmp(command[0].s, str, command[0].length) == 0) {
		cmd_0(str);
		return true;
	}
	printf("Invalid command\n");
	return false;
}