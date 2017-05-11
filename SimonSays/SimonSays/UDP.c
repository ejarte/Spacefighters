#include <SDL.h>
#include <SDL_net.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <definition.h>
#include <object.h>
#include <math.h>

#include "UDP.h"

double my_round(double x, unsigned int digits) {
	double fac = pow(10, 12);
	return round(x*fac) / fac;
}

int UDP(int ipNr)
{
	printf("UDP\n");



	IPaddress ip;
	UDPsocket server;
	UDPsocket client;
	UDPpacket *packets;
	UDPpacket *packetr;
	//write "127.0.0.1",1234 to connect to the server.cpp on your local machine

	server = SDLNet_UDP_Open(0); //kan va 1123 men bör inte va de //send
	client = SDLNet_UDP_Open(1234);//recieve

	SDLNet_ResolveHost(&ip, ipNr, 1234);

	packets = SDLNet_AllocPacket(1024);
	packetr = SDLNet_AllocPacket(1024);

	char hold[100];

	//printf("\n\n%d\n\n", hold[0]);

	//packet->address = ip;
	
	//packets->data = "%f",object[0].speed_x;

	
	


	//printf("\n%d\n",sizeof(hold));
	while (1)
	{
		sprintf(hold, "%d %d %d", (int)object[1].speed_x, (int)object[1].speed_y, (int)object[1].facing);
		printf("\nData Sent: ");
		printf(hold);
		printf("\n");
		packets->data = hold;

		SDL_Delay(1000);
		//printf("%c", packets->data);
		//detta skickar
		packets->address.host = ip.host;	/* Set the destination host */
		packets->address.port = ip.port;	/* And destination port */

		//packets->len = strlen((char *)packets->data) + 1;
		packets->len = sizeof(int) + 1;

		SDLNet_UDP_Send(server, -1, packets); 
											  //detta är altså den som tar emot
		if (SDLNet_UDP_Recv(server, packetr))
		{
			/*
			printf("UDP Packet incoming\n");
			printf("\tChan:    %d\n", packetr->channel);
			printf("\tData:    %s\n", (char *)packetr->data);
			printf("\tLen:     %d\n", packetr->len);
			printf("\tMaxlen:  %d\n", packetr->maxlen);
			printf("\tStatus:  %d\n", packetr->status);
			printf("\tAddress: %x %x\n", packetr->address.host, packetr->address.port);
			*/
			sscanf(packetr->data, "%f %f %f", &object[1].speed_x, &object[1].speed_y, &object[1].facing);
			printf("\nData recieved: %f %f %f\n", object[1].speed_x, object[1].speed_y, object[1].facing);
		}
	}

		


	SDLNet_UDP_Close(server);


	return 0;
}