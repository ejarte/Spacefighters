#include "SDL.h"
#include "SDL_net.h"

#include "TCP.h"
#include "UDP.h"

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

void initConnection()
{
	for (int i = 0; i < 3; i++)
	{
		isConnected[i] = 0;
	}
}

int main()
{
	//TODO snygga till koden, ta bort onödigt och namnge bättre
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();	

	//UDP();
	player_id = 1;
	broadCast = false;
		TCP();

	SDLNet_Quit();
	SDL_Quit();
	return 0;
}