#pragma once

// Sprite limitations
#define MAX_FRAME_COL	10
#define MAX_FRAME_ROW	10
#define MAX_FRAME_TOT	100

// Object Types 
#define OBJ_TYPE_GREENWIND			1
#define OBJ_TYPE_SPACESHIP			2
#define OBJ_TYPE_EXPLOSION			3
#define OBJ_TYPE_BLACKHOLE			4
#define OBJ_TYPE_ASTEROID			5
#define OBJ_TYPE_ITEM_HEALTH		6
#define OBJ_TYPE_ITEM_INVUL			7
#define OBJ_TYPE_ITEM_SPEED			8
#define OBJ_TYPE_PROJECTILE			9

#define MAX_NUM_OBJ					1000

#define DEFAULT_MAX_SPEED			20.0
#define DEFAULT_DRAG				1.0
#define DEFAULT_ACC					2.0

// World Side
#define WORLD_LEFT					0
#define WORLD_RIGHT					1
#define WORLD_TOP					2
#define WORLD_BOT					3

// Life

#define LIFE_ASTEROID				3

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
	SDL_Rect clip[MAX_FRAME_COL];		// Frame clip
	int frames_on_row[MAX_FRAME_ROW];	// Declared frames on row
	int frame_w;						// Frame width
	int frame_h;						// Frame height
	int col;							// Columns on spritesheet
	int row;							// Rows on spritesheet
};

struct Object {
	int center_y;
	int center_x;
	int prev_x;
	int prev_y;
	int w;
	int h;

	int collision_w;
	int collision_h;

	int id_type;
	int id_index;
	int id_custom;

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

	bool show;

	struct Animation animation;
	struct Sprite* sprite;
};