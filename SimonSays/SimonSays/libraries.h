//De bibliotek som används
#pragma once

#include <stdio.h>
#include <string.h>
#include <tchar.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_net.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL_ttf.h>
#include <math.h>

SDL_Color createColor(int r, int g, int b, int a);

double distanceBetweenPoints(SDL_Point p1, SDL_Point p2);

double distanceBetweenPointsCoordinates(int x1, int x2, int y1, int y2);