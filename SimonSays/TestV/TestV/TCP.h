#pragma once
#include "definitions.h"

int TCP();

IPaddress ip;
TCPsocket server;
TCPsocket client;
TCPsocket players[MAXPLAYERS];