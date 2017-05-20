#pragma once
#include "SDL.h"
#include "SDL_net.h"
#include <stdio.h>
#include <string.h>

#define TCP_SERVER_PORT		1337				// The port our server will listen to
#define BUFFER_SIZE			1024				// size of messsage buffer
#define MAX_SOCKETS			5					// Max number of sockets
#define MAX_CLIENTS			4					// Max number of clients

// keys to send back to the client to identify what type of TCP packet it is and how to read it
#define SERVER_NOT_FULL		70					
#define SEVER_FULL			71
#define PLAYER_ID			72

struct Server {
	IPaddress ip;
	TCPsocket tcp_s;
	TCPsocket tcp_s_client[MAX_CLIENTS];
	bool tcp_socket_free[MAX_CLIENTS];
};

struct Server server;

char buffer[BUFFER_SIZE];
int recievedByteCount_tcp; 
bool shutdownServer; 

int tcp_2()
{
	shutdownServer = false;
	recievedByteCount_tcp = 0;

	if (SDLNet_Init() == -1) {
		printf("Failed to initialize SDL_net: %s\n", SDLNet_GetError());
		exit(-1);
	}
	// Create a socket set with enough sockets to store our desired number of connections
	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(MAX_SOCKETS);
	if (socketSet == NULL) {
		printf("Failed to allocate the socket set: %s\n", SDLNet_GetError());
		exit(-1);
	} else {
		printf("Allocated socket set with size: %d of which %d are available for use by clients\n", MAX_SOCKETS, MAX_CLIENTS);
	}
	// Initialize all the client sockets
	for (int i = 0; i < MAX_CLIENTS; i++) {
		server.tcp_s_client[i] = NULL;
		server.tcp_socket_free[i] = true;
	}

	int hostResolved = SDLNet_ResolveHost(&server.ip, NULL, TCP_SERVER_PORT);
	if (hostResolved == -1) {
		printf("Failed to resolve the server host: %s\n", SDLNet_GetError());
	}
	else 
	{
		Uint8 * dotQuad = (Uint8*)&server.ip.host;
		printf("Succesfully resolved server host to IP: %d.%d.%d.%d, port: %d\n", (unsigned short)dotQuad[0], (unsigned short)dotQuad[1], (unsigned short)dotQuad[2], (unsigned short)dotQuad[3], server.ip.port);
	}
	// Try to open the server socket
	server.tcp_s = SDLNet_TCP_Open(&server.ip);
	if(!server.tcp_s)
	{
		printf("Failed to open server socket: %s\n", SDLNet_GetError());
		exit(-1);
	}
	else {
		printf("Succesfully created server socket.\n");
	}
	SDLNet_TCP_AddSocket(socketSet, server.tcp_s);

	printf("Awaiting clients...\n");

	while (shutdownServer == false) {

	}
}