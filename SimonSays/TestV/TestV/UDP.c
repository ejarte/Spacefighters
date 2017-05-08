//----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------------------------
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_net.h"

#include "UDP.h"

//----------------------------------------------------------------------
int UDP()
{
	printf("UDP\n");


	IPaddress adrs[4] = { 0,0,0,0 };


	IPaddress ip;
	UDPsocket server;
	UDPsocket client;
	UDPpacket *packet;
	UDPpacket *packets;

	server = SDLNet_UDP_Open(1234);
	client = SDLNet_UDP_Open(0);

	packet = SDLNet_AllocPacket(1024);
	packets = SDLNet_AllocPacket(1024);

	


	while (1)
	{
		/* Wait a packet. UDP_Recv returns != 0 if a packet is coming */
		SDL_Delay(1000);
		while (SDLNet_UDP_Recv(server, packet))
		{
			void SDL_Delay(Uint32 ms);
			SDL_Delay(1000);
			printf("UDP Packet incoming\n");
			printf("\tChan:    %d\n", packet->channel);
			printf("\tData:    %s\n", (char *)packet->data);
			printf("\tLen:     %d\n", packet->len);
			printf("\tMaxlen:  %d\n", packet->maxlen);
			printf("\tStatus:  %d\n", packet->status);
			printf("\tAddress: %x %x\n", packet->address.host, packet->address.port);

			//detta skickar med ipadressen som kom
			packets->address.host = packet->address.host;	
			packets->address.port = packet->address.port;

			packets->data = "da";
			packets->len = strlen((char *)packets->data) + 1;

			SDLNet_UDP_Send(client, -1, packets); /* This sets the p->channel */


		}
	}

	SDLNet_UDP_Close(server);
	return 0;
}