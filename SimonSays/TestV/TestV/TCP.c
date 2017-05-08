
//----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//----------------------------------------------------------------------
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_net.h"

#include "TCP.h"


//----------------------------------------------------------------------
int TCP()
{
	printf("TCP\n");


	IPaddress ip;
	
	SDLNet_ResolveHost(&ip, NULL, 1234);

	TCPsocket server = SDLNet_TCP_Open(&ip);
	TCPsocket client;

	char text[100] = "Hampus!\n";
	
	
	while (1)
	{
		client = SDLNet_TCP_Accept(server);
		if (client)
		{
			printf("%d\n", client);
			scanf("%s", text);
			//here you can communitcate with the client
			SDLNet_TCP_Send(client, text, strlen(text) + 1);
			//SDLNet_TCP_Close(client);

			//break;
			
		}
		
	}
	SDLNet_TCP_Close(server);
	return 0;
}