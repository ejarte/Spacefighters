#include "text_messages.h"
#include "events.h"

#define MAX_LINES		30	
#define MSG_MAX_CHARS	150

struct Text_Line {
	struct Label label[10];
	int end_time;
	int size;
};

int current_lines;

struct Text_Line line[MAX_LINES];

int dist_k;

TTF_Font* font_roboto_black;
SDL_Color white;

int h = 20;

char* temp_str;

void init_text_messages()
{
	font_roboto_black = TTF_OpenFont("fonts/roboto/Roboto-Black.ttf", 12);
	white = createColor(0xFF, 0xFF, 0xFF, 0);

	dist_k = 10;

	current_lines = 0;
	temp_str = malloc(150);
	temp_str[0] = '\0';
}

void update_all_text_line_pos()
{
	for (int i = current_lines; i > 0; i--) {
		line[i] = line[i - 1];
		for (int j = 0; j < line[i].size; j++) {
			line[i].label[j].rect.y -= h;
		}
	}
}

void addMessageToDisplay(SDL_Renderer* rend, char* msg, int time_seconds)
{
	if (strlen(msg) > MSG_MAX_CHARS) {
		msg[MSG_MAX_CHARS] = '\0';
	}
	update_all_text_line_pos();

	SDL_Color white = { 255, 255, 255, 0 };
	interface_setup_label(&line[0].label[0], rend, msg, font_roboto_black, white, 50, getWindowHeight() - 100, true);
	line[0].end_time = SDL_GetTicks() + time_seconds * 1000;
	line[0].size = 1;
	current_lines++;
	printf("Not stuck in addMessageToDisplay...\n");
}

void addPlayerEmoteMessageToDisplay(SDL_Renderer* rend, int p_id, char* msg, int time_seconds)
{
	// Quick fix
	char str[1000];
	sprintf(str, "*%s* %s", player[p_id].name, msg);
	addMessageToDisplay(rend, str, time_seconds);
	return;

	// Hidden old code

	if (strlen(msg) > MSG_MAX_CHARS) {
		msg[MSG_MAX_CHARS] = '\0';
	}

	update_all_text_line_pos();

	interface_setup_label(&line[0].label[0], rend, player[p_id].name, font_roboto_black, player[p_id].sdl_color, 50, getWindowHeight() - 100, true);
	interface_setup_label(&line[0].label[1], rend, msg, font_roboto_black, white, 50 + line[0].label[0].rect.w + dist_k, getWindowHeight() - 100, true);
	line[0].end_time = SDL_GetTicks() + time_seconds * 1000;
	line[0].size = 2;
	current_lines++;
}

void addPlayerMessageToDisplay(SDL_Renderer* rend, int p_id, char* msg, int time_seconds)
{
	// Quick fix
	char str[1000];
	sprintf(str, "%s: %s", player[p_id].name, msg);
	addMessageToDisplay(rend, str, time_seconds);
	return;

	// Hidden old code

	if (strlen(msg) > MSG_MAX_CHARS) {
		msg[MSG_MAX_CHARS] = '\0';
	}

	update_all_text_line_pos();
	temp_str[0] = '\0';
	strcat(temp_str, player[p_id].name);
	strcat(temp_str, ": ");
	interface_setup_label(&line[0].label[0], rend, temp_str, font_roboto_black, player[p_id].sdl_color, 50, getWindowHeight() - 100, true);
	interface_setup_label(&line[0].label[1], rend, msg, font_roboto_black, white, 50 + line[0].label[0].rect.w + dist_k, getWindowHeight() - 100, true);
	line[0].end_time = SDL_GetTicks() + time_seconds * 1000;
	line[0].size = 2;
	current_lines++;
}

void renderMessageDisplay(SDL_Renderer* rend)
{
	int time = SDL_GetTicks();
	for (int i = current_lines - 1; i >= 0; i--) {
		for (int j = 0; j < line[i].size; j++) {
			if (line[i].end_time > time) {
				SDL_RenderCopy(rend, line[i].label[j].texture, NULL, &line[i].label[j].rect);
			}
			else {
				current_lines--;
			}
		}
	}
}

/*
#include "text_messages.h"
#include "events.h"
#include "interface_lib.h"

typedef struct Text_Line_t Text_L;

struct Text_Line_t {
	struct Label label[10];
	int removeTime;
	int size;					// Note that if the size is greater than instaniated label.texture it will crash
	int x;
	int y;

	Text_L* next;				// Node to next text line
};

int textMsgCount = 0;

Text_L* TextHead = NULL;			
Text_L* TextTail = NULL;
Text_L* removedHead;
Text_L* removedTail;

// Allocate memory
Text_L* createTextLine(int x, int y, int size, int duration_seconds)
{
	Text_L* t = malloc(sizeof(Text_L));
	t->x = x;
	t->y = y;
	t->size = size;
	t->removeTime = SDL_GetTicks() + 1000 * duration_seconds;
	textMsgCount++;
	t->next = NULL;
	return t;
}

// Free memory
void destroyTextLine(Text_L *t) {
	printf("destroyed\n");
	for (int i = 0; i < t->size; i++) {
	//	SDL_DestroyTexture(t->label[i].texture);
	}
	free(t);
	textMsgCount--;
}

// Add Text_L to the linked list
void indexTextLine(Text_L *t)
{
	if (TextHead == NULL) {
		TextHead = t;
		TextTail = t;
	}
	else if (TextTail == TextHead) {
		TextHead->next = t;
		TextTail = t;
	}
	else {
		TextTail->next = t;
		TextTail = t;
	}
}

// Remove Text_L from the linked list
void deindexTextLine(Text_L *t)
{
	Text_L *cur = TextHead;
	Text_L *prev = NULL;
	while (cur != NULL) {
		if (cur == t) {
			if (t == TextHead) {
				if (t == TextTail) {
					TextHead = TextTail = NULL;
				}
				else
					TextHead = TextHead->next;
			}
			else {
				if (cur == TextTail) {
					TextTail = prev;
				}
				prev->next = cur->next;
			}
		}
		prev = cur;
		cur = cur->next;
	}
}

struct Text_Line {
	struct Label label[10];
	int end_time;
	int size;
};

#define MAX_LINES		30	
#define MSG_MAX_CHARS	80

struct Text_Line line[MAX_LINES];

int dist_k;

TTF_Font* font_roboto_black;
SDL_Color white;

int h = 20;

int delta_h = -20;		// change distance on y-axis
int delta_w = 10;		// spacing between words

char* temp_str;
char* temp_str2;

void init_text_messages()
{
	font_roboto_black = TTF_OpenFont("fonts/roboto/Roboto-Black.ttf", 12);
	white = createColor(0xFF, 0xFF, 0xFF, 0);

	dist_k = 10;		// ta bort

	current_lines = 2;			// bug fix: 2 instead of 0...
	temp_str = malloc(150);
	temp_str[0] = '\0';
}

void increase_all_y_pos()
{
	Text_L *cur = TextHead;
	while (cur != NULL) {
		for (int i = 0; i < cur->size; i++) {
			cur->label[i].rect.y += delta_h;
		}
		cur = cur->next;
	}
}

void renderTextLine(Text_L* t, SDL_Renderer* rend)
{
	for (int i = 0; i < t->size; i++) {
		SDL_RenderCopy(rend, t->label[i].texture, NULL, &t->label[i].rect);
	}
}

void renderMessageDisplay(SDL_Renderer* rend)
{
	int time = SDL_GetTicks();
	Text_L *cur = TextHead;
	removedHead = NULL;
	while (cur != NULL) {
		renderTextLine(cur, rend);
		// Add to remove index
		if (time > cur->removeTime) {
			if (removedHead == NULL) {
				removedHead = removedTail = cur;
			}
			else {
				removedTail->next = cur;
				removedTail = cur;
			}
		}
		cur = cur->next;
	}
	// Remove logic is flawed needs to be remade
	cur = removedHead;
	while (cur != NULL) {
		deindexTextLine(cur);
		//destroyTextLine(cur);
		cur = cur->next;
	}
}

void addMessageToDisplay(SDL_Renderer* rend, char* msg, int time_seconds)
{
	int x = 50;
	int y = getWindowHeight() - 100;
	int size = 1;

	increase_all_y_pos();
	Text_L* t = createTextLine(x, y, size, time_seconds/4);
	indexTextLine(t);
	interface_setup_label(&t->label[0], rend, msg, font_roboto_black, white, x, y, true);

	/*
	w = t->label[0].rect.w + delta_w;
	interface_setup_label(&t->label[1], rend, msg, font_roboto_black, white, x + w, y, true);

	increase_all_y_pos();

	t = createTextLine(x, y, 1, time_seconds);
	indexTextLine(t);
	interface_setup_label(&t->label[0], rend, msg, font_roboto_black, white, x, y, true);



	/*
	w = t->label[0].rect.w;
	printf("%d\n", w);
	interface_setup_label(&t->label[1], rend, msg, font_roboto_black, white, x + w + dist_k, y, true);
	printf("here?\n");
	
	while (1)
	{
		SDL_RenderClear(rend);
		renderTextLine(t, rend);
		renderMessageDisplay(rend);
		SDL_RenderPresent(rend);
		SDL_Delay(25);
	}
	*/

	/*
	printf("adding message...\n");
	if (strlen(msg) > MSG_MAX_CHARS) {
		msg[MSG_MAX_CHARS] = '\0';
	}

	for (int i = current_lines; i > 0; i--) {
		line[i] = line[i - 1];
		for (int j = 0; j < line[i].size; j++) {
			line[i - 1].label[j].rect.y -= h;
		}
	}
	SDL_Color white = { 255, 255, 255, 0 };
	interface_setup_label(&line[0].label[0], rend, msg, font_roboto_black, white, 50, getWindowHeight() - 100, true);
	line[0].end_time = SDL_GetTicks() + time_seconds * 1000;
	line[0].size = 1;
	current_lines++;
	printf("done adding message to display\n");
	
}
*/

/*
void addPlayerEmoteMessageToDisplay(SDL_Renderer* rend, int p_id, char* msg, int time_seconds)
{
	addMessageToDisplay(rend, msg, time_seconds);
	return;

	for (int i = current_lines; i > 0; i--) {
		line[i] = line[i - 1];
		for (int j = 0; j < line[i].size; j++) {
			line[i].label[j].rect.y -= h;
		}
	}
	interface_setup_label(&line[0].label[0], rend, player[p_id].name, font_roboto_black, player[p_id].sdl_color, 50, getWindowHeight() - 100, true);
	interface_setup_label(&line[0].label[1], rend, msg, font_roboto_black, white, 50 + line[0].label[0].rect.w + dist_k, getWindowHeight() - 100, true);
	line[0].end_time = SDL_GetTicks() + time_seconds * 1000;
	line[0].size = 2;
	current_lines++;
}


void addPlayerMessageToDisplay(SDL_Renderer* rend, int p_id, char* msg, int time_seconds)
{
	addMessageToDisplay(rend, msg, time_seconds);
	return;

	if (strlen(msg) > MSG_MAX_CHARS) {
		msg[MSG_MAX_CHARS] = '\0';
	}
	for (int i = current_lines; i > 0; i--) {
		line[i] = line[i - 1];
		for (int j = 0; j < line[i].size; j++) {
			line[i].label[j].rect.y -= h;
		}
	}
	temp_str[0] = '\0';
	strcat(temp_str, player[p_id].name);
	strcat(temp_str, ": ");
	interface_setup_label(&line[0].label[0], rend, temp_str, font_roboto_black, player[p_id].sdl_color, 50, getWindowHeight() - 100, true);
	interface_setup_label(&line[0].label[1], rend, msg, font_roboto_black, white, 50 + line[0].label[0].rect.w + dist_k, getWindowHeight() - 100, true);
	line[0].end_time = SDL_GetTicks() + time_seconds * 1000;
	line[0].size = 2;
	current_lines++;
}
*/

/*
void renderMessageDisplay(SDL_Renderer* rend)
{
	int time = SDL_GetTicks();
	for (int i = current_lines - 1; i >= 0; i--) {
		for (int j = 0; j < line[i].size; j++) {
			if (line[i].end_time > time) {
				SDL_RenderCopy(rend, line[i].label[j].texture, NULL, &line[i].label[j].rect);
			}
			else {
				current_lines--;
			}
		}
	}
}
*/

