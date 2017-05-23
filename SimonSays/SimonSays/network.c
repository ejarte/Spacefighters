/*	Author(s):	Jacob Ekedahl, Tiago Redaelli, Hampus Hauffman
*	Modified:	09-05-14
*	Version:	0.3
*
*	Changelog
*	0.1 Hampus
*	- Created files for basic TCP.c and UDP.c
*	0.2 Jacob
*	- Worked on TCP.c and added chat functionality, resolve client id and connection/disconnection
*	0.3 Tiago
*	- Added string input for connection and validation of ip and port strings
*	- Removed host = SDL_NetResolveIP(...) which was unstable and some times crashed.
*	- Merged the TCP and UDP files into one
*	- Now only has one thread to listen to server messages for TCP
*	- No longer uses multiple threads to send TCP messages to server (might be a misstake)
*	- Sends disconnect and connect messages from server
*	- Spawns neutral objects from server
*	(- Players can change their names - NOT COMPLETE)
*	(- Added a command to shutdown the server - NOT COMPLETE)
*/


#include "network.h"
#include "definition.h"
#include "game.h"
#include "text_messages.h"

char ip_substr[30][30];

// Validates the string as a IPv4 address and sets a pointer to the IP address

bool validateIPv4Entry(char* str, Uint32* ipaddr)
{
	Uint8 byte[4];
	for (int i = 0; i < 30; i++) {
		ip_substr[i][0] = '\0';
	}
	int min, max, k;
	min = 0;
	k = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		max = i;
		if (!(isDigit(str[i]) || str[i] == '.')) {
			return false;
		}
		if (str[i] == '.') {
			if (i - min > 3) {
				return false;
			}
			else {
				strcpy(ip_substr[k], substring(str, min, max));
				byte[k] = atoi(ip_substr[k]);
				min = i + 1;
				k++;
			}
		}
	}
	if (k == 3) {
		max += 1;
		strcpy(ip_substr[k], substring(str, min, max));
		byte[k] = atoi(ip_substr[k]);
		for (int i = 0; i < 4; i++) {
			k = atoi(ip_substr[i]);
			if (k < 0 || k > 255) {
				return false;
			}
		}
		(*ipaddr) = byte[3] << 24 | byte[2] << 16 | byte[1] << 8 | byte[0];		// sets pointer to a the matching bytes through bit operations
		return true;
	}
	return false;
}

// Validates the string and sets a Uint16 pointer to the port

bool validatePortEntry(char* str, Uint16* port)
{
	for (int i = 0; str[i] != '\0'; i++) {
		if (!isDigit(str[i])) {
			return false;
		}
	}
	*port = atoi(str);
	return true;
}

// Prints out the ip address 

void printIpInfo(IPaddress* ip)
{
	Uint8 byte[4];
	Uint32 ip_adr = ip->host;
	Uint8 *p = (Uint8 *)&ip_adr;
	byte[0] = p[0];
	byte[1] = p[1];
	byte[2] = p[2];
	byte[3] = p[3];
	printf("IP: %d.%d.%d.%d\n", byte[0], byte[1], byte[2], byte[3]);
}

//======================================================================================================================

#define BUFFER_SIZE				1024

#define MSG_SERVER_NOT_FULL		"#1#"
#define MSG_SERVER_FULL			"#2#"
#define MSG_CLIENT_NUM			"#3#"
#define MSG_CHAT_MSG			"#4#"
#define MSG_PLAYER_CONNECTED	"#5#"
#define MSG_PLAYER_DISCONNECTED	"#6#"
#define MSG_SHUTDOWN_SERVER		"#7#"
#define MSG_CHANGE_NAME			"#8#"
#define MSG_NEUTRAL_OBJ			"#9#"
#define MSG_PLAYER_ACTIONS		"#10#"
#define MSG_START_GAME			"#11#"

struct Client_t {
	bool shutdown;
	TCPsocket tcp_socket;
};

struct Server_t {
	IPaddress ip;	// Server IP address
	int tcp_byte_count;
	char tcp_buffer[BUFFER_SIZE];
};

struct Client_t client;
struct Server_t server;

SDLNet_SocketSet tcp_socketSet;


struct RecvPlayerActions playerActions[MAX_PLAYERS];

char data[100];
void TCP_listen() 
{
	int playerId;
	char* substr;

	printf("Now listening to TCP messages.\n");
	while (run_program) {
		if (SDLNet_CheckSockets(tcp_socketSet, 0) != 0) {
			if (SDLNet_SocketReady(client.tcp_socket) != 0) {

				// Recieve message
				server.tcp_byte_count = SDLNet_TCP_Recv(client.tcp_socket, server.tcp_buffer, BUFFER_SIZE);
				printf("TCP_Recv: %s\n", server.tcp_buffer);

				// Connection message

				if (strncmp(MSG_PLAYER_CONNECTED, server.tcp_buffer, 3) == 0 && startTheGame == true) {		
					playerId = server.tcp_buffer[3] - 48;
					addPlayerEmoteMessageToDisplay(renderer, playerId, "has connected.", MSG_DURATION);
					printf("%d has connected to the game.\n");
				}

				// Disconnection Message
				else if (strncmp(MSG_PLAYER_DISCONNECTED, server.tcp_buffer, 3) == 0 && startTheGame == true) {
					playerId = server.tcp_buffer[3] - 48;
					addPlayerEmoteMessageToDisplay(renderer, playerId, "has disconnected.", MSG_DURATION);
					printf("%d has disconnected from the game.\n");
				}

				// Player chat message
				else if (strncmp(MSG_CHAT_MSG, server.tcp_buffer, 3) == 0) {
					playerId = server.tcp_buffer[3] - 48;
					substr = substring(server.tcp_buffer, 5, server.tcp_byte_count - 1);
					addPlayerMessageToDisplay(renderer, playerId, substr, MSG_DURATION);
					printf("chat message recieved from player %d: %s\n", playerId, substr);
					if (strcmp(substr, "-start") == 0)
					{
						startTheGame = true;
						printf("TEST");
					}
					else if (strncmp(substr, "has killed player ", 15) == 0)
					{
						int idDeath;
						idDeath = substr[18] - 48;
						printf("death id: %d", idDeath);
						recievedShipDeath(idDeath);
					}
				}

				// Request name change
				else if (strncmp(MSG_CHANGE_NAME, server.tcp_buffer, 3) == 0 && startTheGame == true) {
					playerId = server.tcp_buffer[3] - 48;
					substr = substring(server.tcp_buffer, 5, server.tcp_byte_count - 1);
					player[playerId].name[0] = '\0';
					strcpy(player[playerId].name, substr);
					addPlayerEmoteMessageToDisplay(renderer, playerId, " changed name.", MSG_DURATION);
					switch (playerId) {
						case 0: interface_setup_label(&playerNameLabel[0], renderer, substr, font_roboto_black, createColor(0xFF, 0, 0, 0), 100, 100, true); 
								interface_attach_label(&playerNameLabel[0], player[0].spaceship->ptr_center_x, player[0].spaceship->ptr_center_y, -50, -50);
								break;
						case 1: interface_setup_label(&playerNameLabel[1], renderer, substr, font_roboto_black, createColor(0, 0, 0xFF, 0), 800, 100, true);
								interface_attach_label(&playerNameLabel[1], player[1].spaceship->ptr_center_x, player[1].spaceship->ptr_center_y, -50, -50);
								break;
						
						case 2: interface_setup_label(&playerNameLabel[2], renderer, substr, font_roboto_black, createColor(0, 0xFF, 0, 0), 100, 800, true);
								interface_attach_label(&playerNameLabel[2], player[2].spaceship->ptr_center_x, player[2].spaceship->ptr_center_y, -50, -50);
								break;
						case 3: interface_setup_label(&playerNameLabel[3], renderer, substr, font_roboto_black, createColor(0xFF, 0x78, 0x1C, 0), 800, 600, true);
								interface_attach_label(&playerNameLabel[3], player[3].spaceship->ptr_center_x, player[3].spaceship->ptr_center_y, -50, -50);
								break;
						default:	break;
					}
				}

				// Spawn Neutral Objects
				else if (strncmp(MSG_NEUTRAL_OBJ, server.tcp_buffer, 3) == 0 && startTheGame == true) {
					SDL_Point p;
					int dx, dy, facing, obj_type;
					substr = substring(server.tcp_buffer, 3, server.tcp_byte_count - 1);
					sscanf(substr, "%d %d %d %d %d %d %d", &obj_type, &p.x, &p.y, &dx, &dy, &facing);
					world_spawnNeutralObject(obj_type, p, dx, dy, facing);
				}

				// Record other player actions
				else if (strncmp(MSG_PLAYER_ACTIONS, server.tcp_buffer, 4) == 0 &&  startTheGame == true) {
					int i;
					
					//char* str = malloc(sizeof(200));
					substr = substring(server.tcp_buffer, 5, server.tcp_byte_count);

					//substring(str, 5, server.tcp_byte_count - 1);

					//substring(server.tcp_buffer, 5, server.tcp_byte_count - 1);
					//printf("%s\n", substr);

					//sscanf(substr, "%d", &i);
					sscanf(substr, "%d", &i);
					sscanf(substr, "%d %d %d %d %d %d %d %d", &playerId,
						&playerActions[i].shoot,
						&playerActions[i].w,
						&playerActions[i].a,
						&playerActions[i].s,
						&playerActions[i].d,
						&playerActions[i].mx,
						&playerActions[i].my);
				}
				else
				{
					printf("Other message recieved: %s\n", server.tcp_buffer);
				}

			}
		}
	}
}

void TCP_sendPlayerActions(int pId)
{
	data[0] = '\0';
	server.tcp_buffer[0] = '\0';
	strcpy(server.tcp_buffer, MSG_PLAYER_ACTIONS);
	sprintf(
		data, " %d %d %d %d %d %d %d %d", 
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

void TCP_sendStart()
{
	server.tcp_buffer[0] = '\0';
	strcpy(server.tcp_buffer, MSG_START_GAME);
	strcat(server.tcp_buffer, "*#");
	strcat(server.tcp_buffer, "1");
	server.tcp_buffer[3] = client_player_num + 48;
	int len = strlen(server.tcp_buffer) + 1;
	if (SDLNet_TCP_Send(client.tcp_socket, (void *)server.tcp_buffer, len) < len) {
		return -1;	// failed to send a message
	}
}

void TCP_sendNameChange(char* name)
{
	server.tcp_buffer[0] = '\0';
	strcpy(server.tcp_buffer, MSG_CHANGE_NAME);
	strcat(server.tcp_buffer, "*#");
	strcat(server.tcp_buffer, name);
	server.tcp_buffer[3] = client_player_num + 48;
	int len = strlen(server.tcp_buffer) + 1;
	if (SDLNet_TCP_Send(client.tcp_socket, (void *)server.tcp_buffer, len) < len) {
		return -1;	// failed to send a message
	}
}

void TCP_sendChatMsg(char* msg)
{
	server.tcp_buffer[0] = '\0';
	strcpy(server.tcp_buffer, MSG_CHAT_MSG);
	strcat(server.tcp_buffer, "*#");
	strcat(server.tcp_buffer, msg);
	server.tcp_buffer[3] = client_player_num + 48;
	int len = strlen(server.tcp_buffer) + 1;
	if (SDLNet_TCP_Send(client.tcp_socket, (void *)server.tcp_buffer, len) < len) {
		return -1;	// failed to send a message
	}
}

int requestPlayerId()
{
	int time = SDL_GetTicks() + 3000;	// 3 seconds wait for response time
	int len;
	// Send a message to request a player id from the server
	strcpy(server.tcp_buffer, MSG_CLIENT_NUM);
	len = strlen(server.tcp_buffer) + 1;
	if (SDLNet_TCP_Send(client.tcp_socket, (void *)server.tcp_buffer, len) < len) {
		return -1;	// failed to send a message
	}
	while (time > SDL_GetTicks()) {
		// Check our socketset for activity
		if (SDLNet_CheckSockets(tcp_socketSet, 0) != 0) {
			// check for response from server
			if (SDLNet_SocketReady(client.tcp_socket) != 0) {									// On recieve
				len = SDLNet_TCP_Recv(client.tcp_socket, server.tcp_buffer, BUFFER_SIZE);
				// Decodes the packet
				if (strncmp(MSG_CLIENT_NUM, server.tcp_buffer, 3) == 0) {
					return server.tcp_buffer[3] - 48;	// Converts from char to number
				}
			}
		}
	}
	return -1;
}

bool connectToServer(char* str_host_ip, char* str_port)
{
	Uint16 port;
	bool connected = false;

	if (validateIPv4Entry(str_host_ip, &server.ip.host)) {
		printf("Host ");
		printIpInfo(&server.ip.host);
	}
	else {
		printf("Invalid server IP entry.\n");
		return false;
	}
	if (validatePortEntry(str_port, &port)) {
		printf("Port validated: %d.\n", port);
	}
	else {
		printf("Invalid server PORT entry.\n");
		return false;
	}

	tcp_socketSet = SDLNet_AllocSocketSet(1);

	// Try to resolve host 
	if (SDLNet_ResolveHost(&server.ip, str_host_ip, port) == -1)
	{
		printf("Failed to resolve the server hostname: %s\n Continuing...\n", SDLNet_GetError());
	}
	else // If we successfully resolved the host then output the details
	{
		// Get our IP address in proper dot-quad format by breaking up the 32-bit unsigned host address and splitting it into an array of four 8-bit unsigned numbers...
		Uint8 * dotQuad = (Uint8*)&server.ip.host;
		printf("Succesfully resolved host to IP: %d.%d.%d.%d and port %d\n", (unsigned short)dotQuad[0], (unsigned short)dotQuad[1], (unsigned short)dotQuad[2], (unsigned short)dotQuad[3], SDLNet_Read16(&server.ip.port));

		//... and then outputting them cast to integers. Then read the last 16 bits of the serverIP object to get the port number
	}

	/*
	// Unstable part of code
	// Try to resolve the IP of the server
	char* host = SDLNet_ResolveIP(&server.ip);

	if (host == NULL)
	{
		printf("Failed to resolve the server IP address: %s.\n", SDLNet_GetError());
	}
	else
	{
		printf("Succesfully resolved IP to host: %s\n", host);
	}
	// End of unstable part of code
	*/

	// Setup player actions
	for (int j = 0; j < MAX_PLAYERS; j++) {
		playerActions[j].w = 0;
		playerActions[j].s = 0;
		playerActions[j].a = 0;
		playerActions[j].d = 0;
		playerActions[j].shoot = 0;
	}

	// Try to open a connection to the server 
	if (!(client.tcp_socket = SDLNet_TCP_Open(&server.ip))) {
		printf("Failed to open socket server: %s.\n", SDLNet_GetError());
	}
	else { // if we succesfully opened a connection check for server response to connection
	
		   // Add our socket to the socket set for polling
		SDLNet_TCP_AddSocket(tcp_socketSet, client.tcp_socket);

		// Wait for up to five seconds for a response from the server
		// Note: If we don't check the socket set and WAIT for the response, we'll be checking before the server can respond, and it'll look as if the server sent us nothing back
		int activeSockets = SDLNet_CheckSockets(tcp_socketSet, 5000);
		if (activeSockets == -1) {
			printf("SDLNet_CheckSockets: %s", SDLNet_GetError());
		}
		printf("There are %d active socket(s) with data at the moment.\n", activeSockets);

		if (SDLNet_SocketReady(client.tcp_socket) != 0) {
			server.tcp_byte_count = SDLNet_TCP_Recv(client.tcp_socket, server.tcp_buffer, BUFFER_SIZE);
			printf("Message recieved: %s\n", server.tcp_buffer);
			if (strcmp(MSG_SERVER_NOT_FULL, server.tcp_buffer) == 0) {
				printf("Joined server...\n");

				// if we managed to connect request client id
				client_player_num = requestPlayerId();
				if (client_player_num >= 0) {
					printf("Client number set to: %d\n", client_player_num);
					connected = true;
				}
			}
			else if (strcmp(MSG_SERVER_FULL, server.tcp_buffer) == 0) {
				printf("Server is full.\n");
			}
		}
		else {
			printf("No response from server\n");
		}
	}
	return connected;
}

/*
int connect(int currentID)
{
IPaddress ip;
TCPsocket client;

//write the ip of the host
printf("testing connection\n");
if (SDLNet_ResolveHost(&ip, SERVERIP, INITPORT) == -1)
{
printf("Couldn't resolve host during the connection!\n");
SDL_Delay(4000);
exit(1);
}
client = SDLNet_TCP_Open(&ip);

int player_id = 0;
printf("Player id %d\n", player_id);
SDLNet_TCP_Recv(client, &player_id, 100);

SDLNet_TCP_Close(client);
printf("player id: %d\n", player_id);

createDemonCL(player_id, "listenForMessage", listenForMessage);
createDemonCL(player_id, "imConnected", imConnected);

return player_id;
}
*/
