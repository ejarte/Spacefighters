#include "intro_menu.h"
#include "state_handler.h"
#include "definition.h"
#include "graphics.h"
#include "interface_lib.h"

TTF_Font* kenvector_future;
TTF_Font* kenvector_future_thin;
SDL_Texture* t_background;
SDL_Texture* t_panel;

SDL_Rect rect_background;

struct Plane plane;

bool quit_intro_menu = false;

//void interface_setup_plane(struct Plane* p, SDL_Texture* texture, int x, int y, int w, int h, bool show)
void init_introMenu()
{
	kenvector_future = TTF_OpenFont("fonts/kenvector_future.ttf", 12);
	kenvector_future_thin = TTF_OpenFont("fonts/kenvector_future_thin.ttf", 12);
	t_background = IMG_LoadTexture(renderer, "images/skyBackground.png");


	t_panel = IMG_LoadTexture(renderer, "images/Interface/uipack/PNG/grey_panel.png");
	rect_background.x = rect_background.y = 0;

//	interface_setup_plane(&plane, t_panel, 200, 200, 100, 100, true);

	interface_setup_plane(&plane, t_panel, 200, 200, 100, 50, true);

}

void cleanup_introMenu()
{

}

void event_introMenu()
{

}

void render_introMenu()
{
	rect_background.w = screenW;
	rect_background.h = screenH;
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, t_background, NULL, &rect_background);
	interface_render_plane(&plane, renderer);
	SDL_RenderPresent(renderer);
}

void execute_introMenu()
{

	event_introMenu();
	render_introMenu();
	if (!quit_intro_menu) {
		event_introMenu();
		render_introMenu();
	}
	else {
		cleanup_introMenu();
		if (!getNextState() == STATE_EXIT)
			setNextState(STATE_GAME_RUNNING);
	}
}