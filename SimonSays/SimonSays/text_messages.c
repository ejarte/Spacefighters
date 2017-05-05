#include "text_messages.h"
#include "events.h"

#define MAX_LINES 30	

struct Text_Line line[MAX_LINES];

int dist_k;

TTF_Font* font_roboto_black;
SDL_Color white;

int h = 20;

// font_roboto_black = TTF_OpenFont("fonts/roboto/Roboto-Black.ttf", 12);
// interface_setup_label(&playerNameColored[0], renderer, player[0].name, font_roboto_black, createColor(0xFF, 0, 0, 0), 100, 100, true);

void init_text_messages()
{
	font_roboto_black = TTF_OpenFont("fonts/roboto/Roboto-Black.ttf", 12);
	white = createColor(0xFF, 0xFF, 0xFF, 0);
	dist_k = 10;

	current_lines = 0;
}

void addPlayerMessageToDisplay(SDL_Renderer* rend, int p_id, char* msg, int time_seconds)
{
	for (int i = current_lines; i > 0; i--) {
		line[i] = line[i - 1];
		for (int j = 0; j < line[i].size; j++) {
			line[i].label[j].rect.y -= h;
		}
	}
	interface_setup_label(&line[0].label[0], rend, player[p_id].name, font_roboto_black, player[p_id].sdl_color, 50, getWindowHeight() - 100, true);
	interface_setup_label(&line[0].label[1], rend, msg, font_roboto_black, white, 50 + line[0].label[0].rect.w + dist_k, getWindowHeight() - 100, true);
	line[0].end_time = SDL_GetTicks() + time_seconds * 1000;
	line[0].size = 2;
	current_lines++;
}

void renderMessageDisplay(SDL_Renderer* rend)
{
	printf("rendering text msg\n");
	int time = SDL_GetTicks();
	for (int i = current_lines - 1; i >= 0; i--) {
		for (int j = 0; j < line[i].size; j++) {
			if (line[i].end_time > time) {
				SDL_RenderCopy(rend, line[i].label[j].texture, NULL, &line[i].label[j].rect);
			}
			else {
				current_lines--;
			}
		}
	}
}