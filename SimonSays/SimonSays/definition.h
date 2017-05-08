#pragma once

#define UNDEFINED					9999
#define OBJ_INDEX_HEAD				8888

// Players
#define MAX_PLAYERS					4
#define PL_COLOR_RED				0
#define PL_COLOR_BLUE				1
#define PL_COLOR_GREEN				2
#define PL_COLOR_ORANGE				3

// Extra color
#define COLOR_GRAY					4

// Sprite limitations
#define MAX_FRAME_COL				10
#define MAX_FRAME_ROW				10
#define MAX_FRAME_TOT				100

// Object Types 
#define OBJ_TYPE_SPACESHIP			1
#define OBJ_TYPE_EFFECT				2
#define OBJ_TYPE_ASTEROID			3
#define OBJ_TYPE_POWERUP			4
#define OBJ_TYPE_PROJECTILE			5

#define MAX_NUM_OBJ					1000

// World Side
#define WORLD_LEFT					0
#define WORLD_RIGHT					1
#define WORLD_TOP					2
#define WORLD_BOT					3

// Collision Types
#define COLLISION_TYPE_BOX			1
#define COLLISION_TYPE_CIRCLE		2

// Life
#define LIFE_POWERUP				1		// Powerup hitpoints
#define LIFE_ASTEROID				3		// Asteroid hitpoints
#define LIFE_SPACESHIP				10		// Spaceship hitpoints

// Power Up
#define POWER_SPEED					0
#define POWER_ATK_2					1
#define POWER_ATK_3					2
#define POWER_HP					3
#define POWER_INVUL					4		// Not implemented
#define POWER_OVERPOWER				5		// Not implemented

#define NUM_OF_POWERS				4		// The number of currently existing power up types

// Powerup Stats
#define POWER_LIFE_ADDED			5		// Life added on pickup

// Duration (ms)
#define TIME_DEATH					20000	// Death timer
#define TIME_SHOOT					300		// Shoot cooldown
#define TIME_SPEED					6000	// Speed boost duration
#define TIME_ATK					6000	// Duration of unique projectile bonus
#define TIME_ACC					100		// The amount of time that a acceleration effect lasts

// Speed
#define SPEED_ACC_DEFAULT			0.7		// default spaceship acceleration added per tick
#define SPEED_ACC_POWER				1.4		// acceleration added per tick when affected by speed boost
#define SPEED_MAX_DEFAULT			9.0		// default maximum spaceship speed
#define SPEED_MAX_POWER				15.0	// powerup maximum spaceship seed
#define DRAG_SPACESHIP				0.98	// drag per tick (speed*drag = new speed)

#define DEFAULT_MAX_SPEED			20.0	// Objects default max speed
#define DEFAULT_DRAG				1.0		// Objects default drag
#define DEFAULT_ACC					2.0		// Objects default acceleration

// Attack types
#define ATK_TYPE_1					1		// Normal attack
#define ATK_TYPE_2					2		// Shotgun attack
#define ATK_TYPE_3					3		// All direction attack

// Chat
#define MSG_DURATION				20		// Chat message duration seconds

// Window
SDL_Renderer*	renderer;					// Game Renderer
SDL_Window*		window;						// Game Window

// Time

int curTime;	

// Structs

struct Animation {
	int cyclesPerFrame;						// Number of cycles per frame
	int numOfFrames;						// Total number of frames			
	int frameCol[MAX_FRAME_TOT];
	int frameRow[MAX_FRAME_TOT];
	int tick;
	int index;
	int size;
	int col;
	int row;
	bool complete;
};

struct Sprite {
	SDL_Texture* texture;				// Texture
	SDL_Rect clip[MAX_FRAME_TOT];		// Frame clip
	int frames_on_row[MAX_FRAME_ROW];	// Declared frames on row
	int frame_w;						// Frame width
	int frame_h;						// Frame height
	int col;							// Columns on spritesheet
	int row;							// Rows on spritesheet
};

struct Collision {
	int w;
	int h;
	int r; 
	int type;
	bool enabled;
};

struct Object {
	int center_y; //skickas
	int center_x; //skickas
	int prev_x;
	int prev_y;
	int w;
	int h;
	
	int* ptr_center_x;
	int* ptr_center_y;

	int id_type;
	int id_index;
	int source_id;		// used by projectiles
	int power_id;		// used to distinguish different powerups

	double delta_x;
	double delta_y;
	double speed_x;
	double speed_y;
	double speed_max;
	double drag;
	double acc;

	double facing;
	double IMG_facingOffset;
	int hp;
	int dmg_on_impact;			
	bool show;					// show/hide the object and the collision from the world

	struct Animation animation;
	struct Sprite* sprite;
	struct Collision collision;

	// node
	int next;
};

struct Player {
	char* name;
	int color;
	SDL_Color sdl_color;
	bool alive;
	bool mobile;
	bool connected;			
	struct Object* spaceship;	
	int death_timestamp;
	int attack_timestamp;
	int rune_speed_timestamp;
	int rune_atk_timestamp;
	int acceleration_timestamp;
	bool speed_active;
	int current_attack_type;
	int shipIndex;

	int killstreak_tot;
	int killstreak_round;		
	int kills;
	int deaths;
	int won_rounds;
};

// DEBUG Variables
bool debug_show_collision_box;

struct Player player[MAX_PLAYERS];