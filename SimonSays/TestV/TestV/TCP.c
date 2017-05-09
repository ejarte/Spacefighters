
//----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//----------------------------------------------------------------------
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_net.h"

#include "TCP.h"
#include "definitions.h"


//----------------------------------------------------------------------

int stringToInt(const char * pString)
{
	int number;
	number = atoi(pString);
	return number;
}

const char * intToString(int number)
{
	char inputString[100];
	itoa(inputString, number, 1);
	return inputString;
}


int TCP()
{
	printf("TCP\n");


	IPaddress ip;
	
	SDLNet_ResolveHost(&ip, NULL, 1234);

	TCPsocket server = SDLNet_TCP_Open(&ip);
	TCPsocket client;

	int number = 0;


	char text[100] = "";
	
	while (1)
	{
		client = SDLNet_TCP_Accept(server);
		if (client)
		{
			printf("player id: %d\n", player_id);
			SDLNet_TCP_Send(client, &player_id, sizeof(player_id));
			player_id++;
			SDLNet_TCP_Close(client);
		}	
		
	}

	//stänger ned kommunikationen när servern stängs ned
	SDLNet_TCP_Close(client);
	SDLNet_TCP_Close(server);
	return 0;
}