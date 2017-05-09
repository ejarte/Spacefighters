
#include <SDL.h>
#include <SDL_net.h>
#include <stdio.h>
#include <string.h>

#include "TCP.h"
#include "game.h"
#include "definition.h"

void sendMessage()
{

}

int connect(int currentID)
{
	IPaddress ip;
	TCPsocket client;

	//write the ip of the host

	SDLNet_ResolveHost(&ip, "127.0.0.1", 1234);
	client = SDLNet_TCP_Open(&ip);

	int player_id;
	
	SDLNet_TCP_Recv(client, &player_id, 100);

	SDLNet_TCP_Close(client);
	printf("player id: %d\n", player_id);

	return player_id;
}

const char * TCP(int ipNr) //demon
{
	IPaddress ip;
	TCPsocket client;

	//write the ip of the host

	SDLNet_ResolveHost(&ip, ipNr, 1234);
	client = SDLNet_TCP_Open(&ip);

	char text[100];

	while (1)
	{
		SDLNet_TCP_Recv(client, &text, 100);
		printf(" heer");
		if (text != NULL)
		{
			//addPlayerMessageToDisplay(renderer, client_player_num, text, MSG_DURATION);
		}
	}

	SDLNet_TCP_Close(client);

	return text;
}