#include "game.h"
#include "spaceship.h"
#include "graphics.h"
#include "sprite.h"

// Background
SDL_Rect background_rect;
SDL_Texture* background_texture;

Sprite *s1;
SDL_Rect s1_display_rect;
SDL_Rect s1_display_rect_2;

Sprite *s2;
SDL_Rect s2_display_rect;

void initGame()
{
	// Background
	background_texture = IMG_LoadTexture(renderer, "images/bakgrund_himmel.gif");
	background_rect.x = background_rect.y = 0;
	SDL_GetRendererOutputSize(renderer, &background_rect.w, &background_rect.h);


	// Sprites

	s1 = createSprite(renderer, "images/wind_eff_001.png", 5, 6);
	// The iamge coordinates.
	s1_display_rect.x = 0;
	s1_display_rect.y = 0;
	// Configures the display size to match the image frame
	s1_display_rect.w = sprite_getFrameWidth(s1);				
	s1_display_rect.h = sprite_getFrameHeight(s1);

	// Copy of sprite (s1) on another rect
	s1_display_rect_2.x = 500;
	s1_display_rect_2.y = 0;
	s1_display_rect_2.w = sprite_getFrameWidth(s1);
	s1_display_rect_2.h = sprite_getFrameHeight(s1);

	s2 = createSprite(renderer, "images/explosion1.png", 5, 5);
	s2_display_rect.x = 1000;
	s2_display_rect.y = 500;
	s2_display_rect.w = sprite_getFrameWidth(s2);
	s2_display_rect.h = sprite_getFrameHeight(s2);
}

bool hasRunOnce = false;

void gameLoop() {
	if (!hasRunOnce) {
		hasRunOnce = true;
		initGame();
	}
	gameRender();
}

int frame_row_1 = 0;
int frame_row_2 = 0;

int frame_col_1 = 0;
int frame_col_2 = 0;

int frTime = 0;

void gameRender()
{
	// Animation relaterat
	frTime++;
	if (frTime == 2)
	{
		frame_col_1++;
		frame_col_2++;

		// Gröna cirklar
		if (frame_col_1 == sprite_getColumns(s1)) {
			frame_col_1 = 0;
			frame_row_1++;
			if (frame_row_1 == sprite_getRows(s1)) {
				frame_row_1 = 0;
			}
		}

		// Explosion
		if (frame_col_2 == sprite_getColumns(s2)) {
			frame_col_2 = 0;
			frame_row_2++;
			if (frame_row_2 == sprite_getRows(s2)) {
				frame_row_2 = 0;
			}
		}
		frTime = 0;
	}

	// Adjuct background to screen dimensions
	SDL_GetRendererOutputSize(renderer, &background_rect.w, &background_rect.h);
	// Clear Screen
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background_texture, NULL, &background_rect);
	// Green circles
	sprite_RenderCopy(renderer, s1, frame_col_1, frame_row_1, s1_display_rect);
	sprite_RenderCopy(renderer, s1, frame_col_1, frame_row_1, s1_display_rect_2);
	// Explosion
	sprite_RenderCopy(renderer, s2, frame_col_2, frame_row_2, s2_display_rect);
	// Present Screen
	SDL_RenderPresent(renderer);
}