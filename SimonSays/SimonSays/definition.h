#pragma once

#define UNDEFINED					9999
#define OBJ_INDEX_HEAD				8888

// Players
#define MAX_PLAYERS					4
#define PL_COLOR_RED				0
#define PL_COLOR_BLUE				1
#define PL_COLOR_ORANGE				2
#define PL_COLOR_YELLOW				3

// Sprite limitations
#define MAX_FRAME_COL				10
#define MAX_FRAME_ROW				10
#define MAX_FRAME_TOT				100

// Object Types 
#define OBJ_TYPE_SPACESHIP			1
#define OBJ_TYPE_EXPLOSION			2
#define OBJ_TYPE_ASTEROID			3
#define OBJ_TYPE_POWERUP			4
#define OBJ_TYPE_PROJECTILE			5

#define MAX_NUM_OBJ					1000

#define DEFAULT_MAX_SPEED			20.0
#define DEFAULT_DRAG				1.0
#define DEFAULT_ACC					2.0

// World Side
#define WORLD_LEFT					0
#define WORLD_RIGHT					1
#define WORLD_TOP					2
#define WORLD_BOT					3

// Collision Types
#define COLLISION_TYPE_BOX			1
#define COLLISION_TYPE_CIRCLE		2

// Life
#define LIFE_POWERUP				1
#define LIFE_ASTEROID				3
#define LIFE_SPACESHIP				20

// Power Up
#define POWER_SPEED					0
#define POWER_ATK_2					1
#define POWER_ATK_3					2
#define POWER_HP					3

#define POWER_INVUL					4	// Not implemented
#define POWER_OVERPOWER				5	// Not implemented
#define NUM_OF_POWERS				3

// Time (ms)
#define TIME_DEATH					20000	
#define TIME_SHOOT					300		

// Window
SDL_Renderer*	renderer;
SDL_Window*		window;

// Structs

struct Animation {
	int cyclesPerFrame;					// Number of cycles per frame
	int numOfFrames;					// Total number of frames			
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
	int center_y;
	int center_x;
	int prev_x;
	int prev_y;
	int w;
	int h;

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
	bool alive;
	bool mobile;
	bool connected;
	bool accelerating;				
	struct Object* spaceship;	
	int death_timestamp;
	int attack_timestamp;
	int rune_speed_timestamp;
	int rune_atk_2_timestamp;
	int rune_atk_3_timestamp;
	bool speed_active;
	bool atk_2_active;
	bool atk_3_active;
	int shipIndex;
};

// DEBUG Variables
bool debug_show_collision_box;
