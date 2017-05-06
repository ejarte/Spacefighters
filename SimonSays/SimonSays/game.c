#include "game.h"
#include "TCP.h"
#include "UDP.h"
#include "interface_lib.h"
#include "text_messages.h"

// Background
SDL_Rect background_rect;
SDL_Rect back_rect;
SDL_Rect stars_rect;
SDL_Texture* backgroundImage;
SDL_Texture *starsImage;

int free_obj_index[500];
int free_obj_size;

int client_player_num;

// Temp
SDL_Texture* texture_chat_box;
TTF_Font* font_roboto_black;

struct Plane plane_chat_box;
struct Label label_chat_msg;
struct Label playerNameColored[MAX_PLAYERS];

struct TextBox tb;

SDL_Texture* t;

// 
char* player_text_input;

void game_init()
{
	// Background
	backgroundImage = IMG_LoadTexture(renderer, "images/skyBackground.png");
	background_rect.x = background_rect.y = 0;
	starsImage = IMG_LoadTexture(renderer, "images/skyForeground.png");
	stars_rect.x = stars_rect.y = 0;
	stars_rect.w = stars_rect.h = 800;

	world_init();
	object_init();
	init_text_messages();

	// Hide cursor
	//SDL_ShowCursor(SDL_DISABLE);

	// Text input
	player_text_input = malloc(sizeof(80));
	player_text_input[0] = '\0';

	// On Server
	for (int i = 0; i < MAX_PLAYERS; i++) {
		player[i].name = malloc(sizeof(30));
		player[i].name[0] = '\0';
		player[i].color = i;
		player[i].connected = true;		// Set true on connection
		player[i].shipIndex = UNDEFINED;
		player[i].death_timestamp = 0;
		player[i].attack_timestamp = 0;
		player[i].rune_atk_timestamp = 0;
		player[i].acceleration_timestamp = 0;
		player[i].current_attack_type = ATK_TYPE_1;

		player[i].deaths = 0;
		player[i].kills = 0;
		player[i].killstreak_tot = 0;
		player[i].killstreak_round = 0;
		player[i].won_rounds = 0;
	}

	// Setup Player color
	player[0].sdl_color = createColor(0xFF, 0, 0, 0);
	player[1].sdl_color = createColor(0, 0, 0xFF, 0);
	player[2].sdl_color = createColor(0, 0xFF, 0, 0);
	player[3].sdl_color = createColor(0xFF, 0x78, 0x1C, 0);

	// The recieved player id of this client
	client_player_num = 0;

	// Player 1
	player[0].name = "Player 1";
	player[0].connected = true;
	world_spawnSpaceship(&player[0], 200, 200, 0);

	// Player 2
	player[1].name = "Player 2";
	player[1].connected = true;
	world_spawnSpaceship(&player[1], 400, 200, 0);

	// Player 3
	player[2].name = "Player 3";
	player[2].connected = true;
	world_spawnSpaceship(&player[2], 400, 400, 0);

	// Player 2
	player[3].name = "Player 4";
	player[3].connected = true;
	world_spawnSpaceship(&player[3], 299, 400, 0);

	texture_chat_box = IMG_LoadTexture(renderer, "images/greensquare.bmp");


	interface_setup_plane(&plane_chat_box, texture_chat_box, 200, 200, 100, 100, true);

	font_roboto_black = TTF_OpenFont("fonts/roboto/Roboto-Black.ttf", 12);

	// Exempel p� connect/disconnect meddelande
	addPlayerEmoteMessageToDisplay(renderer, client_player_num, "connected.", MSG_DURATION);
	addPlayerEmoteMessageToDisplay(renderer, client_player_num, "disconnected.", MSG_DURATION);

	//interface_setup_label(&label_chat_msg, renderer, "|c00FF00AAHello!|r", font_roboto_black, createColor(255, 0, 0, 0), 200, 200, true);

	interface_setup_label(&playerNameColored[0], renderer, player[0].name, font_roboto_black, createColor(0xFF, 0, 0, 0), 100, 100, true);
	interface_setup_label(&playerNameColored[1], renderer, player[1].name, font_roboto_black, createColor(0, 0, 0xFF, 0), 800, 100, true);
	interface_setup_label(&playerNameColored[2], renderer, player[2].name, font_roboto_black, createColor(0, 0xFF, 0, 0), 100, 800, true);
	interface_setup_label(&playerNameColored[3], renderer, player[3].name, font_roboto_black, createColor(0xFF, 0x78, 0x1C, 0), 800, 600, true);

	//	printf("%d %d\n", *object[0].ptr_center_x, 0);

	interface_attach_label(&playerNameColored[0], player[0].spaceship->ptr_center_x, player[0].spaceship->ptr_center_y, -50, -50);
	interface_attach_label(&playerNameColored[1], player[1].spaceship->ptr_center_x, player[1].spaceship->ptr_center_y, -50, -50);
	interface_attach_label(&playerNameColored[2], player[2].spaceship->ptr_center_x, player[2].spaceship->ptr_center_y, -50, -50);
	interface_attach_label(&playerNameColored[3], player[3].spaceship->ptr_center_x, player[3].spaceship->ptr_center_y, -50, -50);

	//printf("lol? %d %d\n", *object[4].ptr_center_x, *object[4].ptr_center_y);

	t = IMG_LoadTexture(renderer, "images/greensquare.bmp");

	interface_setup_textbox(&tb, t, renderer, font_roboto_black, createColor(255, 255, 255, 0), createRect(200, 200, 200, 25), 10, true);
	appendInTextBox(&tb, "hello!", renderer);
	appendInTextBox(&tb, "there!", renderer);
	// game menu
	initInterface();
	all_button_positions_Interface();
	// Debug variables
	debug_show_collision_box = false;
}

void game_execute()
{
	game_events();
	game_update();
	game_render();
}

void game_events()
{
	int time = SDL_GetTicks();

	if (quitEventTriggered()) {
		setNextState(STATE_EXIT);
		return;
	}

	if (keyEventPressed(SDL_SCANCODE_RETURN)) {

		if (isTextEventEnabled()) {
			disableTextInput();
			if (player_text_input[0] != '\0') {
				printf("msg: %s\n", player_text_input);
				addPlayerMessageToDisplay(renderer, client_player_num, player_text_input, MSG_DURATION);
			}
		}
		else {
			enableTextInput();
			player_text_input[0] = '\0';
			printf("enter text msg...\n");
		}
	}
	if (textEvent()) {
		strcat(player_text_input, getTextInput());
		printf("%s\n", player_text_input);
	}




	runInterface();




	if (keyEventPressed(SDL_SCANCODE_P)) {

		SDL_Thread *TCPThread = NULL;
		const char *TCPThreadReturnValue;
		//TCPThread = SDL_CreateThread(TCP, "TestThread", "127.0.0.1");

		if (NULL == TCPThread) {
			printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
		}
		else {
			//SDL_WaitThread(TCPThread, &TCPThreadReturnValue);
			//printf("\nThread returned value: %d", TCPThreadReturnValue);
		}
		/*
		char* text = malloc(sizeof(100));
		text[0] = '\0';
		strcat(text, TCP("127.0.0.1"));
		printf("%s\n", text);
		free(text);
		*/
	}

	if (keyEventPressed(SDL_SCANCODE_O)) {
		SDL_Thread *TCPThread;
		const char *TCPThreadReturnValue;
		TCPThread = SDL_CreateThread(UDP, "TestThreadUDP", "127.0.0.1");

		if (NULL == TCPThread) {
			printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
		}
	}

	if (mouseEventHeld(SDL_BUTTON_LEFT) && player[client_player_num].alive && player[client_player_num].attack_timestamp + TIME_SHOOT < time) {
		spawnNormalProjectile(player[client_player_num].spaceship, player[client_player_num].color);
		player[client_player_num].attack_timestamp = time;
	}
	if (keyEventHeld(SDL_SCANCODE_W) && player[client_player_num].mobile == true) {
		player[client_player_num].acceleration_timestamp = time;
		object_deaccelerateSpeedY(player[client_player_num].spaceship);
	}
	if (keyEventHeld(SDL_SCANCODE_S) && player[client_player_num].mobile) {
		player[client_player_num].acceleration_timestamp = time;
		object_accelerateSpeedY(player[client_player_num].spaceship);
	}
	if (keyEventHeld(SDL_SCANCODE_A) && player[client_player_num].mobile) {
		player[client_player_num].acceleration_timestamp = time;
		object_deaccelerateSpeedX(player[client_player_num].spaceship);
	}
	if (keyEventHeld(SDL_SCANCODE_D) && player[client_player_num].mobile) {
		player[client_player_num].acceleration_timestamp = time;
		object_accelerateSpeedX(player[client_player_num].spaceship);
	}
	if (keyEventPressed(SDL_SCANCODE_C)) {
		client_player_num++;
		if (client_player_num == MAX_PLAYERS) {
			client_player_num = 0;
		}
	}

	object_setFacingToPoint(player[client_player_num].spaceship, getMousePos());


	// Testing 
	if (keyEventPressed(SDL_SCANCODE_Z)) {
		world_spawnEnteringAsteroid();
	}
	if (keyEventPressed(SDL_SCANCODE_X)) {
		spawnPowerUpType(rand() % NUM_OF_POWERS);
	}
}

void handleWallCollision(int i, int side)
{
	if (side == WORLD_TOP) {
		object[i].delta_y = object[i].delta_y *-1;
		object[i].speed_y = object[i].speed_y *-1;
	}
	if (side == WORLD_BOT) {
		object[i].delta_y = object[i].delta_y *-1;
		object[i].speed_y = object[i].speed_y *-1;
	}
	if (side == WORLD_LEFT) {
		object[i].delta_x = object[i].delta_x *-1;
		object[i].speed_x = object[i].speed_x *-1;
	}
	if (side == WORLD_RIGHT) {
		object[i].delta_x = object[i].delta_x *-1;
		object[i].speed_x = object[i].speed_x *-1;
	}
	object_move(&object[i]);
}

bool resolveCollisionSpaceshipPowerup(int i, int j, int* ptr_ship, int* ptr_power)
{
	if (object[i].id_type == OBJ_TYPE_SPACESHIP && object[j].id_type == OBJ_TYPE_POWERUP) {
		*ptr_ship = i;
		*ptr_power = j;
		return true;
	}
	if (object[i].id_type == OBJ_TYPE_POWERUP && object[j].id_type == OBJ_TYPE_SPACESHIP) {
		*ptr_ship = j;
		*ptr_power = i;
		return true;
	}
	return false;
}

bool resolveCollisionProjPowerup(int i, int j, int* ptr_proj, int* ptr_power)
{
	if (object[i].id_type == OBJ_TYPE_PROJECTILE && object[j].id_type == OBJ_TYPE_POWERUP) {
		*ptr_proj = i;
		*ptr_power = j;
		return true;
	}
	if (object[i].id_type == OBJ_TYPE_POWERUP && object[j].id_type == OBJ_TYPE_PROJECTILE) {
		*ptr_proj = j;
		*ptr_power = i;
		return true;
	}
	return false;
}

bool resolveCollisionProjSpaceship(int i, int j, int* ptr_proj, int* ptr_ship)
{
	if (object[i].id_type == OBJ_TYPE_PROJECTILE && object[j].id_type == OBJ_TYPE_SPACESHIP && object[i].source_id != j) {
		*ptr_proj = i;
		*ptr_ship = j;
		return true;
	}
	if (object[i].id_type == OBJ_TYPE_SPACESHIP && object[j].id_type == OBJ_TYPE_PROJECTILE && object[j].source_id != i) {
		*ptr_proj = j;
		*ptr_ship = i;
		return true;
	}
	return false;
}

bool resolveCollisionProjAsteroid(int i, int j, int* ptr_proj, int* ptr_asteroid)
{
	if (object[i].id_type == OBJ_TYPE_PROJECTILE && object[j].id_type == OBJ_TYPE_ASTEROID) {
		*ptr_proj = i;
		*ptr_asteroid = j;
		return true;
	}
	if (object[i].id_type == OBJ_TYPE_ASTEROID && object[j].id_type == OBJ_TYPE_PROJECTILE) {
		*ptr_proj = j;
		*ptr_asteroid = i;
		return true;
	}
	return false;
}

bool resolveCollisionSpaceshipAsteroid(int i, int j, int* ptr_asteroid, int* ptr_ship)
{
	if (object[i].id_type == OBJ_TYPE_SPACESHIP && object[j].id_type == OBJ_TYPE_ASTEROID) {
		*ptr_ship = i;
		*ptr_asteroid = j;
		return true;
	}
	if (object[i].id_type == OBJ_TYPE_ASTEROID && object[j].id_type == OBJ_TYPE_SPACESHIP) {
		*ptr_ship = j;
		*ptr_asteroid = i;
		return true;
	}
	return false;
}


void markForRemoval(int index) {
	bool add = true;
	// Prevents duplications
	for (int i = 0; i < free_obj_size; i++) {
		if (free_obj_index[i] == index) {
			add = false;
		}
	}
	if (add) {
		free_obj_index[free_obj_size++] = index;
	}
}

int getPlayer(int objIndex)
{
	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (player[i].spaceship->id_index == objIndex)
			return i;
	}
	return UNDEFINED;
}

int getPlayerFromSource(int objIndex)
{
	int ship_index = object[objIndex].source_id;
	return getPlayer(ship_index);
}

void handleShipDeath(int ship)
{
	int time = SDL_GetTicks();
	int p = getPlayer(ship);
	object[ship].show = false;
	printf("Player %d's ship was destroyed (%d) @time: %d\n", p, ship, time); 
	player[p].mobile = false;
	player[p].alive = false;
	player[p].death_timestamp = time;
}

void handleSpeedBoost(int ship) {
	int p = getPlayer(ship);
	int time = SDL_GetTicks();
	object[ship].acc = SPEED_ACC_POWER;
	object[ship].speed_max = SPEED_MAX_POWER;
	player[p].speed_active = true;
	player[p].rune_speed_timestamp = time;
	printf("player %d got a speed boost! @time: %d\n", getPlayer(ship), time);
}

void disableSpeedBoost(int p) 
{
	player[p].spaceship->acc = SPEED_ACC_DEFAULT;
	player[p].spaceship->speed_max = SPEED_MAX_DEFAULT;
	player[p].speed_active = false;
	printf("player %d speed boost expired! @time: %d\n", p, SDL_GetTicks());
}

void handleLifePickup(int ship)
{
	int p = getPlayer(ship);
	object[ship].hp += POWER_LIFE_ADDED;
	if (object[ship].hp > LIFE_SPACESHIP)
		object[ship].hp = LIFE_SPACESHIP;
	printf("player %d recieved %d life back (%d) @time: %d\n", p, POWER_LIFE_ADDED, object[ship].hp, SDL_GetTicks());
}

void handleAttack_2_Pickup(int ship) 
{
	int time = SDL_GetTicks();
	int p = getPlayer(ship);
	player[p].current_attack_type = ATK_TYPE_2;
	player[p].rune_atk_timestamp = time;
	printf("player %d aquired attack type (%d) @time: %d\n", p, 2, time);
}

void handleAttack_3_Pickup(int ship)
{
	int time = SDL_GetTicks();
	int p = getPlayer(ship);
	player[p].current_attack_type = ATK_TYPE_3;
	player[p].rune_atk_timestamp = time;
	printf("player %d aquired attack type (%d) @time: %d\n", p, 3, time);
}

void handleAttackReset(int p)
{
	player[p].current_attack_type = ATK_TYPE_1;
	printf("player %d now has a normal attack again (%d) @time: %d\n", p, 1, SDL_GetTicks());
}

void handleShipResurrection(int p)
{
	int time = SDL_GetTicks();
	int i = player[p].shipIndex;
	object[i].show = true;
	object[i].hp = LIFE_SPACESHIP;
	player[p].mobile = true;
	player[p].alive = true;
	printf("Player %d's ship was resurrected (%d) @time: %d\n", p, i, time);

	// Kvar att g�ra: ??? Kolla ifall det �r tomt d�r skeppet ska spawna annars spawna n�gn annan stanns.
}

void handlePlayerKillsAndDeaths(int killer, int victim) 
{
	player[victim].killstreak_tot = 0;
	player[victim].killstreak_round = 0;
	player[victim].deaths++;
	player[killer].kills++;
	player[killer].killstreak_tot++;
	player[killer].killstreak_round++;
	if (killer != victim)
		printf("%s killed %s\n", player[killer].name, player[victim].name);
	if (killer == victim) {
		printf("%s took his own life.\n", player[victim]);
	}
}


void game_update()
{
	int ptr_side, i, i_projectile, i_ship, i_asteroid, i_item, i_power, time, x, y, dx, dy, killer, victim;
	double angle;

	free_obj_size = 0; // clears the array of removed objects
	
	// Update player activities
	time = SDL_GetTicks();
	for (int i = 0; i < MAX_PLAYERS; i++) {
		// Resurrection triggered
		if (player[i].connected && player[i].alive == false && player[i].death_timestamp + TIME_DEATH < time) {
			handleShipResurrection(i);
		}
		// Spped boost expired
		if (player[i].speed_active && player[i].rune_speed_timestamp + TIME_SPEED < time) {
			disableSpeedBoost(i);
		}
		if (player[i].current_attack_type != ATK_TYPE_1 && player[i].rune_atk_timestamp + TIME_ATK < time) {
			handleAttackReset(i);
		}
		if (player[i].acceleration_timestamp + TIME_ACC > time) {
			dx = player[i].spaceship->speed_x;
			dy = player[i].spaceship->speed_y;
			x = player[i].spaceship->center_x;
			y = player[i].spaceship->center_y;
			world_createParticleFlightPath(player[i].color, x, y, dx, dy);
		}
	}

	i = objHead;
	while (i != UNDEFINED) {
		if (object[i].id_type == OBJ_TYPE_SPACESHIP) {
			if (!isInsideWorld(&object[i], &ptr_side)) {
				handleWallCollision(i, ptr_side);
			}

			// Debug when the player manages to leave the map
			if (world_spaceshipLost(&object[i])) {
				object[i].center_x = getWindowWidth() / 2;
				object[i].center_y = getWindowHeight() / 2;
			}
		}

		object_tick(&object[i]);
		object_move(&object[i]);

		// Tick particles
		
		particle_tick_all();


		// Collision
		int j = object[i].next;
		while (j != UNDEFINED) {
			if (object_instersection(&object[i], &object[j])) {

				// Bouncing things
				if (object[i].id_type != OBJ_TYPE_PROJECTILE && object[j].id_type != OBJ_TYPE_PROJECTILE && resolveCollisionSpaceshipPowerup(i, j, &i_item, &i_item) == false) {
					object_calculateCollisionSpeed(&object[i], &object[j]);
				}
				// Projectile hits spaceship
				if (resolveCollisionProjSpaceship(i, j, &i_projectile, &i_ship)) {
					// Particle explosion on impact
					dx = object[i_projectile].delta_x;
					dy = object[i_projectile].delta_y;
					angle = radiansToDegrees(pointToAngle(dx, dy));
					world_createParticleExplosionAngled(object[i_ship].center_x, object[i_ship].center_y, angle);	
					// Remove projectile
					markForRemoval(i_projectile);		
					// Damage ship
					object[i_ship].hp -= object[i_projectile].dmg_on_impact;	
					// Death
					if (object[i_ship].hp <= 0) {
						handleShipDeath(i_ship);
						victim = getPlayer(i_ship);
						killer = getPlayerFromSource(i_projectile);
						handlePlayerKillsAndDeaths(killer, victim);
					}
				}
				// Projectile hits asteroid
				else if (resolveCollisionProjAsteroid(i, j, &i_projectile, &i_asteroid)) {
					dx = object[i_projectile].delta_x;
					dy = object[i_projectile].delta_y;
					angle = radiansToDegrees(pointToAngle(dx, dy));
					markForRemoval(i_projectile);
					object[i_asteroid].hp -= object[i_projectile].dmg_on_impact;
					world_createParticleExplosionAngled(object[i_asteroid].center_x, object[i_asteroid].center_y, angle);		// Particle explosion on impact
					// On asteroid death
					if (object[i_asteroid].hp <= 0) {
						markForRemoval(i_asteroid);
					}
				}
				// Projectile hits powerup
				else if (resolveCollisionProjPowerup(i, j, &i_projectile, &i_power)) {
					markForRemoval(i);
					markForRemoval(j);
				}
				// Spaceship picksup powerup
				if (resolveCollisionSpaceshipPowerup(i, j, &i_ship, &i_power)) {
					markForRemoval(i_power);
					if (object[i_power].power_id == POWER_SPEED) {
						handleSpeedBoost(i_ship);
					}
					else if (object[i_power].power_id == POWER_HP) {
						handleLifePickup(i_ship);
					}
					else if (object[i_power].power_id == POWER_ATK_2) {
						handleAttack_2_Pickup(i_ship);
					}
					else if (object[i_power].power_id == POWER_ATK_3) {
						handleAttack_2_Pickup(i_ship);
					}
				}

				// Spaceship and asteroid collide
				else if (resolveCollisionSpaceshipAsteroid(i, j, &i_asteroid, &i_ship)) {
					object[i_asteroid].hp -= object[i_ship].dmg_on_impact;
					object[i_ship].hp -= object[i_asteroid].dmg_on_impact;
					if (object[i_asteroid].hp <= 0) {
						markForRemoval(i_asteroid);
					}
					if (object[i_ship].hp <= 0) {
						handleShipDeath(i_ship);
						victim = getPlayer(i_ship);
						handlePlayerKillsAndDeaths(victim, victim);
					}
				}
			}
			j = object[j].next;
		}

		if (hasLeftWorld(&object[i])) {
			markForRemoval(i);
		}
		i = object[i].next;
	}

	// Free removed objects
	for (int i = 0; i < free_obj_size; i++) {
		object_deindex(free_obj_index[i]);		// &thisPlayer on client NULL on server
	}
}

void game_render()
{
	int x = player[client_player_num].spaceship->center_x;
	int y = player[client_player_num].spaceship->center_y;


	SDL_RenderClear(renderer);

	stars_rect.x = x / 10;
	stars_rect.y = y / 10;
	back_rect.x = x / 15;
	back_rect.y = y / 15;
	back_rect.w = background_rect.w;
	back_rect.h = background_rect.h;
	background_rect.w = getWindowWidth();
	background_rect.h = getWindowHeight();

	// Background
	SDL_RenderCopy(renderer, backgroundImage, &back_rect, &background_rect);
	SDL_RenderCopy(renderer, starsImage, &stars_rect, &background_rect);

	// Particles
	particle_render_all(renderer);

	// Objects
	int i = objHead;
	while (i != UNDEFINED) {
		object_render(renderer, &object[i]);
		i = object[i].next;
	}

	if (current_lines > 0)
		renderMessageDisplay(renderer);

	interface_render_textbox(&tb, renderer);

	//interface_render_plane(&plane_chat_box, renderer);
	//interface_render_label(&label_chat_msg, renderer);
	interface_render_label(&playerNameColored[0], renderer);
	interface_render_label(&playerNameColored[1], renderer);
	interface_render_label(&playerNameColored[2], renderer);
	interface_render_label(&playerNameColored[3], renderer);
	rendererInterface();

	SDL_RenderPresent(renderer);
}