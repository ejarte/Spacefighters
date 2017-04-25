//De bibliotek som används
#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_net.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>

SDL_Color createColor(int r, int g, int b, int a);

double distanceBetweenPointsCoordinates(int x1, int x2, int y1, int y2);

double distanceBetweenPoints(SDL_Point p1, SDL_Point p2);

double radiansToDegrees(double radians);

double degreesToRadians(double degree);

double angleBetweenPointsRad(SDL_Point p1, SDL_Point p2);