#include "game_state.h"
#include "state_handler.h"

int boxW;
int boxH;
SDL_Texture* yellow_box;
SDL_Texture* green_box;
SDL_Texture* red_box;
SDL_Texture* blue_box;

SDL_Rect yellow_rect; //rutan där bilden kommer finnas
SDL_Rect green_rect;
SDL_Rect red_rect;
SDL_Rect blue_rect;

char yellowPath[30];
char greenPath[30];
char bluePath[30];
char redPath[30];

Mix_Music *bgm; //longer then 10 sec
Mix_Chunk *soundEffect;  //ljudeffekter

#define YELLOW_NORMAL "images/yellowsquare.bmp"
#define YELLOW_HOVER "images/yellowsquare.bmp"
#define YELLOW_CLICKED "images/yellowsquare_light.bmp"

#define GREEN_NORMAL "images/greensquare.bmp"
#define GREEN_HOVER "images/greensquare.bmp"
#define GREEN_CLICKED "images/greensquare_light.bmp"

#define BLUE_NORMAL "images/bluesquare.bmp"
#define BLUE_HOVER "images/bluesquare.bmp"
#define BLUE_CLICKED "images/bluesquare_light.bmp"

#define RED_NORMAL "images/redsquare.bmp"
#define RED_HOVER "images/redsquare.bmp"
#define RED_CLICKED "images/redsquare_light.bmp"

void buttonSound()
{
		soundEffect = Mix_LoadWAV("soundeffects/buttonpop.wav");
		Mix_PlayChannel(-1, soundEffect, 0);
}

void checkButtonClicked()
{

	if (SDL_PointInRect(&p, &yellow_rect) && mouseEventPressed(SDL_BUTTON_LEFT))
	{
		buttonSound();
	} else if (SDL_PointInRect(&p, &green_rect) && mouseEventPressed(SDL_BUTTON_LEFT))
	{
		buttonSound();
	} else if (SDL_PointInRect(&p, &blue_rect) && mouseEventPressed(SDL_BUTTON_LEFT))
	{
		buttonSound();
	} else if (SDL_PointInRect(&p, &red_rect) && mouseEventPressed(SDL_BUTTON_LEFT))
	{
		buttonSound();
	}

}

void checkButtonPressedDown()
{

	if (SDL_PointInRect(&p, &yellow_rect) && mouseEventHeld(SDL_BUTTON_LEFT))
	{
		strcpy(yellowPath, YELLOW_CLICKED);
	}
	else
		strcpy(yellowPath, YELLOW_NORMAL);

	if (SDL_PointInRect(&p, &green_rect) && mouseEventHeld(SDL_BUTTON_LEFT))
	{
		strcpy(greenPath, GREEN_CLICKED);
	}
	else
		strcpy(greenPath, GREEN_NORMAL);

	if (SDL_PointInRect(&p, &blue_rect) && mouseEventHeld(SDL_BUTTON_LEFT))
	{
		strcpy(bluePath, BLUE_CLICKED);
	}
	else
		strcpy(bluePath, BLUE_NORMAL);

	if (SDL_PointInRect(&p, &red_rect) && mouseEventHeld(SDL_BUTTON_LEFT))
	{
		strcpy(redPath, RED_CLICKED);
	}
	else
		strcpy(redPath, RED_NORMAL);
	
}

void initNormal()
{
	strcpy(yellowPath, YELLOW_NORMAL);
	strcpy(greenPath, GREEN_NORMAL);
	strcpy(bluePath, BLUE_NORMAL);
	strcpy(redPath, RED_NORMAL);
}

void lookState()  //gameloop
{
	// Enables/disables chat on return key
	if (keyEventPressed(SDL_SCANCODE_RETURN)) {
		if (isTextEventEnabled()) {
			puts("Chat disabled.");
			disableTextInput();
		}
		else {
			puts("Chat enabled");
			enableTextInput();
		}
	}

	SDL_GetMouseState(&p.x, &p.y);
	checkButtonPressedDown(); //change colour of button if it is pressed

	checkButtonClicked(); //play sound if button is pressed

						  // if the chat is enabled and a text event was triggered it gets the text input
	if (textEvent()) {
		puts(getTextInput());
	}

	if (mouseEventHeld(SDL_BUTTON_LEFT))
		//puts("Held: Left mouse");

	if (mouseEventPressed(SDL_BUTTON_LEFT))
		Mix_PlayChannel(0, soundEffect, 1);
			//	printf("Left mouse pressed - %d\n", getTimeStamp(STATE_PRESSED, SDL_BUTTON_LEFT));

	if (mouseEventReleased(SDL_BUTTON_LEFT))
		//printf("Left mouse released - %d\n", getTimeStamp(STATE_RELEASED, SDL_BUTTON_LEFT));

	if (keyEventHeld(SDL_SCANCODE_W))
		puts("Held: W");

	if (keyEventPressed(SDL_SCANCODE_W))
		printf("W pressed - %d\n", getTimeStamp(STATE_PRESSED, SDL_SCANCODE_W));

	if (keyEventReleased(SDL_SCANCODE_W))
		printf("W released - %d\n", getTimeStamp(STATE_RELEASED, SDL_SCANCODE_W));

	if (quitEventTriggered()) {
		setNextState(STATE_EXIT);
	}
}


void initImages()
{
	//laddar in bilderna
	SDL_GetRendererOutputSize(renderer, &screenW, &screenH);

	if (boxW < boxH)
	{
		boxW = screenW / 4;
		boxH = boxW;
	}
	else
	{
		boxH = screenH / 4;
		boxW = boxH;
	}

	yellow_box = NULL;
	loadTexture(yellowPath, &yellow_box); //laddar den gula bilden i yellow_box

	yellow_rect.x = screenW / 2 - (boxW);
	yellow_rect.y = 10 + (boxH * 0.2);
	yellow_rect.w = boxW;  //Bredd
	yellow_rect.h = boxH;  //Höjd

	green_box = NULL;
	loadTexture(greenPath, &green_box); //laddar den gröna bilden i green_box

	green_rect.x = 10 + (screenW / 2);
	green_rect.y = 10 + (boxH * 0.2);
	green_rect.w = boxW;
	green_rect.h = boxH;

	red_box = NULL;
	loadTexture(redPath, &red_box); //laddar den röda bilden i red_box

	red_rect.x = screenW / 2 - (boxW);
	red_rect.y = 20 + boxH + (boxH * 0.2);
	red_rect.w = boxW;
	red_rect.h = boxH;

	blue_box = NULL;
	loadTexture(bluePath, &blue_box); //laddar den gula bilden i yellow_box

	blue_rect.x = 10 + (screenW / 2);
	blue_rect.y = 20 + boxH + (boxH * 0.2);
	blue_rect.w = boxW;  //Bredd
	blue_rect.h = boxH;  //10 + (screenW / 2)
}

void drawScreen()
{
	SDL_RenderClear(renderer); //Clears the screen
							   //Ritar ut bilderna på fönstret
	SDL_RenderCopy(renderer, yellow_box, NULL, &yellow_rect); //Null eftersom vi inte ska croppa bilden
	SDL_RenderCopy(renderer, green_box, NULL, &green_rect);
	SDL_RenderCopy(renderer, red_box, NULL, &red_rect);
	SDL_RenderCopy(renderer, blue_box, NULL, &blue_rect);

	SDL_RenderPresent(renderer);
}

void clearPointers()
{
	//Tar bort pekarna ur minnet för säkerhets skull
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	clearImages();
	Mix_FreeChunk(soundEffect);
	Mix_FreeMusic(bgm);

	Mix_Quit();
	SDL_Quit();
}

void clearImages()
{
	SDL_DestroyTexture(yellow_box);
	SDL_DestroyTexture(green_box);
	SDL_DestroyTexture(red_box);
	SDL_DestroyTexture(blue_box);
}



void initGameState()
{


}

void onGameRunning()
{
	lookState();
	initImages();				//initierar bilder
	drawScreen();				//ritar upp bilder m.m. på fönstret
	clearImages();				//rensar bilderna från ram
}