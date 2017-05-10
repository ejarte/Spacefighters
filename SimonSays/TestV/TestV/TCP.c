//----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libaries.h"

//----------------------------------------------------------------------
#define SDL_MAIN_HANDLED
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

void createDemon()
{
	SDL_Thread *TCPThread = NULL;
	const char *TCPThreadReturnValue;
	TCPThread = SDL_CreateThread(TCP, "TestThread", "127.0.0.1");

	if (NULL == TCPThread) {
		printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
	}
	else {

		printf("\nYouve created a demon");
	}
}

int TCP()
{
	//printf("TCP\n");

	SDLNet_ResolveHost(&ip, NULL, 1234); //NULL betyder är detta är servern

	server = SDLNet_TCP_Open(&ip); //öppnar server socketen med sin egna ipadres och port 1234

	while (1)
	{
		client = SDLNet_TCP_Accept(server); //ligger och lyssnar på kontakt med klient
		if (client)
		{
			players[player_id] = client;
			printf("player id: %d\n", player_id);
			printf("client id: %d\n", client);
			SDLNet_TCP_Send(client, &player_id, sizeof(player_id));

			char *host;
			if (!(host = SDLNet_ResolveIP(&ip))) {
				printf("SDLNet_ResolveIP: %s\n", SDLNet_GetError());
				exit(1);
			}
			printf("Server hostname: %s\n", host);
			printf("Server ipadress: %s and port %d\n", ip.host, ip.port);

			// get the remote IP and port
			//TCPsocket new_tcpsock;
			IPaddress *remote_ip;

			remote_ip = SDLNet_TCP_GetPeerAddress(client);
			if (!remote_ip) {
				printf("SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());
				printf("This may be a server socket.\n");
			}
			else {
				// print the info in IPaddress or something else...
				printf("clients ipadress: %d and port %d\n", remote_ip->host, remote_ip->port);
			}

			player_id++;
			SDLNet_TCP_Close(client);
		}

	}

	//stänger ned kommunikationen när servern stängs ned
	SDLNet_TCP_Close(client);
	SDLNet_TCP_Close(server);
	return 0;
}