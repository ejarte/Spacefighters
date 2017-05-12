//----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------------------------
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_net.h"
#include "UDP.h"
#include "definitions.h"

//----------------------------------------------------------------------
int UDP()
{
	printf("UDP\n");


	IPaddress adrs[4];
	int i = 0;
	int k = 0;
	int objOne[3];
	int objTwo[3];
	int objThree[3];
	int objFour[3];

	struct Object spaceship[4];

	

	adrs[0].port = 0;
	adrs[1].port = 0;
	adrs[2].port = 0;
	adrs[3].port = 0;

	IPaddress ip;
	UDPsocket server;
	UDPsocket client;
	UDPpacket *packet;
	UDPpacket *packets;

	server = SDLNet_UDP_Open(1234);
	client = SDLNet_UDP_Open(0);

	packet = SDLNet_AllocPacket(1024);
	packets = SDLNet_AllocPacket(1024);

	char hold[1000];

	while (1)
	{
		/* Wait a packet. UDP_Recv returns != 0 if a packet is coming */
		//SDL_Delay(1000);
		if (SDLNet_UDP_Recv(server, packet))
		{
			/*
			printf("UDP Packet incoming\n");
			printf("\tChan:    %d\n", packet->channel);
			printf("\tData:    %s\n", (char *)packet->data);
			printf("\tLen:     %d\n", packet->len);
			printf("\tMaxlen:  %d\n", packet->maxlen);
			printf("\tStatus:  %d\n", packet->status);
			printf("\tAddress: %x %x\n", packet->address.host, packet->address.port);
			*/



			//gives each adress a unique place in adrs
			if ((adrs[i].port == 0x00) && (packet->address.port != adrs[0].port) && (packet->address.port != adrs[1].port) && (packet->address.port != adrs[2].port) && (packet->address.port != adrs[3].port))
			{
				adrs[i] = packet->address;
				printf("Saved port: %x to %d\n", adrs[i].port, i);
				i++;
			}
			if (i == 0) {
				printf("nothing has connected yet");
			}
			if (i == 1) {//One
				sscanf(packet->data, "%d %d %d", &spaceship[0].speed_x, &spaceship[0].speed_y, &spaceship[0].speed_max);
				printf("\nData Recieved: %d %d %d\n", spaceship[0].speed_x, spaceship[0].speed_y, spaceship[0].speed_max);
			}
			if (i == 2) {//Two
				sscanf(packet->data, "%d %d %d", &spaceship[1].speed_x, &spaceship[1].speed_y, &spaceship[1].speed_max);
				printf("\nData Recieved: %d %d %d\n", spaceship[1].speed_x, spaceship[1].speed_y, spaceship[1].speed_max);
			}

			if (i == 3) {//Three
				sscanf(packet->data, "%d %d %d", &spaceship[2].speed_x, &spaceship[2].speed_y, &spaceship[2].speed_max);
				printf("\nData Recieved: %d %d %d\n", spaceship[2].speed_x, spaceship[2].speed_y, spaceship[2].speed_max);
			}

			if (i == 4) {//Four
				sscanf(packet->data, "%d %d %d", &spaceship[3].speed_x, &spaceship[3].speed_y, &spaceship[3].speed_max);
				printf("\nData Recieved: %d %d %d\n", spaceship[3].speed_x, spaceship[3].speed_y, spaceship[3].speed_max);
			}


			/*

			Här kan man ändra på data som ska skickas tillbaka

			*/
			//tex 
			//objOne[0] = objOne[0] + 1;
			if (i == 1) {//One
				sprintf(hold, "%d %d %d", spaceship[0].speed_x, spaceship[0].speed_y, spaceship[0].speed_max);
				packets->data = hold;
				printf(hold);
			}
			if (i == 2) {//Two
				sprintf(hold, "%d %d %d", spaceship[1].speed_x, spaceship[1].speed_y, spaceship[1].speed_max);
				packets->data = hold;
			}
			if (i == 3) {//Three
				sprintf(hold, "%d %d %d", spaceship[2].speed_x, spaceship[2].speed_y, spaceship[2].speed_max);
				packets->data = hold;
			}
			if (i == 4) {//Four
				sprintf(hold, "%d %d %d", spaceship[3].speed_x, spaceship[3].speed_y, spaceship[0].speed_max);
				packets->data = hold;
			}
			//detta skickar med ipadressen som kom
			packets->address.host = packet->address.host;
			packets->address.port = packet->address.port;
			//scanf(&packet->data);


			packets->len = strlen((char *)packets->data) + 1;

			SDLNet_UDP_Send(client, -1, packets); /* This sets the p->channel */
												  /* not necesarry since we never use more than 5 players
												  if (i == 4) {
												  i = 0;
												  }*/
		}
	}

	SDLNet_UDP_Close(server);
	return 0;
}