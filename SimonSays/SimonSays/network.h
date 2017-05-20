#pragma once
#include "libraries.h"
#include "definition.h"
#include "libraries.h"

bool validateIPv4Entry(char* str, Uint32* ipaddr);
bool validatePortEntry(char* str, Uint16* port);
void printIpInfo(IPaddress* ip);
bool connectToServer(char* str_host_ip, char* str_port);
void TCP_listen();
void TCP_sendChatMsg(char* msg);
void TCP_sendNameChange(char* name);
void TCP_sendPlayerActions(int pId);
void TCP_sendStart();
bool startTheGame;

struct RecvPlayerActions {
	int w;
	int a;
	int s;
	int d;
	int mx;
	int my;
	int shoot;
};

struct RecvPlayerActions playerActions[MAX_PLAYERS];
