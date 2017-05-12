#pragma once
#include "libraries.h"
#include "definition.h"

bool validateIPv4Entry(char* str);
bool validatePort(char* str, Uint16* port);
void printIpInfo(IPaddress* ip);