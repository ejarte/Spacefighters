
#include "libraries.h"
#include "graphics.h"
#include "events.h"
#include "game_menu.h"
#include "state_handler.h"


int interfaceState = 0;

#define INT_STATE_OPTION_OPEN = 0
#define INT_STATE_ABOUT = 1


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



void initInterface()
{
	optionImage = IMG_LoadTexture(renderer, "images/Interface/opt.bmp");
	chatImage = IMG_LoadTexture(renderer, "images/Interface/chat.bmp");
	backImage = IMG_LoadTexture(renderer, "images/Interface/Back.bmp");
	settingsImage = IMG_LoadTexture(renderer, "images/Interface/Settings.bmp");
	aboutImage = IMG_LoadTexture(renderer, "images/Interface/About.bmp");
	exitImage = IMG_LoadTexture(renderer, "images/Interface/Exit.bmp");
	hotkeysImage = IMG_LoadTexture(renderer, "images/Interface/Hotkeys.bmp");
	infoWindowImage = IMG_LoadTexture(renderer, "images/Interface/About-info.bmp");
	soundONImage = IMG_LoadTexture(renderer, "images/Interface/SoundOn.bmp");
	soundOFFImage = IMG_LoadTexture(renderer, "images/Interface/SoundOff.bmp");
	infoHotkeysImage = IMG_LoadTexture(renderer, "images/Interface/arrows.bmp");
	// Done
	//printf("Interface Initialized...\n");
}

void all_button_positions_Interface() {

	//SDL_Rect button_option;      // option  button
	option_rect.w = 200;
	option_rect.h = 70;
	option_rect.x = 20;
	option_rect.y = 0;

	//SDL_Rect button_chat;    // chat button
	chat_rect.w = 200;
	chat_rect.h = 70;
	chat_rect.x = 800;
	chat_rect.y = 500;

	//SDL_Rect button_Back;    //  Back button
	backButton_rect.w = 185;
	backButton_rect.h = 70;
	backButton_rect.x = 250;
	backButton_rect.y = 160;

	//SDL_Rect button_settings;    //  Settings button
	settings_rect.w = 200;
	settings_rect.h = 70;
	settings_rect.x = 250;
	settings_rect.y = 230;

	//SDL_Rect button_about;    //  About button
	about_rect.w = 200;
	about_rect.h = 70;
	about_rect.x = 250;
	about_rect.y = 300;

	//SDL_Rect button_exit;    //  Exit button
	exit_rect.w = 200;
	exit_rect.h = 70;
	exit_rect.x = 250;
	exit_rect.y = 370;

	//SDL_Rect button_hotkeys;    //  Hotkeys button
	hotkeys_rect.w = 180;
	hotkeys_rect.h = 70;
	hotkeys_rect.x = 480;
	hotkeys_rect.y = 310;

	//SDL_Rect button_AboutInfoWindow   // Info window
	infoWindow_rect.w = 400;
	infoWindow_rect.h = 180;
	infoWindow_rect.x = 480;
	infoWindow_rect.y = 160;

	//SDL_Rect button_sound;    //  soundON button
	soundON_rect.w = 100;
	soundON_rect.h = 70;
	soundON_rect.x = 480;
	soundON_rect.y = 230;

	//SDL_Rect button_movement_shot;    //  movement button
	infoHotkeys_rect.w = 250;
	infoHotkeys_rect.h = 180;
	infoHotkeys_rect.x = 670;
	infoHotkeys_rect.y = 290;

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

/*void rendererInterface()
{
SDL_RenderClear(rend);
SDL_RenderCopy(rend, texBakgrund, NULL, &bakgrund);

for (int i = 0; i < 5; ++i) {
SDL_Rect rect;
rect.x = dest.x + i*rect.w;
rect.y = dest.y;
rect.w = dest.w;
rect.h = dest.h;
SDL_RenderCopy(rend, tex, NULL, &rect);
}
SDL_RenderCopy(rend, tex, NULL, &dest);
}
*/

int gameState0() {
	SDL_RenderCopy(renderer, optionImage, NULL, &option_rect);
	SDL_RenderCopy(renderer, chatImage, NULL, &chat_rect);
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
	SDL_RenderCopy(renderer, hotkeysImage, NULL, &hotkeys_rect);
	SDL_RenderCopy(renderer, soundONImage, NULL, &soundON_rect);
}

int gameState3() {

	gameState1();
	SDL_RenderCopy(renderer, infoWindowImage, NULL, &infoWindow_rect);
}

int gameState4()
{
	gameState1();
	SDL_RenderCopy(renderer, soundONImage, NULL, &soundON_rect);
	SDL_RenderCopy(renderer, hotkeysImage, NULL, &hotkeys_rect);
	if (button_sound_pressed) {
		SDL_RenderCopy(renderer, soundOFFImage, NULL, &soundON_rect);
	}
}

int gameState5() {
	gameState4();
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

	if (interfaceState != 0) {

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
		if (SDL_PointInRect(&point, &soundON_rect) && mouseEventPressed(SDL_BUTTON_LEFT)) {
			mouse_on_sound();
			interfaceState = 4;
		}
		if (SDL_PointInRect(&point, &hotkeys_rect) && mouseEventPressed(SDL_BUTTON_LEFT)) {
			interfaceState = 5;
		}
	}
}




