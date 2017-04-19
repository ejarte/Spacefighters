#include "game.h"
#include "spaceship.h"
#include "graphics.h"
#include "sprite.h"
#include "animation.h"
#include "effect.h"

// Background
SDL_Rect background_rect;
SDL_Texture* background_texture;

Sprite *s1;
SDL_Rect s1_display_rect;
SDL_Rect s1_display_rect_2;

Sprite *s2;
SDL_Rect s2_display_rect;

Animation *a1;
Animation *a2;

Effect *e1;

void initGame()
{
	// Background
	background_texture = IMG_LoadTexture(renderer, "images/bakgrund_himmel.gif");
	background_rect.x = background_rect.y = 0;
	SDL_GetRendererOutputSize(renderer, &background_rect.w, &background_rect.h);

	// Sprites

	s1 = createSprite(renderer, "images/wind_eff_001.png", 5, 6, createColor(0, 0, 0, 0));
	// Skapar en display rect med x, y, w, h
	s1_display_rect = createRect(0, 0, sprite_getFrameWidth(s1), sprite_getFrameHeight(s1));
	// Copy of sprite (s1) on another rect
	s1_display_rect_2 = createRect(500, 0, sprite_getFrameWidth(s1), sprite_getFrameHeight(s1));

	s2 = createSprite(renderer, "images/skybusterexplosion.png", 4, 5, createColor(0, 0, 0, 0));
	s2_display_rect = createRect(1000, 500, sprite_getFrameWidth(s2), sprite_getFrameHeight(s2));

	int t_frameTime = 2;	// Så ni ser vad det är för något

	// Antal frames samt frame time i in parametern
	a1 = createAnimation(5*6, t_frameTime);
	for (int r = 0; r < 6; r++) {
		for (int c = 0; c < 5 ; c++) {
			anim_addFrameColRow(a1, c, r);
		}
	}

	a2 = createAnimation(4*5, t_frameTime);
	for (int r = 0; r < 5; r++) {
		for (int c = 0; c < 4; c++) {
			anim_addFrameColRow(a2, c, r);
		}
	}

	// false = repeterar
	// true kör bara en gång
	e1 = createEffect(&s2, a2, true);      
	
	printf("effect created\n");

}

bool hasRunOnce = false;

void gameLoop() {
	if (!hasRunOnce) {
		hasRunOnce = true;
		initGame();
	}
	gameRender();
}

/*
soundEffect = Mix_LoadWAV("sounds/buttonpop.wav");
Mix_PlayChannel(-1, soundEffect, 0);

*/


SDL_Rect disp_rect;

bool has_reset = false;

void gameRender()
{
	//Mix_Chunk* soundEffect2 = Mix_LoadWAV("audio/sounds/granade1.wav");
	//Mix_PlayChannel(-1, soundEffect2, 0);
	//playSound(-1, "audio/sounds/granade1.wav", 0);
	//SDL_Delay(2000);
	//return;

	// Ticka animationer
	//anim_tick(a1);


	//anim_tick(a2);

	// Adjuct background to screen dimensions
	SDL_GetRendererOutputSize(renderer, &background_rect.w, &background_rect.h);
	// Clear Screen
	SDL_RenderClear(renderer);
	// Background
	SDL_RenderCopy(renderer, background_texture, NULL, &background_rect);
	
	
	// Green circles
	
	//sprite_RenderCopy(renderer, s1, anim_getCurCol(a1), anim_getCurRow(a1), s1_display_rect);

	disp_rect = createRect(0, 0, sprite_getFrameWidth(s1), sprite_getFrameHeight(s1));
	if (e1 != NULL) {
		effect_tick(e1);
		effect_render(renderer, e1, disp_rect);
	}


	//if (SDL_GetTicks() > 3000 && !has_reset) {
	//	effect_reset(e1);
	//	has_reset = true;
	//}


	//sprite_RenderCopy(renderer, s1, anim_getCurCol(a1), anim_getCurRow(a1), s1_display_rect_2);
	// Explosion
	//sprite_RenderCopy(renderer, s2, anim_getCurCol(a2), anim_getCurRow(a2), s2_display_rect);
	// Present Screen
	SDL_RenderPresent(renderer);
}