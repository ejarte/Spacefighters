#pragma once
#include "definitions.h"

int TCP();
int player_id;

IPaddress ip;
TCPsocket server;
TCPsocket client;
TCPsocket players[MAXPLAYERS];