#include "SDL.h"
#include "SDL_net.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "definitions.h"
#include "logic.h"

void TCP_sendClientNumber(int i) 
{
	char number = i + 48;
	s.tcp_buffer[0] = '\0';
	strcpy(s.tcp_buffer, MSG_CLIENT_NUM);
	s.tcp_len = strlen(s.tcp_buffer);
	s.tcp_buffer[s.tcp_len] = number;
	s.tcp_buffer[s.tcp_len + 1] = '\0';
	s.tcp_len = strlen(s.tcp_buffer) + 1;
	SDLNet_TCP_Send(c[i].tcp_socket, (void *)s.tcp_buffer, s.tcp_len);
}

void TCP_broadcast()
{
	s.tcp_len = strlen(s.tcp_buffer) + 1;
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (c[i].tcp_socket_is_free == false) {
			if (SDLNet_TCP_Send(c[i].tcp_socket, (void *)s.tcp_buffer, s.tcp_len) < s.tcp_len) {
				printf("Failed to send player connected: %s\n", SDLNet_GetError());
			}
		}
	}
}

void TCP_broadcastPlayerConnected(int connecting_id)
{
	char number = connecting_id + 48;
	s.tcp_buffer[0] = '\0';
	strcpy(s.tcp_buffer, MSG_PLAYER_CONNECTED);
	s.tcp_len = strlen(s.tcp_buffer);
	s.tcp_buffer[s.tcp_len] = number;
	s.tcp_buffer[s.tcp_len + 1] = '\0';
	TCP_broadcast();
}

void TCP_broadcastPlayerDisconected(int connecting_id)
{
	char number = connecting_id + 48;
	s.tcp_buffer[0] = '\0';
	strcpy(s.tcp_buffer, MSG_PLAYER_DISCONNECTED);
	s.tcp_len = strlen(s.tcp_buffer);
	s.tcp_buffer[s.tcp_len] = number;
	s.tcp_buffer[s.tcp_len + 1] = '\0';
	TCP_broadcast();
}

void TCP_broadcastPlayerChatMsg(int sender_id, char *msg) 
{
	printf("Message send: %s\n", s.tcp_buffer);
	TCP_broadcast();
}

void TCP_broadcastPlayerNameChange()
{
	TCP_broadcast();
}

void TCP_broadcastPlayerDataRecieved()
{
	TCP_broadcast();
}

void timerToStart(char * tcpHead, int senderId)
{
	int currTime = SDL_GetTicks();
	int timeToS = 3;

	memset(s.tcp_buffer, 0, strlen(s.tcp_buffer));
	sprintf(s.tcp_buffer, "%s%d....", tcpHead, timeToS);
	TCP_broadcastPlayerChatMsg(senderId, s.tcp_buffer);

	while (timeToS != 0)
	{
		if ((SDL_GetTicks() - currTime) == 2000 && timeToS == 2)
		{
			timeToS = 1;
			printf("2...\n");
			memset(s.tcp_buffer, 0, strlen(s.tcp_buffer));
			sprintf(s.tcp_buffer, "%s%d....", tcpHead, timeToS);
			TCP_broadcastPlayerChatMsg(senderId, s.tcp_buffer);
		} else if ((SDL_GetTicks() - currTime) == 1000 && timeToS == 3)
		{
			timeToS = 2;
			printf("1...\n");
			memset(s.tcp_buffer, 0, strlen(s.tcp_buffer));
			sprintf(s.tcp_buffer, "%s%d....", tcpHead, timeToS);
			TCP_broadcastPlayerChatMsg(senderId, s.tcp_buffer);
		}
		else if ((SDL_GetTicks() - currTime) == 3000)
		{	
			timeToS = 0;
			printf("0...\n");
			memset(s.tcp_buffer, 0, strlen(s.tcp_buffer));
			sprintf(s.tcp_buffer, "%s-start", tcpHead);
			TCP_broadcastPlayerChatMsg(senderId, s.tcp_buffer);
		}
	}
}

int main(int argc, char **argv)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL_Init: %s\n", SDL_GetError());
		return -1;
	}
	if (SDLNet_Init() < 0)
	{
		printf("SDLNet_Init: %s\n", SDLNet_GetError());
		return -1;
	}

	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(MAX_SOCKETS);
	if (socketSet == NULL) {
		printf("Failed to allocate socket set: %s", SDLNet_GetError());
		return -1;
	} 
	else printf("Allocated socket set with size: %d of which %d are available.\n", MAX_SOCKETS, MAX_CLIENTS);

	for (int i = 0; i < MAX_CLIENTS; i++) {
		c[i].tcp_socket = NULL;
		c[i].tcp_socket_is_free = true;
	}

	s.tcp_recv_byteCount = 0;

	Uint16 serverPort = SERVER_PORT;
	if (SDLNet_ResolveHost(&s.ip, NULL, serverPort) == -1) {
		printf("Failed to resolve the server host: %s", SDLNet_GetError);
	}
	else {
		Uint8 * dotQuad = (Uint8*)&s.ip.host;
		printf("Succesfully resolved the server host: %d.%d.%d.%d.\n", (unsigned short)dotQuad[0], (unsigned short)dotQuad[1], (unsigned short)dotQuad[2], (unsigned short)dotQuad[3]);
		printf("Port: %d\n", SDLNet_Read16(&s.ip.port));
	}

	s.tcp_socket = SDLNet_TCP_Open(&s.ip);
	if (!s.tcp_socket) {
		printf("Failed to open server socket: %s", SDLNet_GetError());
	}
	else printf("Succesfully opened TCP server socket.\n");

	// Add our server socket ot the socket set.
	SDLNet_TCP_AddSocket(socketSet, s.tcp_socket);

	init_logic();

	printf("Awaiting clients...\n");

	int numActiveSockets = 0;
	int clientCount = 0;
	s.running = true;

	
	while (s.running) {
		numActiveSockets = SDLNet_CheckSockets(socketSet, 0);	// Not necessary

		// if a client has transmitted any data
		if (SDLNet_SocketReady(s.tcp_socket) != 0) {
			
			printf("A client is ready to transmit data...\n");

			if (clientCount < MAX_CLIENTS) {

				// Find first free socket in our array of client sockets
				for (int i = 0; i < MAX_CLIENTS; i++) {
					if (c[i].tcp_socket_is_free) {
						c[i].tcp_socket_is_free = false;

						c[i].tcp_socket = SDLNet_TCP_Accept(s.tcp_socket);			// Accept connection
						SDLNet_TCP_AddSocket(socketSet, c[i].tcp_socket);			// Add client to socket set
						clientCount++;												// Increase client count
						
						// Send a message to client that server is not full
						strcpy(s.tcp_buffer, MSG_SERVER_NOT_FULL);
						s.tcp_len = strlen(s.tcp_buffer) + 1;
						SDLNet_TCP_Send(c[i].tcp_socket, (void *)s.tcp_buffer, s.tcp_len);
						printf("Client %d connected. There are now %d clients.\n", i, clientCount);
						TCP_broadcastPlayerConnected(i);
						break;
					}
				}
			}
			else {	// if we don't have room on server
				printf("Maximum client count reached - rejecting client connection.\n");
				TCPsocket tmpSocket = SDLNet_TCP_Accept(s.tcp_socket);			// Accept connection

				// Send a message to client that server is full
				strcpy(s.tcp_buffer, MSG_SERVER_FULL);
				s.tcp_len = strlen(s.tcp_buffer) + 1;
				SDLNet_TCP_Send(tmpSocket, (void *)s.tcp_buffer, s.tcp_len);
				// Shutdown, disconnect and close the socket to the client
				SDLNet_TCP_Close(tmpSocket);
			}
		}	// end of SDLNet_SocketReady

		// Loop to check all possible clients for activity 
		for (int i = 0; i < MAX_CLIENTS; i++) {

			// If there is any activity on the client socket...
			if (SDLNet_SocketReady(c[i].tcp_socket) != 0) {

				// If there's activity, but we didn't read anything from the client socket, then the client has disconnected...
				if (SDLNet_TCP_Recv(c[i].tcp_socket, s.tcp_buffer, BUFFER_SIZE) <= 0) {
					TCP_broadcastPlayerDisconected(i);
					// Remove the socket from the socket set, then close and reset the socket ready for re-use and free up the slot
					SDLNet_TCP_DelSocket(socketSet, c[i].tcp_socket);
					SDLNet_TCP_Close(c[i].tcp_socket);
					c[i].tcp_socket = NULL;
					c[i].tcp_socket_is_free = true;
					clientCount--;
					printf("Client %d disconnected. There are now %d clients.\n", i, clientCount);
				}
				else {	// if we read data from the client socket

					// Send back player number
					if (strncmp(MSG_CLIENT_NUM, s.tcp_buffer, 3) == 0) {
						TCP_sendClientNumber(i);
					}
					else if ((strncmp(MSG_CHAT_MSG, s.tcp_buffer, 3) == 0) && startTimer == false) {
						strncpy(tempMSG, s.tcp_buffer + 5, strlen(s.tcp_buffer));
						if (strcmp(tempMSG, "-start") == 0)
						{
							memset(tempMSG, 0, strlen(tempMSG));
							strncpy(tempMSG, s.tcp_buffer, 5);

							if (clientCount <= 0)
							{
								sprintf(s.tcp_buffer, "%s %d more players have to connect before you can start the game!", tempMSG, 4- clientCount);
							} else
							{
								startTimer = true;
								timerToStart(tempMSG, i);
								startTimer = false;
							}
						}
						else
						{
							TCP_broadcastPlayerChatMsg(i, s.tcp_buffer);
						}
					}
					else if (strncmp(MSG_CHANGE_NAME, s.tcp_buffer, 3) == 0) {
						TCP_broadcastPlayerNameChange();
					}
					else if (strncmp(s.tcp_buffer, MSG_SHUTDOWN_SERVER, 3) == 0) {
						s.running = false;
						printf("Shutting down server...\n");
					}

					// Player movement related
					else if (strncmp(s.tcp_buffer, MSG_PLAYER_ACTIONS, 4) == 0) {
						TCP_broadcastPlayerDataRecieved();
					}
					else {
						// broadcast recieved message
						TCP_broadcast();
					}
				}
			}
		} // end of client loop

		num_spawned_neutral_obj = 0;

		// Generates neutral objects when ready
		generateNeutralObjects();	

		// Send object data
		/*
		for (int i = 0; i < MAX_PLAYERS; i++) {
			sprintf(s.tcp_buffer, "%s %d %d %d", SERVER_OBJECTS, object[i].pos.x, object[i].pos.y, object[i].facing);
			TCP_broadcast();
		}
		*/
	}
	// Free our socket set 
	SDLNet_FreeSocketSet(socketSet);
	SDLNet_TCP_Close(s.tcp_socket);
	SDLNet_Quit();
	return 0;
}
