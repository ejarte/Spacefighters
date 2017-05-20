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

void TCP_broadcastPlayerConnected(int connecting_id)
{
	char number = connecting_id + 48;
	s.tcp_buffer[0] = '\0';
	strcpy(s.tcp_buffer, MSG_PLAYER_CONNECTED);
	s.tcp_len = strlen(s.tcp_buffer);
	s.tcp_buffer[s.tcp_len] = number;
	s.tcp_buffer[s.tcp_len + 1] = '\0';
	s.tcp_len = strlen(s.tcp_buffer) + 1;
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (c[i].tcp_socket_is_free == false) {
			if (SDLNet_TCP_Send(c[i].tcp_socket, (void *)s.tcp_buffer, s.tcp_len) < s.tcp_len) {
				printf("Failed to send player connected: %s\n", SDLNet_GetError());
			}
		}
	}
}

void TCP_broadcastPlayerDisconected(int connecting_id)
{
	char number = connecting_id + 48;
	s.tcp_buffer[0] = '\0';
	strcpy(s.tcp_buffer, MSG_PLAYER_DISCONNECTED);
	s.tcp_len = strlen(s.tcp_buffer);
	s.tcp_buffer[s.tcp_len] = number;
	s.tcp_buffer[s.tcp_len + 1] = '\0';
	s.tcp_len = strlen(s.tcp_buffer) + 1;
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (c[i].tcp_socket_is_free == false) {
			if (SDLNet_TCP_Send(c[i].tcp_socket, (void *)s.tcp_buffer, s.tcp_len) < s.tcp_len) {
				printf("Failed to send player disconnected: %s\n", SDLNet_GetError());
			}
		}
	}
}

void TCP_broadcastPlayerChatMsg(int sender_id, char *msg) 
{
	s.tcp_len = strlen(s.tcp_buffer) + 1;
	for (int i = 0; i < MAX_CLIENTS; i++) {
		// if socket is available send the message
		if (c[i].tcp_socket_is_free == false) {	
			if (SDLNet_TCP_Send(c[i].tcp_socket, (void *)s.tcp_buffer, s.tcp_len) < s.tcp_len) {
				printf("Failed to send chat: %s\n", SDLNet_GetError());
			}
		}
	}
}

void TCP_broadcastPlayerNameChange()
{
	s.tcp_len = strlen(s.tcp_buffer) + 1;
	for (int i = 0; i < MAX_CLIENTS; i++) {
		// if socket is available send the message
		if (c[i].tcp_socket_is_free == false) {
			if (SDLNet_TCP_Send(c[i].tcp_socket, (void *)s.tcp_buffer, s.tcp_len) < s.tcp_len) {
				printf("Failed to send name change: %s\n", SDLNet_GetError());
			}
		}
	}
}

void TCP_broadcastPlayerDataRecieved()
{
	s.tcp_len = strlen(s.tcp_buffer) + 1;
	for (int i = 0; i < MAX_CLIENTS; i++) {
		// if socket is available send the message
		if (c[i].tcp_socket_is_free == false) {
			if (SDLNet_TCP_Send(c[i].tcp_socket, (void *)s.tcp_buffer, s.tcp_len) < s.tcp_len) {
				printf("Failed to send player data: %s\n", SDLNet_GetError());
			}
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

	/*
	// Unstable part of code
	char* host = SDLNet_ResolveIP(&s.ip);

	if (host == NULL)
	{
		printf("Failed to resolve the server IP address: %s.\n", SDLNet_GetError());
	}
	else
	{
		printf("Succesfully resolved server host: %s\n", host);
	}
	// End of ustable part of code
	*/

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

					printf("TCP_Recieved: %s (from client %d).\n", s.tcp_buffer, i);

					// Send back player number
					if (strncmp(MSG_CLIENT_NUM, s.tcp_buffer, 3) == 0) {
						TCP_sendClientNumber(i);
					}
					else if (strncmp(MSG_CHAT_MSG, s.tcp_buffer, 3) == 0) {
						TCP_broadcastPlayerChatMsg(i, s.tcp_buffer);
					}
					else if (strncmp(MSG_CHANGE_NAME, s.tcp_buffer, 3) == 0) {
						TCP_broadcastPlayerNameChange();
					}
					else if (strncmp(s.tcp_buffer, MSG_SHUTDOWN_SERVER, 3) == 0) {
						s.running = false;
						printf("Shuting down server...\n");
					}

					else if (strncmp(s.tcp_buffer, MSG_PLAYER_ACTIONS, 4) == 0) {
						TCP_broadcastPlayerDataRecieved();
					}
				}
			}
		} // end of client loop

		num_spawned_neutral_obj = 0;

		// Generates neutral objects when ready
		generateNeutralObjects();	

	}
	// Free our socket set 
	SDLNet_FreeSocketSet(socketSet);
	SDLNet_TCP_Close(s.tcp_socket);
	SDLNet_Quit();
	return 0;
}



/*
void TCP_sendPlayerActions(int pId)
{
	char data[100];
	server.tcp_buffer[0] = '\0';
	strcpy(server.tcp_buffer, MSG_PLAYER_ACTIONS);
	sprintf(
		data, "%d %d %d %d %d %d %d %d", 
		pId,
		mouseEventHeld(SDL_BUTTON_LEFT),
		keyEventHeld(SDL_SCANCODE_W),
		keyEventHeld(SDL_SCANCODE_A),
		keyEventHeld(SDL_SCANCODE_S),
		keyEventHeld(SDL_SCANCODE_D),
		getMouseX(),
		getMouseY()
	);
	strcat(server.tcp_buffer, data);
	int len = strlen(server.tcp_buffer) + 1;
	if (SDLNet_TCP_Send(client.tcp_socket, (void *)server.tcp_buffer, len) < len) {
		return -1;	// failed to send a message
	}
}
*/


//#include "TCP.h"
//#include "UDP.h"

// --------------------------------------------
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

void createDemon(int id, const char * function, void(*f)(int)) //spelarens id, namnet på funktionen, själva funktionen
{
	SDL_Thread *TCPThread = NULL;
	printf("ID %d \n", id);
	TCPThread = SDL_CreateThread(f, function, id);

	if (NULL == TCPThread) {
		printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
	}
	else {
		printf("\nYou've created a demon, you monster!\n");
	}
}

void createThread(const char * function, void(*f)(int)) //namnet på funktionen, själva funktionen
{
	SDL_Thread *TCPThread = NULL;
	TCPThread = SDL_CreateThread(f, function, NULL);

	if (NULL == TCPThread) {
		printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
	}
	else {
		printf("\nYou've created a demon, you monster!\n");
	}
}

/*

int main()
{
	//TODO snygga till koden, ta bort onödigt och namnge bättre
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();	

	init_logic();

	//UDP();
	player_id = 1;
	broadCast = false;

	//UDP tråd
	SDL_Thread *UDPThread;
	const char *UDPThreadReturnValue;
	UDPThread = SDL_CreateThread(UDP, "UDP", "127.0.0.1");

	if (NULL == UDPThread) {
		printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
	}
	//UDP Tråd


	TCP();
	SDL_WaitThread(UDP, UDPThreadReturnValue);

	SDLNet_Quit();
	SDL_Quit();
	return 0;
}
*/