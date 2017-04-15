#include "game_state.h"
#include "world.h"

#define MAXSPEED 16
#define DRAG 0.98
#define ACC 1

typedef struct Spaceship
{
	float speedx;
	float acc;
	int x;
	int y;
	float drag;
	float speedy;
} Player;

Player Jacob = {0, 1.05, 50, 100, 0.98, 0};

Mix_Music *bgm; //longer then 10 sec
Mix_Chunk *soundEffect;  //ljudeffekter

#define SPACESHIP "images/spaceship.png"
#define SKY "images/bakgrund_himmel.gif"

SDL_Rect background_rect;
SDL_Texture* background_box;
char background_path[30];
SDL_Texture *backgroundImage;

SDL_Texture *currentImage;
SDL_Rect playerRect;

int frameWidth, frameHeight;
int textureWidth, textureHeight;
int posX, posY;

SDL_Rect rects[3]; //alla frames i rymdskeppet
SDL_Texture* spaceship_box;
SDL_Rect spaceship_rect;
char spaceShip_path[30];
int frame = 0;
int frameTime = 0;

float angle = 100.0f; // set the angle.
SDL_Point center = { 8, 8 }; // the center where the texture will be rotated.
SDL_RendererFlip flip = SDL_FLIP_NONE; // the flip of the texture.

float angleShip(SDL_Rect pSpaceShip, SDL_Point pmouse)
{
	float newAngle, delta_y, delta_x;
	delta_y = pSpaceShip.y - pmouse.y;
	delta_x = pSpaceShip.x - pmouse.x;
	newAngle = (atan2(delta_y, delta_x) * 180.0000) / M_PI; //får ut vinkeln i grader mellan muspekaren och bilden

	return newAngle - 90; // 90 eftersom annars så pekar skeppets sida mot muspekaren
}

void buttonSound()
{
		soundEffect = Mix_LoadWAV("soundeffects/buttonpop.wav");
		Mix_PlayChannel(-1, soundEffect, 0);
}

void checkButtonClicked()
{
	SDL_Point p = getMousePos();
	if (SDL_PointInRect(&p, &spaceship_rect) && mouseEventPressed(SDL_BUTTON_LEFT))
	{
		buttonSound();
	}

}

void checkButtonPressedDown()
{
	SDL_Point p = getMousePos();
	if (SDL_PointInRect(&p, &spaceship_rect) && mouseEventHeld(SDL_BUTTON_LEFT))
	{
		strcpy(spaceShip_path, SPACESHIP);
	}
}

void initNormal() // the standard image for spaceship
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
	SDL_Point p = getMousePos();

	checkButtonPressedDown(); //change colour of button if it is pressed

	checkButtonClicked(); //play sound if button is pressed

						  // if the chat is enabled and a text event was triggered it gets the text input
	if (textEvent()) {
		puts(getTextInput());
	}

	if (mouseEventHeld(SDL_BUTTON_LEFT))
		buttonSound();

	if (mouseEventPressed(SDL_BUTTON_LEFT))
	{
	}

	if (mouseEventReleased(SDL_BUTTON_LEFT))
		printf("Left mouse released - %d\n", getTimeStamp(STATE_RELEASED, SDL_BUTTON_LEFT));
	

	//if (keyEventPressed(SDL_SCANCODE_W))
	//	spaceship_rect.y += 5;			//up

	if (keyEventHeld(SDL_SCANCODE_W))
	{
		Jacob.speedy -= ACC;
	}
	if (keyEventHeld(SDL_SCANCODE_S))
	{
		Jacob.speedy += ACC;			//down
	}
	if (keyEventHeld(SDL_SCANCODE_A))
	{
		Jacob.speedx -= ACC;				//left
	}
	if (keyEventHeld(SDL_SCANCODE_D))
	{
		Jacob.speedx += ACC;			//right
	}


	if (quitEventTriggered()) {
		setNextState(STATE_EXIT);
	}
}

void movementSpaceship()
{
	//controlling maxspeed
	if (Jacob.speedy > MAXSPEED)
	{
		Jacob.speedy = MAXSPEED;
	}
	else if (Jacob.speedy < -MAXSPEED)
		Jacob.speedy = -MAXSPEED;

	if (Jacob.speedx > MAXSPEED)
	{
		Jacob.speedx = MAXSPEED;
	}
	else if (Jacob.speedx < -MAXSPEED)
		Jacob.speedx = -MAXSPEED;

	Jacob.speedx *= DRAG;
	Jacob.speedy *= DRAG;

	//moving the spaceship

	int newX = spaceship_rect.x + Jacob.speedx;
	int newY = spaceship_rect.y + Jacob.speedy;
	if (isInsideWorld(newX, newY)) {
		spaceship_rect.x = newX;
		spaceship_rect.y = newY;
	} 
	else {
		printf("Trying to go beyond space!!!\n");
	}
}

void spaceShipSetup()
{
	currentImage = IMG_LoadTexture(renderer, spaceShip_path);
	setrects(rects);
	SDL_Rect* CurrentClip = &rects[0];

	SDL_QueryTexture(currentImage, NULL, NULL, &textureWidth, &textureHeight);

/*	frameWidth = textureWidth / 4;  //ifall man vill automatisera själva uppdelningen av bilderna i spriteshheet istället för att manuellt skriva in
	frameHeight = textureHeight / 2;

	playerRect.w = frameWidth;
	playerRect.h = frameHeight; */

	posX = 50;
	posY = 50;

	spaceship_rect.x = Jacob.x;
	spaceship_rect.y = Jacob.y;
	spaceship_rect.h = 100;
	spaceship_rect.w = 50;


}

void animateSpaceship()
{
	SDL_RenderClear(renderer); //Clears the screen

	SDL_GetRendererOutputSize(renderer, &screenW, &screenH);
	background_rect.w = screenW;
	background_rect.h = screenH;

	SDL_RenderCopy(renderer, backgroundImage, NULL, &background_rect);

	frameTime++;
	if (frameTime == 2)
	{
		frame++;
		if (frame == 4)
			frame = 0;
		frameTime = 0;
	}

	SDL_Point p = getMousePos();

	angle = angleShip(spaceship_rect, p);  //får ut vinkeln mellan rymdskeppet och muspekaren

	SDL_RenderCopyEx(renderer, currentImage, &rects[frame], &spaceship_rect, angle, &center, flip); //ritar ut skeppet i fönstret
	SDL_RenderPresent(renderer);
}

void setrects(SDL_Rect* clip)  // här är själva storleken och positionerna på varje spritesheetbild som används
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
	//SDL_DestroyWindow(window);
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
	SDL_DestroyTexture(background_box);
}

void initSky()  //initierar backgrundsbilden
{
	strcpy(background_path, SKY);
	backgroundImage = IMG_LoadTexture(renderer, background_path);
	background_rect.x = background_rect.y = 0;
}

void initGameState()
{


}

void onGameRunning()
{
	lookState();
	frameTime++;
	animateSpaceship();				//initierar bilder
	movementSpaceship();
	clearImages();				//rensar bilderna från ram
}