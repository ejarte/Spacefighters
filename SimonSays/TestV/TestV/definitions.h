#pragma once
#include <stdbool.h>


#define INITPORT 1234
#define SPECPORT 5000
#define BROADCASTPORT 6000
#define MAXPLAYERS 3

bool messageRec;
char message[10000];
bool broadCast;
int player_id;

int listen(int connectedIp);
int send(int connectedIp);