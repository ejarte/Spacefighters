#include "main.h"

void initImages()
{
	//laddar in bilderna

	yellow_box = NULL;
	yellow_box = IMG_LoadTexture(renderer, "images/yellowsquare.bmp"); //laddar den gula bilden i yellow_box

	yellow_rect.x = 10;
	yellow_rect.y = 10;
	yellow_rect.w = BTNWIDTH;  //Bredd
	yellow_rect.h = BTNHEIGHT;  //Höjd

	green_box = NULL;
	green_box = IMG_LoadTexture(renderer, "images/greensquare.bmp");

	green_rect.x = 120;
	green_rect.y = 10;
	green_rect.w = BTNWIDTH;
	green_rect.h = BTNHEIGHT;

	red_box = NULL;
	red_box = IMG_LoadTexture(renderer, "images/redsquare.bmp");

	red_rect.x = 10;
	red_rect.y = 120;
	red_rect.w = BTNWIDTH;
	red_rect.h = BTNHEIGHT;

	blue_box = NULL;
	blue_box = IMG_LoadTexture(renderer, "images/bluesquare.bmp"); //laddar den gula bilden i yellow_box

	blue_rect.x = 120;
	blue_rect.y = 120;
	blue_rect.w = BTNWIDTH;  //Bredd
	blue_rect.h = BTNHEIGHT;  //Höjd
}
