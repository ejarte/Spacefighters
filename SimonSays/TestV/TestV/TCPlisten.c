//----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------------------------
#define SDL_MAIN_HANDLED
#include "libaries.h"


int send(int connectedIp)
{

	IPaddress specific_ip;
	TCPsocket specific_server;
	TCPsocket specific_client;

	int portId = BROADCASTPORT + connectedIp; //specport = 6000
	printf("\n\nspecic thread\n");
	SDLNet_ResolveHost(&specific_ip, NULL, portId); //NULL betyder �r detta �r servern

	specific_server = SDLNet_TCP_Open(&specific_ip); //�ppnar server socketen med sin egna ipadres och port 1234
	printf("portNr: %d", portId);


	while (1)
	{
		if (broadCast == true)
		{
			specific_client = SDLNet_TCP_Accept(specific_server); //ligger och lyssnar p� kontakt med klient
			if (specific_client) //nu �ppnas kontakten mellan klienten och servern p� den h�r porten
			{
				SDLNet_TCP_Send(specific_client, message, 1000);
				printf("meddelande: %s\n", message);
				SDL_Delay(500);
				broadCast = false;
			}
			//SDLNet_TCP_Close(client);
		}
	}

	SDLNet_TCP_Close(client);
	SDLNet_TCP_Close(server);
	return 0;
}

int listen(int connectedIp)
{
	IPaddress specific_ip;
	TCPsocket specific_server;
	TCPsocket specific_client;

	int portId = SPECPORT; //specport = 5000
	printf("\n\nspecic thread\n");
	portId += connectedIp;
	SDLNet_ResolveHost(&specific_ip, NULL, portId); //NULL betyder �r detta �r servern

	specific_server = SDLNet_TCP_Open(&specific_ip); //�ppnar server socketen med sin egna ipadres och port 1234
	printf("portNr: %d", portId);

	while (1)
	{
		specific_client = SDLNet_TCP_Accept(specific_server); //ligger och lyssnar p� kontakt med klient
		if (specific_client) //nu �ppnas kontakten mellan klienten och servern p� den h�r porten
		{
			SDLNet_TCP_Recv(specific_client, &message, 1000);
			broadCast = true;
			printf("meddelande: %s\n", message);
			SDLNet_TCP_Close(client); 
		}

	}

	//st�nger ned kommunikationen n�r servern st�ngs ned
	SDLNet_TCP_Close(client);
	SDLNet_TCP_Close(server);
	return 0;

}