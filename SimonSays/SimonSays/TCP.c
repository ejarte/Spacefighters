
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
	char completeMsg[100] = "HELLO";
	int portNr = SENDPORT + player_id; //varje spelare skickar via sin egna Port
	sprintf(completeMsg, "Player %d: %s", player_id, incommingMsg); //lägger ihop meddelandet med spelares Alias

	//write the ip of the host 
	SDLNet_ResolveHost(&ip, SERVERIP, portNr);
	client = SDLNet_TCP_Open(&ip);

	SDLNet_TCP_Send(client, completeMsg, strlen(completeMsg) + 1);
	SDLNet_TCP_Close(client);
}

void imConnected(int player_id)
{

	IPaddress ip;
	TCPsocket client;
	int portNr = CONNECTPORT + player_id; //varje spelare skickar via sin egna Port
																	//write the ip of the host 
	SDLNet_ResolveHost(&ip, SERVERIP, portNr);

	while(1)
	{
		client = SDLNet_TCP_Open(&ip);

		SDL_Delay(1000);

		SDLNet_TCP_Send(client, 1, 20);
		SDLNet_TCP_Close(client);
	}
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

	SDLNet_ResolveHost(&ip, SERVERIP, RECVPORT + player_id);
	while (1)
	{
		client = SDLNet_TCP_Open(&ip);
		char listenMessage[1000] = "";
		SDLNet_TCP_Recv(client, &listenMessage, 1000); //recv on socket client, store in listenmsg, the incomming msg max length 1000
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
	printf("testing connection\n");
	if (SDLNet_ResolveHost(&ip, SERVERIP, INITPORT) == -1)
	{
		printf("Couldn't resolve host during the connection!\n");
		SDL_Delay(4000);
		exit(1);
	}
	client = SDLNet_TCP_Open(&ip);

	int player_id = 0;
	printf("Player id %d\n", player_id);
	SDLNet_TCP_Recv(client, &player_id, 100);

	SDLNet_TCP_Close(client);
	printf("player id: %d\n", player_id);

	createDemonCL(player_id, "listenForMessage", listenForMessage);
	createDemonCL(player_id, "imConnected", imConnected);

	return player_id;
}