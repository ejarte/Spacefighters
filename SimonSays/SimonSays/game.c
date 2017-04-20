#include "game.h"
#include "spaceship.h"
#include "graphics.h"
#include "sprite.h"
#include "animation.h"
#include "effect.h"
#include "object.h"
#include "events.h"
#include "state_handler.h"

// Background
SDL_Rect background_rect;
SDL_Texture* background_texture;

// Sprites
Sprite *s1;
Sprite *s2;
Sprite *s3;

// Animations
Animation *a1;
Animation *a2;
Animation *a3;
Animation *a4;

// Objects
Object *o1;
Object *o2;
Object *o3;

Object *o4;	// Spaceship test

// Spaceship
Spaceship *ship_1;

Effect *e1; 

#define OBJ_TYPE_GREENWIND 1
#define OBJ_TYPE_SPACESHIP 2
#define OBJ_TYPE_EXPLOSION 3

Sprite* sprite[100];				
Animation* animation[100];
Object* object[100];

void initGame()
{
	// Background
	background_texture = IMG_LoadTexture(renderer, "images/bakgrund_himmel.gif");
	background_rect.x = background_rect.y = 0;
	SDL_GetRendererOutputSize(renderer, &background_rect.w, &background_rect.h);

	// Sprites

		// Green wind effect
		s1 = createSprite(renderer, "images/wind_eff_001.png", 5, 6, createColor(0, 0, 0, 0));

		// Skybuster Explosion
		s2 = createSprite(renderer, "images/skybusterexplosion.png", 4, 5, createColor(0, 0, 0, 0));

		// Silly Spaceship
		s3 = createSprite(renderer, "images/spaceship.png", 4, 2, createColor(0, 0, 0, 0));

		// test kopia av s3
		sprite[3] = createSprite(renderer, "images/spaceship.png", 4, 2, createColor(0, 0, 0, 0));



	// Animations
		int frameTime = 2;

		// Green wind animation
		a1 = createAnimation(5*6, frameTime);
		for (int r = 0; r < 6; r++) {
			for (int c = 0; c < 5; c++) 
				anim_addFrameColRow(a1, c, r);
		}

		// Skybuster Explosion
		a2 = createAnimation(4*5, frameTime);
		for (int r = 0; r < 5; r++) {
			for (int c = 0; c < 4; c++) 
				anim_addFrameColRow(a2, c, r);
		}

		// Silly spaceship moving
		a3 = createAnimation(4 * 1, frameTime);
		for (int c = 0; c < 4; c++) {
			anim_addFrameColRow(a3, c, 1);
		}

		// testkopia av a3
		animation[3] = createAnimation(4 * 1, frameTime);
		for (int c = 0; c < 4; c++) {
			anim_addFrameColRow(animation[3], c, 1);
		}

	// Pre-existing Objects

		o1 = createObject(OBJ_TYPE_GREENWIND, 100, 100, sprite_getFrameWidth(s1), sprite_getFrameHeight(s1), 1., &s1, a1, true, true);

		o2 = createObject(OBJ_TYPE_EXPLOSION, 800, 600, sprite_getFrameWidth(s2), sprite_getFrameHeight(s2), 1., &s2, a2, true, true);

		o3 = createObject(OBJ_TYPE_SPACESHIP, 880, 100, sprite_getFrameWidth(s3), sprite_getFrameHeight(s3), 1., &s3, a3, true, true);

		// testkopia av o3

		object[3] = createObject(OBJ_TYPE_SPACESHIP, 880, 400, sprite_getFrameWidth(s3), sprite_getFrameHeight(s3), 1., &sprite[3], animation[3], true, true);



		object_setScale(o3, 3.);
		object_hide(o3);
		object_show(o3);
		object_setCollision(o3, false);


	// Spaceship

		//object_hide(o3);

	// false = repeterar
	// true kör bara en gång
	//e1 = createEffect(&s2, a2, true);      
	//printf("effect created\n");

}

bool hasRunOnce = false;
void gameLoop() {
	if (!hasRunOnce) {
		hasRunOnce = true;
		initGame();
	}
	gameLogic();
	gameRender();
}

/*
soundEffect = Mix_LoadWAV("sounds/buttonpop.wav");
Mix_PlayChannel(-1, soundEffect, 0);
*/



int i = 0;

void gameLogic()
{
	if (quitEventTriggered())
		setNextState(STATE_EXIT);

	double scale = object_getScale(o3);





	// Funka ej
	if (object_checkForBoxCollision(o3, o2)) {
		//printf("Collision!\n");
	}
	else {
		//printf("moving!\n");
		object_setPosY(o3, object_getPosY(o3) - 1);
	}
	


}

void gameRender()
{

	SDL_GetRendererOutputSize(renderer, &background_rect.w, &background_rect.h);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background_texture, NULL, &background_rect);

	if (o1 != NULL) {
		object_render(renderer, o1);
		object_tickAnimation(o1);
	}

	if (o2 != NULL) {
		object_render(renderer, o2);
		object_tickAnimation(o2);
	}

	if (o3 != NULL) {
		object_render(renderer, o3);
		object_tickAnimation(o3);

	}

	if (object[3] != NULL) {
		object_render(renderer, object[3]);
		object_tickAnimation(object[3]);
	}

	i++;
	if (i % 5 == 0) {
		object_addToFacingAngle(o3, 3.);
	}
	SDL_RenderPresent(renderer);
}