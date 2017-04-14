#include "main.h"
#include "graphics_lib.h"

void initImages()
{
	//laddar in bilderna
	SDL_GetRendererOutputSize(renderer, &screenW, &screenH);

	if (boxW < boxH)
	{
		boxW = screenW/4;
		boxH = boxW;
	} else
	{
		boxH = screenH/4;
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
	blue_rect.y = 20 + boxH + (boxH * 0.2);;
	blue_rect.w = boxW;  //Bredd
	blue_rect.h = boxH;  //10 + (screenW / 2)
}
