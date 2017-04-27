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
#include "text_commands.h"

// Background

bool collided = false;
SDL_Rect background_rect;

SDL_Rect back_rect;
SDL_Texture *backgroundImage;

SDL_Rect stars_rect;
SDL_Texture* stars_box;
SDL_Texture *starsImage;


Sprite* sprite[100];				
Animation* animation[100];
Spaceship* spaceship[20];

char* user_input;
#define MSG_MAX_CHAR 200

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
		max_speed = 40;

		// Spaceship 1
		tempObj = createObject(OBJ_TYPE_SPACESHIP, 100, 100, sprite_getFrameWidth(sprite[3]) / 2, sprite_getFrameHeight(sprite[3]) / 2, 0, 0, sprite[3], animation[3]);
		object_setCollisionBoxDimension(tempObj, 60, 60, 0, 0);
		object_setLife(tempObj, 20);
		spaceship[0] = createSpaceship(tempObj);
		spaceship_setDrag(spaceship[0], drag);
		spaceship_setAcceleration(spaceship[0], acceleration);
		spaceship_setMaxSpeed(spaceship[0], max_speed);	
		spaceship_setMass(spaceship[0]);


		tempObj = createObject(OBJ_TYPE_SPACESHIP, 800, 100, sprite_getFrameWidth(sprite[3]) / 2, sprite_getFrameHeight(sprite[3]) / 2, 0, 0, sprite[3], animation[3]);
		object_setCollisionBoxDimension(tempObj, 60, 60, 0, 0);
		object_setLife(tempObj, 20);
		spaceship[1] = createSpaceship(tempObj);
		spaceship_setDrag(spaceship[1], drag);
		spaceship_setAcceleration(spaceship[1], acceleration);
		spaceship_setMaxSpeed(spaceship[1], max_speed);
		spaceship_setMass(spaceship[1]);

		// Test
		spawnAteroidTest();
}

//======================================================================================================
// Game Execution
//======================================================================================================

void game_execute() {
	game_events();
	game_update();
	game_render();
}

//======================================================================================================
// Game Events
//======================================================================================================

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
			if (!runCommands(user_input)) {
				printf("MSG: %s\n", user_input);
			}
			disableTextInput();
			free(user_input);	// Deallocates the memory used
		}
		else {
			if (textEvent()) {
				strcat(user_input, getTextInput());
				printf("s: %s\n", getTextInput());
			}
		}
	}
	else {
		// Starts chat mode
		if (keyEventPressed(SDL_SCANCODE_RETURN)) {
			enableTextInput();
			user_input = malloc(MSG_MAX_CHAR);	// allocates memory for the chat message
			user_input[0] = '\0';
			printf("Type in your message...\n");
		}
		else {


			// Shoot 
			if (mouseEventHeld(SDL_BUTTON_LEFT)) {

				if (!spaceship_isGunOnCooldown(spaceship[0])) {
					spaceship_setCooldownExpiration(spaceship[0]);
					spawnNormalProjectile(spaceship[0]);
				}
			}

			if (mouseEventHeld(SDL_BUTTON_RIGHT)) {
				if (!spaceship_isGunOnCooldown(spaceship[0])) {
					spaceship_setCooldownExpiration(spaceship[0]);
					spawnProjectileSpecial_1(spaceship[0]);
				}
			}

			// Movement ship A
			if (collided == false)
			{
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

//======================================================================================================
// Game Logic
//======================================================================================================

// Vad var detta??
SDL_Point returnColPos(Spaceship * s1, Spaceship * s2)
{
	SDL_Point newDirection;
	int distance = 100;
	int newXspeed, newYspeed;
	newDirection = spaceship_getPosition(s1);
	newDirection.x -= - (10 * spaceship_getSpeedX(s1));
	newDirection.y -= - (10 * spaceship_getSpeedY(s1));

	return newDirection;
}

// Vad var detta?
void spaceshipCollided(Spaceship * s1, Spaceship * s2)
{
	collided = true;
	Object* o1 = spaceship_getBody(s1);
	//printf("%d\n", object_getDeltaX(o1));
	//object_setDeltaX(o1, -10);
	//printf("%d\n", object_getDeltaX(o1));
	//spaceship_deaccelerateX(s1);
	//printf()//
}


int list_objectsFound[100];
int foundIndex;

int list_objectsToRemove[100];
int removeIndex;

int getCollisionObjects(int curIndex)
{
	for (int i = curIndex + 1; i < getObjectIndexMax(); i++) {
		if (object[i] != NULL) {
			if (object_checkForCollision(object[curIndex], object[i])) {
				list_objectsFound[foundIndex++] = i;
			}
		}
	}
	return foundIndex;
}

bool varifyAsteroidAndProjectileCollision(int i, int k, int* ptr_projectile, int* ptr_asteroid)
{
	if (object_getTypeId(object[k]) == OBJ_TYPE_PROJECTILE && object_getTypeId(object[i]) == OBJ_TYPE_ASTEROID) {
		*ptr_projectile = k;
		*ptr_asteroid = i;
		return true;
	}
	if (object_getTypeId(object[i]) == OBJ_TYPE_PROJECTILE && object_getTypeId(object[k]) == OBJ_TYPE_ASTEROID) {
		*ptr_projectile = i;
		*ptr_asteroid = k;
		return true;
	}
	return false;
}

bool varifySpaceshipAndProjectileCollision(int i, int k, int* ptr_projectile, int* ptr_spaceship)
{
	if (object_getTypeId(object[k]) == OBJ_TYPE_PROJECTILE && object_getTypeId(object[i]) == OBJ_TYPE_SPACESHIP) {
		*ptr_projectile = k;
		*ptr_spaceship = i;
		return true;
	}
	if (object_getTypeId(object[i]) == OBJ_TYPE_PROJECTILE && object_getTypeId(object[k]) == OBJ_TYPE_SPACESHIP) {
		*ptr_projectile = i;
		*ptr_spaceship = k;
		return true;
	}
	return false;
}

bool varifySpaceshipAndAsteroidCollision(int i, int k, int* ptr_spaceship, int* ptr_asteroid)
{
	if (object_getTypeId(object[k]) == OBJ_TYPE_ASTEROID && object_getTypeId(object[i]) == OBJ_TYPE_SPACESHIP) {
		*ptr_asteroid = k;
		*ptr_spaceship = i;
		return true;
	}
	if (object_getTypeId(object[i]) == OBJ_TYPE_ASTEROID && object_getTypeId(object[k]) == OBJ_TYPE_SPACESHIP) {
		*ptr_asteroid = i;
		*ptr_spaceship = k;
		return true;
	}
	return false;
}

bool varifySpaceshipAndSpaceshipCollision(int i, int k)
{
	return object_getTypeId(object[k]) == OBJ_TYPE_SPACESHIP && object_getTypeId(object[i]) == OBJ_TYPE_SPACESHIP;
}

bool varifyAsteroidAndAsteroidCollision(int i, int k)
{
	return object_getTypeId(object[k]) == OBJ_TYPE_ASTEROID && object_getTypeId(object[i]) == OBJ_TYPE_ASTEROID;
}

void wallColBotTop(Object *s, int thatOne)
{
	int x = object_getDeltaX(object[thatOne]);
	int y = object_getDeltaY(object[thatOne]);
	int posX = object_getX(object[thatOne]);
	int posY = object_getY(object[thatOne]);
//	printf("%d %d - %d %d - side: %d\n", x, y, posX, posY);
	object_setDeltaX(object[thatOne], x); //same delta_x but just slower
	object_setDeltaY(object[thatOne], -y);
	//	printf("Spaceship is trying to leave this universe, stop it!\n");
}

void wallColLeftRight(Object *s, int thatOne)
{
	int x = object_getDeltaX(object[thatOne]);
	int y = object_getDeltaY(object[thatOne]);
	int posX = object_getX(object[thatOne]);
	int posY = object_getY(object[thatOne]);
	//	printf("%d %d - %d %d - side: %d\n", x, y, posX, posY);
	object_setDeltaX(object[thatOne], -x); //same delta_x but just slower
	object_setDeltaY(object[thatOne], y);
	//	printf("Spaceship is trying to leave this universe, stop it!\n");
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

	removeIndex = 0; // Resets the removeIndex each cycle

	// Loop through all objects
	for (int i = 0; i < getObjectIndexMax(); i++) {
		
		if (object[i] != NULL) {

			// Prevents the spaceship from leaving the game universe
			if (object_getTypeId(object[i]) == OBJ_TYPE_SPACESHIP) {
				int side;
				if (!isInsideWorld(object[i], &side)) {
					int whichOne = i; //which spaceship to check for
					if (side == 1) //collided top or bottom on the window
					{
						wallColBotTop(object[i], whichOne);
					}
					else {
						wallColLeftRight(object[i], whichOne);
					}
				}
			}
			// Adds different types of objects to be removed when they leave the universe
			else if (hasLeftWorld(object[i])) {
				printf("Object has left the world...\n");
				list_objectsToRemove[removeIndex++] = i;
			}

			foundIndex = 0;	// Resets the foundIndex

			if (getCollisionObjects(i) > 0) {

				int k, p_spaceship, p_asteroid, p_projectile;

				for (int j = 0; j < foundIndex; j++) {
					k = list_objectsFound[j];

					if (varifySpaceshipAndProjectileCollision(i, k, &p_projectile, &p_spaceship)) {

						// Prevents hit on source spaceship
						if (!projectile_objectIsSource(object[p_projectile], object[p_spaceship])) {
							list_objectsToRemove[removeIndex++] = p_projectile;
							destroyProjectile(projectile[p_projectile]);
						}
					}

					// Projectile hits asteroid

					else if (varifyAsteroidAndProjectileCollision(i, k, &p_projectile, &p_asteroid)) {
					
						double life = object_getLife(object[p_asteroid]) - projectile_getDamage(projectile[p_projectile]);


						if (life <= 0) {
							int x = object_getX(object[p_asteroid]);
							int y = object_getY(object[p_asteroid]);
							printf("Asteroid destruction detected.\n");
							// Create effect

							tempObj = createObject(-1, x, y, sprite_getFrameWidth(sprite[2]) / 3, sprite_getFrameHeight(sprite[2]) / 3, 0, 0, sprite[2], animation[2]);
							createEffect(tempObj, true);
							// Remove asteroid object
							list_objectsToRemove[removeIndex++] = p_asteroid;
						}
						else {
							object_setLife(object[p_asteroid], life);
							printf("asteroid %d has %f life remaing\n", p_asteroid, life);
						}
						list_objectsToRemove[removeIndex++] = p_projectile;	
						destroyProjectile(projectile[p_projectile]);
					}

					// Collision between spaceship and asteroid

					else if (varifySpaceshipAndAsteroidCollision(i, k, &p_spaceship, &p_asteroid)) {
						object_calculateCollisionSpeed(object[i], object[k]);
						printf("Spaceship (%d) collided with asteroid (%d)\n", p_spaceship, p_asteroid);
					}
					else if (varifySpaceshipAndSpaceshipCollision(i, k)) {
						object_calculateCollisionSpeed(object[i], object[k]);
						printf("Two spaceships collided.\n", i, k);
					}
					else if (varifyAsteroidAndAsteroidCollision(i, k)) {
						object_calculateCollisionSpeed(object[i], object[k]);
						printf("Two asteroids collided.\n", i, k);
					}
				}
			}
		}
	}
	for (int i = 0; i < removeIndex; i++) {
		destroyObject(object[list_objectsToRemove[i]]);
	}
	removeFinishedEffects();
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

	// Render all objects in the game
	for (int i = 0; i < getObjectIndexMax(); i++) {
		if (object[i] != NULL) {
			object_tick(object[i]);
			object_render(renderer, object[i], true);
		}
	}


	SDL_RenderPresent(renderer);
}