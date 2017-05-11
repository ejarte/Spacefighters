/*	
*	File		:	intro_menu.c
*	Author(s)	:	Tiago Redaelli
*	Modified	:	09-05-2017
*	Version		:	0.1
*
*	Pre-game intro/connection menu
*
*	To-Do: try to connect and display error messages/alert on failure.
*/

#include "intro_menu.h"
#include "state_handler.h"
#include "definition.h"
#include "graphics.h"
#include "interface_lib.h"
#include "events.h"
#include "game.h"

TTF_Font* kenvector_future;
TTF_Font* kenvector_future_thin;

SDL_Texture* t_background;
SDL_Texture* t_mainmenu_hud;
SDL_Texture* t_networkmenu_hud;
SDL_Texture* t_btn_green_active;
SDL_Texture* t_btn_green_highlighted;
SDL_Texture* t_btn_red_active;
SDL_Texture* t_btn_red_highlighted;
SDL_Texture* t_textbox_active; 
SDL_Texture* t_textbox_highlighted;
SDL_Rect rect_background;

struct Plane mainmenu_hud;
struct Plane networkmenu_hud;

struct Button btn_play;
struct Button btn_exit;
struct Button btn_back;
struct Button btn_connect;
struct TextBox tb_ip;
struct TextBox tb_port;
struct Label l_ip;
struct Label l_port;

bool intro_menu_initialized = false;

SDL_Color white = { 255, 255, 255, 0 };

/*
t = IMG_LoadTexture(renderer, "images/textbox_square.bmp");
interface_setup_textbox(&chat_box, t, renderer, font_roboto_black, createColor(255, 255, 255, 0), createRect(screenW/2 - 50, screenH - 40, 200, 25), 10, 0);
chat_box.selected = true;
*/

void init_introMenu()
{
	int w, h, x, y;
	SDL_Rect rect;

	//SDL_SetWindowDisplayMode(window, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	
	// Fonts
	kenvector_future = TTF_OpenFont("fonts/kenvector_future.ttf", 12);
	kenvector_future_thin = TTF_OpenFont("fonts/kenvector_future_thin.ttf", 12);

	// Background
	t_background = IMG_LoadTexture(renderer, "images/skyBackground.png");
	rect_background.x = rect_background.y = 0;

	// Main menu
	t_mainmenu_hud = IMG_LoadTexture(renderer, "images/Interface/uipaint/main_menu_hud.bmp");
	interface_setup_plane(&mainmenu_hud, t_mainmenu_hud, 0, 0, 219, 176, true);
	w = mainmenu_hud.rect.w;
	h = mainmenu_hud.rect.h;
	mainmenu_hud.rect.x = screenW / 2 - w / 2;
	mainmenu_hud.rect.y = screenH / 2 - h / 2;

	// Play Button
	t_btn_green_active = IMG_LoadTexture(renderer, "images/Interface/button_introMeny.png");
	t_btn_green_highlighted = IMG_LoadTexture(renderer, "images/Interface/button_introMeny.png");
	x = mainmenu_hud.rect.x + 9;
	y = mainmenu_hud.rect.y + 21;
	interface_setup_button(&btn_play, renderer, x, y, t_btn_green_highlighted, t_btn_green_highlighted, t_btn_green_active, "Play", kenvector_future, white);
	btn_play.state = BTN_STATE_UNSELECTED;

	// Exit Button
	t_btn_red_active = IMG_LoadTexture(renderer, "images/Interface/button_introMeny.png");
	t_btn_red_highlighted = IMG_LoadTexture(renderer, "images/Interface/button_introMeny.png");
	x = mainmenu_hud.rect.x + 9;
	y = mainmenu_hud.rect.y + 93;
	interface_setup_button(&btn_exit, renderer, x, y, t_btn_red_highlighted, t_btn_red_highlighted, t_btn_red_active, "Exit", kenvector_future, white);
	btn_play.state = BTN_STATE_UNSELECTED;

	// Network menu
	t_networkmenu_hud = IMG_LoadTexture(renderer, "images/Interface/uipaint/network_menu.bmp");
	interface_setup_plane(&networkmenu_hud, t_networkmenu_hud, 0, 0, 425, 384, true);
	w = networkmenu_hud.rect.w;
	h = networkmenu_hud.rect.h;
	networkmenu_hud.rect.x = screenW / 2 - w / 2;
	networkmenu_hud.rect.y = screenH / 2 - h / 2;

	// Exit Button
	x = networkmenu_hud.rect.x + 9;
	y = networkmenu_hud.rect.y + h - 83;
	interface_setup_button(&btn_back, renderer, x, y, t_btn_red_highlighted, t_btn_red_highlighted, t_btn_red_active, "Back", kenvector_future, white);
	btn_back.state = BTN_STATE_UNSELECTED;

	// Connect Button
	x = networkmenu_hud.rect.x + 17 + btn_back.rect_box.w;
	y = networkmenu_hud.rect.y + h - 83;
	interface_setup_button(&btn_connect, renderer, x, y, t_btn_green_highlighted, t_btn_green_highlighted, t_btn_green_active, "Connect", kenvector_future, white);
	btn_connect.state = BTN_STATE_UNSELECTED;

	// Textbox Texturs
	t_textbox_active = IMG_LoadTexture(renderer, "images/Interface/uipaint/textbox_1.bmp");
	t_textbox_highlighted = IMG_LoadTexture(renderer, "images/Interface/uipaint/textbox_1_highlighted.bmp"); 
	// Textbox IP
	rect.x = networkmenu_hud.rect.x + 89;
	rect.y = networkmenu_hud.rect.y + 89;
	SDL_QueryTexture(t_textbox_active, NULL, NULL, &rect.w, &rect.h);
	interface_setup_textbox(&tb_ip, t_textbox_active, renderer, kenvector_future_thin, white, rect);
	tb_ip.show = true;
	// Textbox Port
	rect.x = tb_ip.rect_box.x;
	rect.y = tb_ip.rect_box.y + 89;
	interface_setup_textbox(&tb_port, t_textbox_active, renderer, kenvector_future_thin, white, rect);
	tb_port.show = true;
	// Label IP
	x = tb_ip.rect_box.x;
	y = tb_ip.rect_box.y - tb_ip.rect_box.h/2;
	interface_setup_label(&l_ip, renderer, "Enter IP:", kenvector_future, white, x, y, true);
	// Label Port
	x = tb_port.rect_box.x;
	y = tb_port.rect_box.y - tb_port.rect_box.h/2;
	interface_setup_label(&l_port, renderer, "Enter Port:", kenvector_future, white, x, y, true);

	printf("Intro Menu Initialized...\n");
}


void cleanup_introMenu()
{

	SDL_DestroyTexture(t_background);
	SDL_DestroyTexture(t_mainmenu_hud);
	SDL_DestroyTexture(t_networkmenu_hud);
	SDL_DestroyTexture(t_btn_green_active);
	SDL_DestroyTexture(t_btn_green_highlighted);
	SDL_DestroyTexture(t_btn_red_active);
	SDL_DestroyTexture(t_btn_red_highlighted);
	SDL_DestroyTexture(t_textbox_active);
	SDL_DestroyTexture(t_textbox_highlighted);
	intro_menu_initialized = false;
}

int event_introMenu()
{
	SDL_Point p = getMousePos();

	// Exit on window button
	if (quitEventTriggered()) {
		setNextState(STATE_EXIT);
		return 0;  // Cleanup intro menu
	}

	// Exit button
	if (SDL_PointInRect(&p, &btn_exit.rect_box)) {
		btn_exit.state = BTN_STATE_MOUSE_OVER;

		if (mouseEventPressed(SDL_BUTTON_LEFT)) {
			setNextState(STATE_EXIT);
			return 0; // Cleanup intro menu
		}
	}
	else {
		btn_exit.state = BTN_STATE_UNSELECTED;
	}

	// Play button
	if (SDL_PointInRect(&p, &btn_play.rect_box)) {
		btn_play.state = BTN_STATE_MOUSE_OVER;
		if (mouseEventPressed(SDL_BUTTON_LEFT)) {
			setNextState(STATE_NETWORK_MENU);
			return 1;
		}
	}
	else {
		btn_play.state = BTN_STATE_UNSELECTED;
	}
	return 1;	
}

void render_introMenu()
{
	SDL_RenderClear(renderer);
	// Render background
	rect_background.w = screenW;
	rect_background.h = screenH;
	SDL_RenderCopy(renderer, t_background, NULL, &rect_background);
	// Hud
	interface_render_plane(&mainmenu_hud, renderer);
	// Buttons
	interface_render_button(&btn_play, renderer);
	interface_render_button(&btn_exit, renderer);

	SDL_RenderPresent(renderer);
}

void execute_introMenu()
{
	if (intro_menu_initialized == false) {
		intro_menu_initialized = true;
		init_introMenu();
	}
	if (event_introMenu())
		render_introMenu();
	else
		cleanup_introMenu();
}

int event_networkMenu()
{
	SDL_Point p = getMousePos();
	bool left_click = false;
	bool changed_tb = false;
	int returnValue = 1;

	// Exit on window button
	if (quitEventTriggered()) {
		setNextState(STATE_EXIT);
		returnValue = 0;
	}

	if (mouseEventPressed(SDL_BUTTON_LEFT)) {
		left_click = true;
	}

	// Back button
	if (SDL_PointInRect(&p, &btn_back.rect_box)) {
		btn_back.state = BTN_STATE_MOUSE_OVER;

		if (left_click) {
			setNextState(STATE_MAIN_MENU);
			returnValue = 0;
		}
	}
	else {
		btn_back.state = BTN_STATE_UNSELECTED;
	}

	// Play button
	if (SDL_PointInRect(&p, &btn_connect.rect_box)) {
		btn_connect.state = BTN_STATE_MOUSE_OVER;
		if (left_click) {

			

			// Testa att connecta här

			// The recieved player id of this client
			client_player_num = 0; //nollställer clientnum så att klienten får en färsk vid connection
			client_player_num = connect(client_player_num);
			sendMessage(client_player_num, "has connected");

			if (client_player_num > 3 || client_player_num < 0) //om fler än 4 spelare försöker connecta, stäng ned programmet för den som connectar
				exit(1);

			SDL_Delay(500);
			printf("try to connect here... IP %s and PORT: %s.\n", tb_ip.text, tb_port.text);
			
			// Det är stärngar så tänk på att användaren kan mata in skräp också ^^

			// Om den lyckades sätt next state till game running och returna 0 annars skapa ett nytt state för felmeddelande men returna 1.
			setNextState(STATE_GAME_RUNNING);
			returnValue = 0;
		}
	}
	else {
		btn_play.state = BTN_STATE_UNSELECTED;
	}

	// Textbox IP
	if (SDL_PointInRect(&p, &tb_ip.rect_box)) {
		tb_ip.background = t_textbox_highlighted;
		if (left_click) {
			enableTextInput();
			tb_ip.selected = true;
			tb_port.selected = false;
			changed_tb = true;
		}
	} else {
		tb_ip.background = t_textbox_active;
	}
	// Textbox Port
	if (SDL_PointInRect(&p, &tb_port.rect_box)) {
		tb_port.background = t_textbox_highlighted;
		if (left_click) {
			enableTextInput();
			tb_port.selected = true;
			tb_ip.selected = false;
			changed_tb = true;
		}
	}
	else {
		tb_port.background = t_textbox_active;
	}

	if (tb_port.selected) {
		if (keyEventHeld(SDL_SCANCODE_BACKSPACE) && isTextEventEnabled()) {
			removeLastFromTextBox(&tb_port, renderer);
		}

		if (textEvent()) {
			appendInTextBox(&tb_port, getTextInput(), renderer);
		}
	}
	else if (tb_ip.selected) {
		if (keyEventHeld(SDL_SCANCODE_BACKSPACE) && isTextEventEnabled()) {
			removeLastFromTextBox(&tb_ip, renderer);
		}

		if (textEvent()) {
			appendInTextBox(&tb_ip, getTextInput(), renderer);
		}
	}


	if (!changed_tb && left_click) {
		tb_ip.selected = false;
		tb_port.selected = false;
		disableTextInput();
	}

	return returnValue;
}

void render_networkMenu()
{
	SDL_RenderClear(renderer);
	// Render background
	rect_background.w = screenW;
	rect_background.h = screenH;
	SDL_RenderCopy(renderer, t_background, NULL, &rect_background);
	// Hud
	interface_render_plane(&networkmenu_hud, renderer);
	// Buttons
	interface_render_button(&btn_back, renderer);
	interface_render_button(&btn_connect, renderer);
	// Textbox
	interface_render_textbox(&tb_ip, renderer);
	interface_render_textbox(&tb_port, renderer);
	// labels
	interface_render_label(&l_ip, renderer);
	interface_render_label(&l_port, renderer);

	SDL_RenderPresent(renderer);
}

void execute_networkMenu()
{
	if (event_networkMenu())
		render_networkMenu();
	else {
		disableTextInput();
		cleanup_introMenu();
	}
}