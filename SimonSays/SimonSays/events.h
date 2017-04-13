/*	Author(s):	Tiago Redaelli
*	Contact:	tiago.redaelli@gmail.com
*	Version:	0.01
*/

#include "libaries.h"

#define STATE_RELEASED					99		// Flag for Released Key/Button
#define STATE_PRESSED					98		// Flag for Pressed Key/Button

bool isTextEventEnabled();
bool textEvent();
char* getTextInput();
void disableTextInput();
void enableTextInput();

int getTimeStamp(int flag, SDL_Scancode sc);

bool mouseEventHeld(SDL_Scancode sc);
bool mouseEventReleased(SDL_Scancode sc);
bool mouseEventPressed(SDL_Scancode sc);

bool keyEventHeld(SDL_Scancode sc);
bool keyEventReleased(SDL_Scancode sc);
bool keyEventPressed(SDL_Scancode sc);

bool quitEventTriggered();

void refreshEventHandler();
void initEventHandler();			