#pragma once
#include <stdbool.h>

//=================================
// SERVER RELATED

#define MSG_SERVER_NOT_FULL		"#1#"
#define MSG_SERVER_FULL			"#2#"
#define MSG_CLIENT_NUM			"#3#"
#define MSG_CHAT_MSG			"#4#"
#define MSG_PLAYER_CONNECTED	"#5#"
#define MSG_PLAYER_DISCONNECTED	"#6#"
#define MSG_SHUTDOWN_SERVER		"#7#"
#define MSG_CHANGE_NAME			"#8#"
#define MSG_NEUTRAL_OBJ			"#9#"
#define MSG_PLAYER_ACTIONS		"#10#"
#define SERVER_OBJECTS			"#11#"
#define MSG_POSITION			"#12#"

// VET EJ VAD AV DETTA SOM SKA TAS BORT 

#define INITPORT 1234
#define SPECPORT 5000
#define BROADCASTPORT 6000
#define CONNECTPORT 7000
#define MAXPLAYERS 3

bool messageRec;
char message[10000];
bool broadCast;
int player_id;

int listen(int connectedIp);
int send(int connectedIp);
void freeClient(int clientId);
int checkConnection(int connectedIp);

bool isConnected[3];

int threadId;

//=================================
// SERVER EXPLICIT

#define SERVER_PORT	1234
#define BUFFER_SIZE 1024
#define MAX_SOCKETS	5
#define MAX_CLIENTS 4

struct Server_t {
	IPaddress ip;
	TCPsocket tcp_socket;
	bool running;
	char tcp_buffer[BUFFER_SIZE];
	int tcp_recv_byteCount;
	int tcp_len;
};

struct Client_t {
	TCPsocket tcp_socket;
	bool tcp_socket_is_free;
};

struct Server_t s;
struct Client_t c[MAX_CLIENTS];

//=================================

#pragma once
#include <stdbool.h>

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

// Neutral Objects
#define POWER_SPEED					0
#define POWER_ATK_2					1
#define POWER_ATK_3					2
#define POWER_HP					3
#define ASTEROID					4

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



int curTime;
int tempMSG[BUFFER_SIZE];
bool startTimer;

