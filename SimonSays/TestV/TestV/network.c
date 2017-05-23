#include "network.h"

void TCP_broadcast()
{
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (c[i].tcp_socket_is_free == false) {
			if (SDLNet_TCP_Send(c[i].tcp_socket, (void *)s.tcp_buffer, s.tcp_len) < s.tcp_len) {
				printf("Failed to send neutral object creation: %s\n", SDLNet_GetError());
			}
		}
	}
}

void TCP_broadcastCreatedNeutralObject(int obj_type, SDL_Point spawn, SDL_Point velocity, int facing)
{
	char data[100];
	s.tcp_buffer[0] = '\0';
	strcpy(s.tcp_buffer, MSG_NEUTRAL_OBJ);
	sprintf(data, "%d %d %d %d %d %d", obj_type, spawn.x, spawn.y, velocity.x, velocity.y, facing);
	strcat(s.tcp_buffer, data);
	s.tcp_len = strlen(s.tcp_buffer) + 1;
	TCP_broadcast();
}