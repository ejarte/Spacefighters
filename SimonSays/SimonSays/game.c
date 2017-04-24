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

// Background
SDL_Rect background_rect;
SDL_Texture* background_texture;


// old test 
Effect *e1; 

#define OBJ_TYPE_GREENWIND			1
#define OBJ_TYPE_SPACESHIP			2
#define OBJ_TYPE_EXPLOSION			3
#define OBJ_TYPE_BLACKHOLE			4
#define OBJ_TYPE_ASTEROID			5
#define OBJ_TYPE_ITEM_HEALTH		6
#define OBJ_TYPE_ITEM_INVUL			7
#define OBJ_TYPE_ITEM_SPEED			8

Sprite* sprite[100];				
Animation* animation[100];
Spaceship* spaceship[20];

void game_init()
{
	// Object Indexer
	initObjectIndex();

	// Background
	background_texture = IMG_LoadTexture(renderer, "images/bakgrund_himmel.gif");
	background_rect.x = background_rect.y = 0;
	SDL_GetRendererOutputSize(renderer, &background_rect.w, &background_rect.h);

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
		tempObj = createObject(OBJ_TYPE_BLACKHOLE, 500, 500, sprite_getFrameWidth(sprite[4]) / 4, sprite_getFrameHeight(sprite[4]) / 4, 0, 0, sprite[4], animation[0]);

		// Asteroids without collision added
		tempObj = createObject(OBJ_TYPE_ASTEROID, 900, 700, sprite_getFrameWidth(sprite[5]) / 4, sprite_getFrameHeight(sprite[5]) / 4, 0, 0, sprite[5], animation[5]);
		tempObj = createObject(OBJ_TYPE_ASTEROID, 600, 600, sprite_getFrameWidth(sprite[5]) / 4, sprite_getFrameHeight(sprite[5]) / 4, 0, 0, sprite[5], animation[6]);
		tempObj = createObject(OBJ_TYPE_ASTEROID, 200, 800, sprite_getFrameWidth(sprite[5]) / 4, sprite_getFrameHeight(sprite[5]) / 4, 0, 0, sprite[5], animation[7]);
		tempObj = createObject(OBJ_TYPE_ASTEROID, 400, 800, sprite_getFrameWidth(sprite[5]) / 4, sprite_getFrameHeight(sprite[5]) / 4, 0, 0, sprite[5], animation[8]);
		tempObj = createObject(OBJ_TYPE_ASTEROID, 500, 800, sprite_getFrameWidth(sprite[5]) / 4, sprite_getFrameHeight(sprite[5]) / 4, 0, 0, sprite[5], animation[9]);
		tempObj = createObject(OBJ_TYPE_ASTEROID, 600, 800, sprite_getFrameWidth(sprite[5]) / 4, sprite_getFrameHeight(sprite[5]) / 4, 0, 0, sprite[5], animation[10]);
		tempObj = createObject(OBJ_TYPE_ASTEROID, 660, 800, sprite_getFrameWidth(sprite[5]) / 4, sprite_getFrameHeight(sprite[5]) / 4, 0, 0, sprite[5], animation[11]);
		tempObj = createObject(OBJ_TYPE_ASTEROID, 720, 800, sprite_getFrameWidth(sprite[5]) / 4, sprite_getFrameHeight(sprite[5]) / 4, 0, 0, sprite[5], animation[12]);

	// Pre-existing Objects

		//Object* createObject(int type, int x, int y, int w, int h, double facingAngle, double facingOffset, Sprite *s, Animation *a);


		//o1 = createObject(OBJ_TYPE_GREENWIND, 100, 100, sprite_getFrameWidth(s1), sprite_getFrameHeight(s1), 1., s1, a1, true, true);
		//o2 = createObject(OBJ_TYPE_EXPLOSION, 800, 600, sprite_getFrameWidth(s2), sprite_getFrameHeight(s2), 1., s2, a2, true, true);

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

		// Declaration
		//spaceship[0] = createSpaceship(x, y, facing, body);
		//spaceship_setWeight(spaceship[0], weight);

		//spaceship[1] = createSpaceship(999, 500, 120, createObjectCopy(body, 600, 600, 180));

		//int* i = object_getPointerToX(body);


		//printf("HERE\n\n\n");
		//object_setPosXY(body, 100, 100);
		//printf("%d\n", &i);
		//SDL_Delay(4000);

		//object_setTexture(body, s2);
		//object_setB

		//object_print(body);	

		// Collision test

		//c = createCollisionBox(500, 500, 50, 50);
		//cc = createCollisionBox(600, 500, 50, 50);

		//collision_setBoxHeight(cc, 100);

		//collision_setBoxWidth(cc, 100);


}

void game_execute() {
	game_events();
	game_update();
	game_render();
}

void game_events()
{
	Object* tempObj;

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
			// Rotate test
			if (keyEventHeld(SDL_SCANCODE_Q)) {
				tempObj = spaceship_getBody(spaceship[0]);
				object_addFacingAngle(tempObj, -3);
			}
			if (keyEventHeld(SDL_SCANCODE_E)) {
				tempObj = spaceship_getBody(spaceship[0]);
				object_addFacingAngle(tempObj, 3);
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
	// Move spaceship
	spaceship_move(spaceship[0]);
	spaceship_move(spaceship[1]);

	// Loop through all objects
	for (int i = 0; i < getObjectIndexMax(); i++) {

		// Collision Detection
		for (int j = i + 1; j < getObjectIndexMax(); j++) {
			if (object_checkForBoxCollision(object[i], object[j])) {
				printf("collision detected between object %d and %d.\n", i, j);


				if (object_getTypeId(object[i]) == OBJ_TYPE_SPACESHIP) {
					// prevents futher movement
					object_clearDeltaXY(object[i]);
					object_clearDeltaXY(object[j]);
				}
			}
		}
		// Rotate blackhole
		if (object_getTypeId(object[i]) == OBJ_TYPE_BLACKHOLE) {
			object_addFacingAngle(object[i], 0.5);
		}
	}
}


void game_render()
{
	// Size
	SDL_GetRendererOutputSize(renderer, &background_rect.w, &background_rect.h);
	// Clear previous display
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, background_texture, NULL, &background_rect);

	// Handle all objects in the game
	for (int i = 0; i < getObjectIndexMax(); i++) {
		if (object[i] != NULL) {
			object_tick(object[i]);
			object_render(renderer, object[i]);
		}
	}
	SDL_RenderPresent(renderer);
}