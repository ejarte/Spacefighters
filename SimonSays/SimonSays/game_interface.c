
#include "libraries.h"
#include "graphics.h"
#include "events.h"
#include "game_interface.h"
#include "state_handler.h"




int interfaceState = 0;

#define MAXLIV 10
#define hpBarLength 17
#define hpBarWidth 27


bool button_option_pressed = false;
bool button_sound_pressed = false;
bool hotkeys_pressed = false;
bool aboutButton_pressed = false;
bool settingsButton_pressed = false;


SDL_Texture *optionImage;
SDL_Rect option_rect;

SDL_Texture *chatImage;
SDL_Rect chat_rect;

SDL_Texture *settingsImage;
SDL_Rect settings_rect;

SDL_Texture *backImage;
SDL_Rect backButton_rect;

SDL_Texture *aboutImage;
SDL_Rect about_rect;

SDL_Texture *exitImage;
SDL_Rect exit_rect;

SDL_Texture *hotkeysImage;
SDL_Rect hotkeys_rect;

SDL_Texture *infoWindowImage;
SDL_Rect infoWindow_rect;

SDL_Texture *soundONImage;
SDL_Rect soundON_rect;

SDL_Texture *soundOFFImage;
//SDL_Rect soundOFF_rect;

SDL_Texture *infoHotkeysImage;
SDL_Rect infoHotkeys_rect;

SDL_Texture *hpBarImage;
SDL_Rect hpBar_rect;

SDL_Texture *hpBarBackgroundImage;



void initInterface()
{
	optionImage = IMG_LoadTexture(renderer, "images/Interface/options.png");
	chatImage = IMG_LoadTexture(renderer, "images/Interface/chat.png");
	backImage = IMG_LoadTexture(renderer, "images/Interface/back.png");
	settingsImage = IMG_LoadTexture(renderer, "images/Interface/settings.png");
	aboutImage = IMG_LoadTexture(renderer, "images/Interface/about.png");
	exitImage = IMG_LoadTexture(renderer, "images/Interface/quit.png");
	hotkeysImage = IMG_LoadTexture(renderer, "images/Interface/hotkeys.png");
	infoWindowImage = IMG_LoadTexture(renderer, "images/Interface/about-info.png");
	soundONImage = IMG_LoadTexture(renderer, "images/Interface/SoundOn.bmp");
	soundOFFImage = IMG_LoadTexture(renderer, "images/Interface/SoundOff.bmp");
	infoHotkeysImage = IMG_LoadTexture(renderer, "images/Interface/hotkeys-info.png");
	hpBarImage = IMG_LoadTexture(renderer, "images/Interface/damageSym.bmp");
	hpBarBackgroundImage =IMG_LoadTexture(renderer, "images/Interface/damageSymBackground.bmp");

	// Done
	//printf("Interface Initialized...\n");
}

void all_button_positions_Interface() {

	//SDL_Rect button_option;      // option  button
	option_rect.w = 122;
	option_rect.h = 47;
	option_rect.x = 20;
	option_rect.y = 0;

	//SDL_Rect button_chat;    // chat button
	chat_rect.w = 122;
	chat_rect.h = 47;
	chat_rect.x = 800;
	chat_rect.y = 500;

	//SDL_Rect button_hpBar;    // chat hpBar
	hpBar_rect.w = hpBarLength;
	hpBar_rect.h = hpBarWidth;
	hpBar_rect.x = 20;
	hpBar_rect.y = 600;

	//SDL_Rect button_Back;    //  Back button
	backButton_rect.w = 122;
	backButton_rect.h = 47;
	backButton_rect.x = 250;
	backButton_rect.y = 160;

	//SDL_Rect button_settings;    //  Settings button
	settings_rect.w = 122;
	settings_rect.h = 47;
	settings_rect.x = 250;
	settings_rect.y = 210;

	//SDL_Rect button_about;    //  About button
	about_rect.w = 122;
	about_rect.h = 47;
	about_rect.x = 250;
	about_rect.y = 260;

	//SDL_Rect button_exit;    //  Exit button
	exit_rect.w = 122;
	exit_rect.h = 47;
	exit_rect.x = 250;
	exit_rect.y = 310;

	//SDL_Rect button_hotkeys;    //  Hotkeys button
	hotkeys_rect.w = 122;
	hotkeys_rect.h = 47;
	hotkeys_rect.x = 420;
	hotkeys_rect.y = 225;

	//SDL_Rect button_AboutInfoWindow   // Info window
	infoWindow_rect.w = 381;
	infoWindow_rect.h = 111;
	infoWindow_rect.x = 420;
	infoWindow_rect.y = 210;

	//SDL_Rect button_sound;    //  soundON button
	soundON_rect.w = 70;
	soundON_rect.h = 50;
	soundON_rect.x = 445;
	soundON_rect.y = 170;

	//SDL_Rect button_movement_shot;    //  movement button
	infoHotkeys_rect.w = 250;
	infoHotkeys_rect.h = 105;
	infoHotkeys_rect.x = 550;
	infoHotkeys_rect.y = 200;

}

void mouse_on_sound()
{
	if (button_sound_pressed)
	{
		button_sound_pressed = false;
	}
	else
	{
		button_sound_pressed = true;

	}
}


int gameState0() {

	chat_rect.w = 122;
	chat_rect.h = 47;
	chat_rect.x = getWindowWidth() - 122-6;
	chat_rect.y = getWindowHeight()-47-6;

	
	SDL_RenderCopy(renderer, optionImage, NULL, &option_rect);
	SDL_RenderCopy(renderer, chatImage, NULL, &chat_rect);
}

void interface_renderPlayerHP(double percentage_life)
{
	if (percentage_life > 1.0)
		percentage_life = 1.0;
	if (percentage_life < 0)
		percentage_life = 0;

	hpBar_rect.w = hpBarWidth;
	hpBar_rect.h = hpBarLength;
	hpBar_rect.x = 20;
	hpBar_rect.y = getWindowHeight() - hpBarLength - 6;

	int lifeLength = (double)percentage_life * 10.0;
	int hpBarMaxlength = 10;
	if (0 <= percentage_life || percentage_life <= 1)
	{

		for (int i = 0; i <lifeLength; ++i) {
			SDL_Rect rect;
			rect.w = hpBar_rect.w;
			rect.h = hpBar_rect.h;
			rect.x = hpBar_rect.x + i*rect.w;
			rect.y = hpBar_rect.y;
			SDL_RenderCopy(renderer, hpBarImage, NULL, &rect);
		}

	}
	for (int i = lifeLength; i < hpBarMaxlength; ++i) {
		SDL_Rect hpBarBackground_rect;

		hpBarBackground_rect.w = hpBar_rect.w;
		hpBarBackground_rect.x = hpBar_rect.x + i*hpBarBackground_rect.w;
		hpBarBackground_rect.y = hpBar_rect.y;
		hpBarBackground_rect.h = hpBar_rect.h;
		SDL_RenderCopy(renderer, hpBarBackgroundImage, NULL, &hpBarBackground_rect);
	}

}

int gameState1()
{
	gameState0();
	SDL_RenderCopy(renderer, backImage, NULL, &backButton_rect);
	SDL_RenderCopy(renderer, settingsImage, NULL, &settings_rect);
	SDL_RenderCopy(renderer, aboutImage, NULL, &about_rect);
	SDL_RenderCopy(renderer, exitImage, NULL, &exit_rect);
}

int gameState2() {

	gameState1();
	//SDL_RenderCopy(renderer, backImage, NULL, &backButton_rect);
	SDL_RenderCopy(renderer, hotkeysImage, NULL, &hotkeys_rect);
	SDL_RenderCopy(renderer, soundONImage, NULL, &soundON_rect);
}

int gameState3() {

	gameState1();
	//SDL_RenderCopy(renderer, backImage, NULL, &backButton_rect);
	SDL_RenderCopy(renderer, infoWindowImage, NULL, &infoWindow_rect);
}

int gameState4()
{
	gameState2();
	SDL_RenderCopy(renderer, soundONImage, NULL, &soundON_rect);
	SDL_RenderCopy(renderer, hotkeysImage, NULL, &hotkeys_rect);
	if (button_sound_pressed) {
		SDL_RenderCopy(renderer, soundOFFImage, NULL, &soundON_rect);
	}
}

int gameState5() {
	gameState4();
	//SDL_RenderCopy(renderer, backImage, NULL, &backButton_rect);
	SDL_RenderCopy(renderer, infoHotkeysImage, NULL, &infoHotkeys_rect);
}

void rendererInterface()
{
	if (interfaceState == 0)
		gameState0();

	else if (interfaceState == 1)
	{

		gameState1();
	}

	else if (interfaceState == 2)
	{
		gameState2();
	}

	else if (interfaceState == 3)
	{
		gameState3();
	}

	else if (interfaceState == 4)
	{
		gameState4();
	}

	else if (interfaceState == 5)
	{
		gameState5();
	}

}

void runInterface() {
	SDL_Point point = getMousePos();

	if (SDL_PointInRect(&point, &option_rect) && mouseEventPressed(SDL_BUTTON_LEFT))
	{
		interfaceState = 1;
	}

	if (interfaceState != 0 ) {

		if (SDL_PointInRect(&point, &backButton_rect) && mouseEventPressed(SDL_BUTTON_LEFT)) {
			interfaceState = 0;
		}
		if (SDL_PointInRect(&point, &settings_rect) && mouseEventPressed(SDL_BUTTON_LEFT)) {
			interfaceState = 2;
		}
		if (SDL_PointInRect(&point, &about_rect) && mouseEventPressed(SDL_BUTTON_LEFT)) {
			interfaceState = 3;
		}
		if (SDL_PointInRect(&point, &exit_rect) && mouseEventPressed(SDL_BUTTON_LEFT)) {
			setNextState(STATE_EXIT);
		}
		if (SDL_PointInRect(&point, &chat_rect) && mouseEventPressed(SDL_BUTTON_LEFT)) {

			printf("CHAT BUTTON CLICKED.\n");
		}

		// ?????
		if (SDL_PointInRect(&point, &hpBar_rect) && mouseEventPressed(SDL_BUTTON_LEFT)) {

			printf("HPBAR BUTTON CLICKED.\n");
		}

		if (SDL_PointInRect(&point, &soundON_rect) && mouseEventPressed(SDL_BUTTON_LEFT)) {
			mouse_on_sound();
			interfaceState = 4;
		}
		if (SDL_PointInRect(&point, &hotkeys_rect) && mouseEventPressed(SDL_BUTTON_LEFT)) {
			interfaceState = 5;
			
		}
	}
}




