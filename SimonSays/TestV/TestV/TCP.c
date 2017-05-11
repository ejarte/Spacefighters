//----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libaries.h"

//----------------------------------------------------------------------
#define SDL_MAIN_HANDLED
//----------------------------------------------------------------------

int TCP()
{
	//printf("TCP\n");

	SDLNet_ResolveHost(&ip, NULL, INITPORT); //NULL betyder �r detta �r servern 
										 //1234 �r initport

	server = SDLNet_TCP_Open(&ip); //�ppnar server socketen med sin egna ipadres och port 1234

	while (1)
	{
		client = SDLNet_TCP_Accept(server); //ligger och lyssnar p� kontakt med klient
		if (client)
		{
			players[player_id] = client;
			printf("player id: %d\n", player_id);
			printf("client id: %d\n", client);

			SDLNet_TCP_Send(client, &player_id, sizeof(player_id));
			printf("player id in TCP: %d\n", player_id);

			char *host;
			if (!(host = SDLNet_ResolveIP(&ip))) {
				printf("SDLNet_ResolveIP: %s\n", SDLNet_GetError());
				exit(1);
			}
			printf("Server hostname: %s\n", host);
			printf("Server ipadress: %s and port %d\n", ip.host, ip.port);
			
			createDemon(player_id, "listen", listen);
			createDemon(player_id, "send", send);

			player_id++;
			SDLNet_TCP_Close(client); //st�nger ned anslutningen mot klienten
		}

	}

	//st�nger ned kommunikationen n�r servern st�ngs ned
	SDLNet_TCP_Close(client);
	SDLNet_TCP_Close(server);
	return 0;
}