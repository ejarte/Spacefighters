
#include <SDL.h>
#include <SDL_net.h>
#include <stdio.h>
#include <string.h>

#include "TCP.h"


const char * TCP(int ipNr)
{
	//SDLNet_Init();
	printf("P was pressed ");
	printf("Client\n");
	char text[100];
	IPaddress ip;
	TCPsocket client;

	//write the ip of the host

	SDLNet_ResolveHost(&ip, ipNr, 1234);
	client = SDLNet_TCP_Open(&ip);


	SDLNet_TCP_Recv(client, text, 100);
	printf("Text : %s\n", text);



	SDLNet_TCP_Close(client);


	return text;
}