#include "game_state.h"
#include "state_handler.h"

int boxW;
int boxH;

SDL_Texture* spaceship_box;

SDL_Rect spaceship_rect;

char yellowPath[30];
char greenPath[30];
char bluePath[30];
char redPath[30];
char spaceShip_path[30];

int frame = 0;
int frameTime = 0;

SDL_Rect rects[3]; //alla frames i rymdskeppet

Mix_Music *bgm; //longer then 10 sec
Mix_Chunk *soundEffect;  //ljudeffekter

#define SPACESHIP "images/spaceship.png"

SDL_Texture *currentImage;
SDL_Rect playerRect;

int frameWidth, frameHeight;
int textureWidth, textureHeight;
int posX, posY;

void buttonSound()
{
		soundEffect = Mix_LoadWAV("soundeffects/buttonpop.wav");
		Mix_PlayChannel(-1, soundEffect, 0);
}

void checkButtonClicked()
{

	if (SDL_PointInRect(&p, &spaceship_rect) && mouseEventPressed(SDL_BUTTON_LEFT))
	{
		buttonSound();
	}

}

void checkButtonPressedDown()
{
	if (SDL_PointInRect(&p, &spaceship_rect) && mouseEventHeld(SDL_BUTTON_LEFT))
	{
		strcpy(spaceShip_path, SPACESHIP);
	}
}

void initNormal()
{
	strcpy(spaceShip_path, SPACESHIP);
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
		printf("Left mouse released - %d\n", getTimeStamp(STATE_RELEASED, SDL_BUTTON_LEFT));
	
	if (keyEventPressed(SDL_SCANCODE_W))
		spaceship_rect.y += 5;
	//	printf("W pressed - %d\n", getTimeStamp(STATE_PRESSED, SDL_SCANCODE_W));

	if (keyEventHeld(SDL_SCANCODE_W))
		spaceship_rect.y -= 5;

	if (keyEventHeld(SDL_SCANCODE_S))
		spaceship_rect.y += 5;

	if (keyEventHeld(SDL_SCANCODE_A))
		spaceship_rect.x -= 5;

	if (keyEventHeld(SDL_SCANCODE_D))
		spaceship_rect.x += 5;

	if (quitEventTriggered()) {
		setNextState(STATE_EXIT);
	}
}

void spaceShipSetup()
{
	currentImage = IMG_LoadTexture(renderer, spaceShip_path);
	setrects(rects);
	SDL_Rect* CurrentClip = &rects[0];

	SDL_QueryTexture(currentImage, NULL, NULL, &textureWidth, &textureHeight);

	frameWidth = textureWidth / 4;
	frameHeight = textureHeight / 2;

	playerRect.x = playerRect.y = 0;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;

	posX = 50;
	posY = 50;

	spaceship_rect.x = posX;
	spaceship_rect.y = posY;
	spaceship_rect.h = 100;
	spaceship_rect.w = 50;
}

void animateSpaceship()
{
	SDL_RenderClear(renderer); //Clears the screen

	frameTime++;
	if (frameTime == 2)
	{
		frame++;
		if (frame == 4)
			frame = 0;
		frameTime = 0;
	}
	SDL_RenderCopy(renderer, currentImage, &rects[frame], &spaceship_rect);
	SDL_RenderPresent(renderer);
}

void setrects(SDL_Rect* clip)
{
	clip[0].x = 0;
	clip[0].y = 0;
	clip[0].w = 99;
	clip[0].h = 154;

	clip[1].x = 99;
	clip[1].y = 0;
	clip[1].w = 99;
	clip[1].h = 154;

	clip[2].x = 198;
	clip[2].y = 0;
	clip[2].w = 99;
	clip[2].h = 154;

	clip[3].x = 297;
	clip[3].y = 0;
	clip[3].w = 99;
	clip[3].h = 154;
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
	SDL_DestroyTexture(spaceship_box);
}

void initGameState()
{


}

void onGameRunning()
{
	lookState();
	frameTime++;
	animateSpaceship();				//initierar bilder
	clearImages();				//rensar bilderna från ram
}