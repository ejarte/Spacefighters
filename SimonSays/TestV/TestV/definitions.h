#pragma once
#include <stdbool.h>


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

	//struct Animation animation;
	struct Sprite* sprite;
	//struct Collision collision;

	// node
	int next;
};