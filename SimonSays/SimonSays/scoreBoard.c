
/*	Author(s):	Farhad Salehi 
*	Modified:	09-05-2017
*	Version:	0.

*/


#include "libraries.h"
#include "graphics.h"
#include "events.h"
#include "state_handler.h"
#include "definition.h"
#include "game.h"
#include "interface_lib.h"
#include "scoreBoard.h"

//void scoreBoard_setup_label();

TTF_Font* font_roboto_black;
SDL_Rect scorePlayer1_rect;
SDL_Rect scorePlayer2_Rect;
SDL_Rect scorePlayer3_Rect;
SDL_Rect scorePlayer4_Rect;

SDL_Rect scorePlayer_rect[4][4];

int digW;
int digH;

struct Label playerNameColored[4];
SDL_Texture* digit[10];
void init_scoreboard(){

	font_roboto_black = TTF_OpenFont("fonts/roboto/Roboto-Black.ttf", 12);

	interface_setup_label(&playerNameColored[0], renderer, player[0].name, font_roboto_black, createColor(0xFF, 0, 0, 0), getWindowWidth()-150, 0, true);
   interface_setup_label(&playerNameColored[1], renderer, player[1].name, font_roboto_black, createColor(0, 0, 0xFF, 0), getWindowWidth()-150, getWindowHeight()-700, true);
   interface_setup_label(&playerNameColored[2], renderer, player[2].name, font_roboto_black, createColor(0, 0xFF, 0, 0), getWindowWidth()-150, getWindowHeight()-677, true);
   interface_setup_label(&playerNameColored[3], renderer, player[3].name, font_roboto_black, createColor(0xFF, 0x78, 0x1C, 0), getWindowWidth()-150, getWindowHeight()-654, true);

   SDL_Surface* surface;
   SDL_Color color = { 255,255,255,0 };
   surface = TTF_RenderText_Solid(font_roboto_black, "0", color);
   digit[0] = SDL_CreateTextureFromSurface(renderer, surface);

   surface = TTF_RenderText_Solid(font_roboto_black, "1", color);
   digit[1] = SDL_CreateTextureFromSurface(renderer, surface);

   surface = TTF_RenderText_Solid(font_roboto_black, "2", color);
   digit[2] = SDL_CreateTextureFromSurface(renderer, surface);

   surface = TTF_RenderText_Solid(font_roboto_black, "3", color);
   digit[3] = SDL_CreateTextureFromSurface(renderer, surface);

   surface = TTF_RenderText_Solid(font_roboto_black, "4", color);
   digit[4] = SDL_CreateTextureFromSurface(renderer, surface);

   surface = TTF_RenderText_Solid(font_roboto_black, "5", color);
   digit[5] = SDL_CreateTextureFromSurface(renderer, surface);

   surface = TTF_RenderText_Solid(font_roboto_black, "6", color);
   digit[6] = SDL_CreateTextureFromSurface(renderer, surface);

   surface = TTF_RenderText_Solid(font_roboto_black, "7", color);
   digit[7] = SDL_CreateTextureFromSurface(renderer, surface);

   surface = TTF_RenderText_Solid(font_roboto_black, "8", color);
   digit[8] = SDL_CreateTextureFromSurface(renderer, surface);

   surface = TTF_RenderText_Solid(font_roboto_black, "9", color);
   digit[9] = SDL_CreateTextureFromSurface(renderer, surface);

   digW = surface->w;
   digH = surface->h;


   /*for(int i = 0; i < 10; i++)
   {
	   surface= TTF_RenderText_Solid(font_roboto_black, "hello",color );
	   digit[i]= SDL_CreateTextureFromSurface(renderer, surface);
	   SDL_FreeSurface(surface);

   }*/

   int x0 = getWindowWidth() - 100;
   int y0 = playerNameColored[0].rect.y;
   int k1 = 5;
   int k2 = 5;

   for (int row = 0; row < 4; row++)
   {
	   for (int column = 0; column < 4; column++)
	   {
		   if (column >= 2)
		   {
			   scorePlayer_rect[row][column].x = x0 + column *(digW + k1+k2) + k2;
			   scorePlayer_rect[row][column].y = y0 + row *(digH + k1);
		   }
		   
		   else
		   {
			   scorePlayer_rect[row][column].x = x0 + column *(digW + k1+k2);
			   scorePlayer_rect[row][column].y = y0 + row *(digH + k1);
		   }
		   
		   scorePlayer_rect[row][column].w = digW;
		   scorePlayer_rect[row][column].h = digH;
	   }

   }
  

  
}

void scoreBoard_renderer()
{

	int dig1, dig0;
	dig1 = player[0].kills / 10;
	dig0 = player[0].kills % 10;
	if (player[0].kills > 9) {
		SDL_RenderCopy(renderer, digit[dig1], NULL, &scorePlayer_rect[0][0]);
		SDL_RenderCopy(renderer, digit[dig0], NULL, &scorePlayer_rect[0][1]);
	}
	else {
		SDL_RenderCopy(renderer, digit[dig0], NULL, &scorePlayer_rect[0][1]);
	}

	dig1 = player[1].kills / 10;
	dig0 = player[1].kills % 10;
	if (player[1].kills > 9) {
		SDL_RenderCopy(renderer, digit[dig1], NULL, &scorePlayer_rect[1][0]);
		SDL_RenderCopy(renderer, digit[dig0], NULL, &scorePlayer_rect[1][1]);
	}
	else {
		SDL_RenderCopy(renderer, digit[dig0], NULL, &scorePlayer_rect[1][1]);
	}

	dig1 = player[2].kills / 10;
	dig0 = player[2].kills % 10;
	if (player[2].kills > 9) {
		SDL_RenderCopy(renderer, digit[dig1], NULL, &scorePlayer_rect[2][0]);
		SDL_RenderCopy(renderer, digit[dig0], NULL, &scorePlayer_rect[2][1]);
	}
	else {
		SDL_RenderCopy(renderer, digit[dig0], NULL, &scorePlayer_rect[2][1]);
	}

	dig1 = player[3].kills / 10;
	dig0 = player[3].kills % 10;
	if (player[3].kills > 9) {
		SDL_RenderCopy(renderer, digit[dig1], NULL, &scorePlayer_rect[3][0]);
		SDL_RenderCopy(renderer, digit[dig0], NULL, &scorePlayer_rect[3][1]);
	}
	else {
		SDL_RenderCopy(renderer, digit[dig0], NULL, &scorePlayer_rect[3][1]);
	}
	/*
	for (int row = 0; row < 4; row++)
	{
		for (int column = 0; column < 4; column++)
		{
			SDL_RenderCopy(renderer, digit[0], NULL, &scorePlayer_rect[row][column]);
		}
	}
	*/
}

/*void scoreBoard_setup_label(struct Label* l, SDL_Renderer* renderer, char* text, TTF_Font* f, SDL_Color color, int x, int y, bool show)
{
	SDL_Surface* surface = TTF_RenderText_Solid(f, 0, color);
	l->texture = SDL_CreateTextureFromSurface(renderer, surface);
	l->rect.x = x;
	l->rect.y = y;
	l->rect.w = surface->w;
	l->rect.h = surface->h;
	l->show = show;
	SDL_FreeSurface(surface);
	l->attached = false;
}*/
