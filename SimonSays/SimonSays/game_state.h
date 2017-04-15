#pragma once

#include "libaries.h"
#include "graphics_lib.h"
#include "events.h"

void onGameRunning();
void initGameState();
void clearPointers();
void clearImages();
//void initImages();
void checkButtonClicked();
void buttonSound();
void checkButtonPressedDown();
void checkButtonClicked();
void spaceShipSetup();
void setrects(SDL_Rect* clip);
void animateSpaceship();
void movementSpaceship();
float angleShip(SDL_Rect spaceshippos, SDL_Point mousepos);
void initSky();