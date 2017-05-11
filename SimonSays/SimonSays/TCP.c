
#include <SDL.h>
#include <SDL_net.h>
#include <stdio.h>
#include <string.h>

#include "TCP.h"
#include "game.h"
#include "definition.h"


void sendMessage(int player_id, char incommingMsg[])
{
	
	IPaddress ip;
	TCPsocket client;

	char test[100] = "HELLO";
	sprintf(test, "Player %d: %s", player_id, incommingMsg);
	
	const char* text = test; //test för vara ingående värdet från klienten

	char message[] = "test\n"; //texten som skickas till servern
	int portNr = 5000;
	portNr += player_id;

	printf("portNr: %d", portNr);

	//write the ip of the host

	SDLNet_ResolveHost(&ip, "127.0.0.1", portNr);
	client = SDLNet_TCP_Open(&ip);

	SDLNet_TCP_Send(client, text, strlen(text) + 1);
	SDLNet_TCP_Close(client);
	//	printf("player id: %d\n", randomNr);

	//	return randomNr;
}

void createDemonCL(int id, const char * function, void(*f)(int)) //spelarens id, namnet på funktionen, själva funktionen
{
	SDL_Thread *TCPThread = NULL;
	printf("ID %d \n", id);
	TCPThread = SDL_CreateThread(f, function, id);

	if (NULL == TCPThread) {
		printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
	}
	else {
		printf("\nYou've created a demon, you monster!\n");
	}
}

void listenForMessage(int player_id)
{
	IPaddress ip;
	TCPsocket client;

	//write the ip of the host

	SDLNet_ResolveHost(&ip, "127.0.0.1", 6000 + player_id);
	while (1)
	{
		client = SDLNet_TCP_Open(&ip);

		char listenMessage[1000];

		SDLNet_TCP_Recv(client, &listenMessage, 1000);

		SDLNet_TCP_Close(client);
		addMessageToDisplay(renderer, listenMessage, MSG_DURATION);
	}
	return 0;
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

	createDemonCL(player_id, "listenForMessage", listenForMessage);

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