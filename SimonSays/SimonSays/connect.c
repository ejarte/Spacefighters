#include "game.h"
#include "TCP.h"
#include "UDP.h"
#include "interface_lib.h"
#include "text_messages.h"

int createDemon()
{
	SDL_Thread *TCPThread = NULL;
	const char *TCPThreadReturnValue;
	TCPThread = SDL_CreateThread(TCP, "Connect", "127.0.0.1");

	if (NULL == TCPThread) {
		printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
	}
	else {
		printf("you created a TCP demon\n");
	}
}

int connectToServer()
{
		SDL_Thread *TCPThread = NULL;
		int *TCPThreadReturnValue = 0;
		TCPThread = SDL_CreateThread(connect(), "TestThread", NULL);

		if (NULL == TCPThread) {
			printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
		}
		else {
			SDL_WaitThread(TCPThread, &TCPThreadReturnValue);
			printf("\nThread returned value: %d", TCPThreadReturnValue);
		}
		return TCPThreadReturnValue;
}
