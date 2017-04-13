/*	Author(s):	Tiago Redaelli
 *	Contact:	tiago.redaelli@gmail.com
 *	Version:	0.01	
 */
#include "libaries.h"
#include "events.h"

#define EV_MAX_SCANCODES				260	// Array Size
#define TRIGGER_EVENT_NONE				0		
#define TRIGGER_EVENT_KEY_PRESSED		1
#define TRIGGER_EVENT_KEY_RELEASED		2
#define TRIGGER_EVENT_MOUSE_PRESSED		3
#define TRIGGER_EVENT_MOUSE_RELEASED	4

// Event data encapsulation
struct EventData {	
	int event_flag[EV_MAX_SCANCODES];
	int cur_event_state[EV_MAX_SCANCODES];
	int prev_event_state[EV_MAX_SCANCODES];
	unsigned int time_stamp_pressed[EV_MAX_SCANCODES];				
	unsigned int time_stamp_released[EV_MAX_SCANCODES];
};

struct TextEventData {
	bool event_flag;
	char *str_input;
	bool enabled;
};

struct	EventData event_data;
struct TextEventData txt_event_data;

bool quit_event;		// Flag for quit event

bool isTextEventEnabled()
{
	return txt_event_data.enabled;
}

bool textEvent()
{
	return txt_event_data.event_flag;
}

char* getTextInput()
{
	return txt_event_data.str_input;
}

void disableTextInput() 
{
	txt_event_data.enabled = false;
	SDL_StopTextInput();
}

void enableTextInput()
{
	txt_event_data.enabled = true;
	SDL_StartTextInput();
}

int getTimeStamp(int flag, SDL_Scancode sc)
{
	if (flag == STATE_RELEASED)
		return event_data.time_stamp_released[sc];
	else if (flag == STATE_PRESSED)
		return event_data.time_stamp_pressed[sc];
	else
		printf("ERROR: Invalid time stamp flag in EventHandler.");
}

bool mouseEventHeld(SDL_Scancode sc) 
{
	return event_data.event_flag[sc] == TRIGGER_EVENT_NONE && event_data.cur_event_state[sc] == STATE_PRESSED;
}

bool mouseEventReleased(SDL_Scancode sc) 
{
	return event_data.event_flag[sc] == TRIGGER_EVENT_MOUSE_RELEASED;
}

bool mouseEventPressed(SDL_Scancode sc) 
{
	return event_data.event_flag[sc] == TRIGGER_EVENT_MOUSE_PRESSED;
}


bool keyEventHeld(SDL_Scancode sc) 
{
	return event_data.event_flag[sc] == TRIGGER_EVENT_NONE && event_data.cur_event_state[sc] == STATE_PRESSED;
}

bool keyEventReleased(SDL_Scancode sc)
{
	return event_data.event_flag[sc] == TRIGGER_EVENT_KEY_RELEASED;
}

bool keyEventPressed(SDL_Scancode sc) 
{
	return event_data.event_flag[sc] == TRIGGER_EVENT_KEY_PRESSED;
}

bool quitEventTriggered() {
	return quit_event;
}

/* Polls for the latest events and stores the information temporarily to be accessed by the librarys API. */

void refreshEventHandler() {
	SDL_Event event;
	int index;

	/* Clear previous events */

	// reset event flag for the event data struct
	for (int i = 0; i < EV_MAX_SCANCODES; i++)
	{
		event_data.event_flag[i] = TRIGGER_EVENT_NONE;
	}
	// reset text_input
	txt_event_data.event_flag = false;
	free(txt_event_data.str_input);
	txt_event_data.str_input = malloc(30);
	txt_event_data.str_input[0] = '\0';

	/* Poll for new events */

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_MOUSEMOTION: break;	
				// Not yet implemented 

			case SDL_MOUSEWHEEL: break;		
				// Not yet implemented

			case SDL_KEYDOWN: {
				if (!event.key.repeat) {
					index = event.key.keysym.scancode;
					event_data.cur_event_state[index] = STATE_PRESSED;
					if (event_data.prev_event_state[index] == STATE_RELEASED) {
						event_data.event_flag[index] = TRIGGER_EVENT_KEY_PRESSED;
						event_data.time_stamp_pressed[index] = SDL_GetTicks();
					}
					event_data.prev_event_state[index] = event_data.cur_event_state[index];
				}
			} break;

			case SDL_KEYUP: {
				if (!event.key.repeat) {
					index = event.key.keysym.scancode;
					event_data.cur_event_state[index] = STATE_RELEASED;
					if (event_data.prev_event_state[index] == STATE_PRESSED) {
						event_data.event_flag[index] = TRIGGER_EVENT_KEY_RELEASED;
						event_data.time_stamp_released[index] = SDL_GetTicks();
					}
					event_data.prev_event_state[index] = event_data.cur_event_state[index];
				}
			} break;

			case SDL_MOUSEBUTTONDOWN: {
				index = event.button.button;
				event_data.cur_event_state[index] = STATE_PRESSED;
				if (event_data.prev_event_state[index] == STATE_RELEASED) {
					event_data.event_flag[index] = TRIGGER_EVENT_MOUSE_PRESSED;
					event_data.time_stamp_pressed[index] = SDL_GetTicks();
				}
				event_data.prev_event_state[index] = event_data.cur_event_state[index];
			} break;
			
			case SDL_MOUSEBUTTONUP: {
				index = event.button.button;
				event_data.cur_event_state[index] = STATE_RELEASED;
				if (event_data.prev_event_state[index] == STATE_PRESSED) {
					event_data.event_flag[index] = TRIGGER_EVENT_MOUSE_RELEASED;
					event_data.time_stamp_released[index] = SDL_GetTicks();
				}
				event_data.prev_event_state[index] = event_data.cur_event_state[index];
			} break;

			case SDL_TEXTINPUT: {
				strcat(txt_event_data.str_input, event.text.text);
				txt_event_data.event_flag = true;
			} break;

			case SDL_QUIT: {
				quit_event = true;
			} break;

			default: break;
		}
	}
}

/* Initializes the Event Handler, run once at the start of the program. */

void initEventHandler() 
{
	for (int i = 0; i < EV_MAX_SCANCODES; i++)
	{
		event_data.event_flag[i] = TRIGGER_EVENT_NONE;
		event_data.prev_event_state[i] = STATE_RELEASED;
		event_data.cur_event_state[i] = STATE_RELEASED;
	}
	txt_event_data.event_flag = false;
	txt_event_data.str_input = malloc(30);
	txt_event_data.str_input[0] = '\0';
	disableTextInput();
	quit_event = false;		

}
