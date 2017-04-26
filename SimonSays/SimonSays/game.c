#include "game.h"
#include "spaceship.h"
#include "graphics.h"
#include "sprite.h"
#include "animation.h"
#include "effect.h"
#include "object.h"
#include "events.h"
#include "state_handler.h"
#include "world.h"
#include "collision.h"
#include "projectile.h"

// Background
//SDL_Rect background_sky_rect;
//SDL_Texture* background_sky_texture;


SDL_Rect background_rect;

SDL_Rect back_rect;
SDL_Texture *backgroundImage;

SDL_Rect stars_rect;
SDL_Texture* stars_box;
SDL_Texture *starsImage;

// old test 
Effect *e1; 

Sprite* sprite[100];				
Animation* animation[100];
Spaceship* spaceship[20];

/*
#define STARS "images/skyForeground.png"
#define SKY "images/skyBackground.png"

*/


void game_init()
{
	// Init World
	initWorld();


	// Object Indexer
	initObjectIndex();

	// Background
	backgroundImage = IMG_LoadTexture(renderer, "images/skyBackground.png");
	background_rect.x = background_rect.y = 0;
	starsImage = IMG_LoadTexture(renderer, "images/skyForeground.png");
	stars_rect.x = stars_rect.y = 0;
	stars_rect.w = stars_rect.h = 800;

	// Sprites
	// Green wind effect
	sprite[1] = createSprite(renderer, "images/wind_eff_001.png", 5, 6, createColor(0, 0, 0, 0));
	// Skybuster Explosion
	sprite[2] = createSprite(renderer, "images/skybusterexplosion.png", 4, 5, createColor(0, 0, 0, 0));
	// Silly Spaceship
	sprite[3] = createSprite(renderer, "images/spaceship.png", 4, 2, createColor(0, 0, 0, 0));
	// Blue blackhole
	sprite[4] = createSprite(renderer, "images/blackhole_blue.png", 1, 1, createColor(0, 0, 0, 0));
	// Gray asteroids
	sprite[5] = createSprite(renderer, "images/asteroid_01.png", 8, 8, createColor(0, 0, 0, 0)); 

	// Animations
	int frameTime = 2;

	animation[0] = createAnimation(1, 2);
	anim_addFrameColRow(animation[0], 0, 0);

	// Green wind animation
	animation[1] = createAnimation(5*6, frameTime);
	for (int r = 0; r < 6; r++) {
		for (int c = 0; c < 5; c++) 
			anim_addFrameColRow(animation[1], c, r);
	}

	// Skybuster Explosion
	animation[2] = createAnimation(4*5, frameTime);
	for (int r = 0; r < 5; r++) {
		for (int c = 0; c < 4; c++) 
			anim_addFrameColRow(animation[2], c, r);
	}

	// Silly spaceship moving
	animation[3] = createAnimation(4 * 1, frameTime);
	for (int c = 0; c < 4; c++) {
		anim_addFrameColRow(animation[3], c, 1);
	}
	animation[4] = createAnimation(4 * 1, frameTime);
	for (int c = 0; c < 4; c++) {
		anim_addFrameColRow(animation[4], c, 1);
	}

	// Asteroid Animations
	for (int i = 5; i <= 12; i++) {
		animation[i] = createAnimation(8, 7);
		for (int c = 0; c < 8; c++) {
			anim_addFrameColRow(animation[i], c, i - 5);
		}
	}

		Object* tempObj;

		// Blackhole
		//tempObj = createObject(OBJ_TYPE_BLACKHOLE, 500, 500, sprite_getFrameWidth(sprite[4]) / 4, sprite_getFrameHeight(sprite[4]) / 4, 0, 0, sprite[4], animation[0]);
	

	// Pre-existing Objects

		//object_disableCollision(o3);

 
		// Pointer test
		//int i = 5;
		//int* p1 = &i;
		//int* p2 = p1; // P2 pekar nu också på i
		//(*p2) = 7;	// i = 7

		//printf("%d %d %d \n", i, *p1, *p2);

		// P2 pekar nu på p3 angle
		//object_setFacingAnglePtr(o2, object_getFacingAnglePtr(o3));
		// När jag ändrar p3 kommer då alltså p3 att ändras!
		//object_setFacingAngle(o3, 270);
		//object_setFacingAngle(o2, 90);
		//object_setDeltaX(o3, 1);

		//SDL_Point* p = object_getPosPtr(o3);
		//c = createCollisionBox(p, 50, 50);

		//SDL_Point* p = object_getCenterPosPtr(o3);
		//p->x = 5;
		//object_print(o3);


	// Spaceship

		// Spaceship config
		double drag, max_speed, acceleration, weight;
		acceleration = 0.2;
		drag = 0.90;
		max_speed = 4.;

		// Spaceship 1
		tempObj = createObject(OBJ_TYPE_SPACESHIP, 100, 100, sprite_getFrameWidth(sprite[3]) / 2, sprite_getFrameHeight(sprite[3]) / 2, 0, 0, sprite[3], animation[3]);
		object_setCollisionBoxDimension(tempObj, 60, 60, 0, 0);
		spaceship[0] = createSpaceship(tempObj);
		spaceship_setDrag(spaceship[0], drag);
		spaceship_setAcceleration(spaceship[0], acceleration);
		spaceship_setMaxSpeed(spaceship[0], max_speed);	

		tempObj = createObject(OBJ_TYPE_SPACESHIP, 800, 100, sprite_getFrameWidth(sprite[3]) / 2, sprite_getFrameHeight(sprite[3]) / 2, 0, 0, sprite[3], animation[3]);
		object_setCollisionBoxDimension(tempObj, 60, 60, 0, 0);
		spaceship[1] = createSpaceship(tempObj);
		spaceship_setDrag(spaceship[1], drag);
		spaceship_setAcceleration(spaceship[1], acceleration);
		spaceship_setMaxSpeed(spaceship[1], max_speed);
}

void game_execute() {
	game_events();
	game_update();
	game_render();
}

void game_events()
{
	Object* tempObj;
	//int x, y;

	if (quitEventTriggered()) {
		setNextState(STATE_EXIT);
		return;
	}

	// Prevents the user from controlling when text event is enabled	
	if (isTextEventEnabled()) {

		// Sends or terminates the chat mode
		if (keyEventPressed(SDL_SCANCODE_RETURN)) {
			printf("send message...\n");
			disableTextInput();
		}
	}
	else {
		// Starts chat mode
		if (keyEventPressed(SDL_SCANCODE_RETURN)) {
			enableTextInput();
			printf("recording message... Cannot move.\n");
		}
		else {

			// Shoot 

			if (mouseEventPressed(SDL_BUTTON_LEFT)) {
				spawnNormalProjectile(spaceship[0]);
			}

			// Movement ship A
			if (keyEventHeld(SDL_SCANCODE_W)) {
				spaceship_deaccelerateY(spaceship[0]);
			}
			if (keyEventHeld(SDL_SCANCODE_S)) {
				spaceship_accelerateY(spaceship[0]);
			}
			if (keyEventHeld(SDL_SCANCODE_A)) {
				spaceship_deaccelerateX(spaceship[0]);
			}
			if (keyEventHeld(SDL_SCANCODE_D)) {
				spaceship_accelerateX(spaceship[0]);
			}

			// TEST - GENERATE ASTEROID ON Z
			if (keyEventPressed(SDL_SCANCODE_Z)) {
				spawnEnteringAsteroid();
			}

			// Movement ship B
			if (keyEventHeld(SDL_SCANCODE_UP)) {
				spaceship_deaccelerateY(spaceship[1]);
			}
			if (keyEventHeld(SDL_SCANCODE_DOWN)) {
				spaceship_accelerateY(spaceship[1]);
			}
			if (keyEventHeld(SDL_SCANCODE_LEFT)) {
				spaceship_deaccelerateX(spaceship[1]);
			}
			if (keyEventHeld(SDL_SCANCODE_RIGHT)) {
				spaceship_accelerateX(spaceship[1]);
			}
		}
	}
}

void game_update()
{
	Object* tempObj;

	// Rotate spaceship to look at mouse position
	spaceship_setFacingToPoint(spaceship[0], getMousePos());		

	// Move spaceship if inside world
	for (int i = 0; i < 2; i++) {
		tempObj = spaceship_getBody(spaceship[i]);
		spaceship_move(spaceship[i]);
	}

	int removedObject[100];
	int removedIndex = 0;

	// Loop through all objects
	for (int i = 0; i < getObjectIndexMax(); i++) {
		
		//Prevents spaceships from leaving the world
		if (!isInsideWorld(object[i])) {
			printf("Object[%d] has left the world\n");
		}
		// prevents nullpointer reference crash
		if (object[i] != NULL) { 
			// Check if still inside world

			// Collision Detection
			for (int j = i + 1; j < getObjectIndexMax(); j++) {
				// prevents nullpointer reference crash
				if (object[j] != NULL) {
					if (object_checkForCollision(object[i], object[j])) {

						/*
						if (object_getTypeId(object[i]) == OBJ_TYPE_SPACESHIP) {
							printf("spaceship collided with ");
							printf("Do nothing... source\n");
						}
						*/
						if (object_getTypeId(object[i]) == OBJ_TYPE_PROJECTILE) {
							if (projectile_isSource(object[i], object[j]) == false) {
								//removedObject[removedIndex++] = i;
							}
						}
						if (object_getTypeId(object[i]) == OBJ_TYPE_ASTEROID) {
							//printf("asteroid collided with ");
						}
						if (object_getTypeId(object[j]) == OBJ_TYPE_SPACESHIP) {
						//	printf("spaceship...\n");
						}
						if (object_getTypeId(object[j]) == OBJ_TYPE_PROJECTILE) {
							if (projectile_isSource(object[j], object[i])) {
								//printf("Do nothing... source\n");
							}
							else {
								//removedObject[removedIndex++] = j;
								//printf("projectile...\n");
							}
						}
						if (object_getTypeId(object[j]) == OBJ_TYPE_ASTEROID) {
							//printf("asteroid...\n");
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < removedIndex; i++) {
		//printf("removed index: %d\n", removedObject[i]);
		object_disableCollision(object[removedObject[i]]);
		destroyObject(object[removedObject[i]]);
	}
}

void game_render()
{
	// Clear previous display
	SDL_RenderClear(renderer);

	Object* tempObj = spaceship_getBody(spaceship[0]);
	int x = object_getX(tempObj);
	int y = object_getY(tempObj);

	stars_rect.x = x / 10;
	stars_rect.y = y / 10;
	// Back
	back_rect.x = x / 15;
	back_rect.y = y / 15;

	SDL_GetRendererOutputSize(renderer, &screenW, &screenH);
	background_rect.w = screenW;
	background_rect.h = screenH;

	back_rect.w = background_rect.w;
	back_rect.h = background_rect.h;

	SDL_RenderCopy(renderer, backgroundImage, &back_rect, &background_rect);
	SDL_RenderCopy(renderer, starsImage, &stars_rect, &background_rect);

	// Handle all objects in the game
	for (int i = 0; i < getObjectIndexMax(); i++) {
		if (object[i] != NULL) {
			object_tick(object[i]);
			object_render(renderer, object[i], true);
		}
	}
	SDL_RenderPresent(renderer);
}