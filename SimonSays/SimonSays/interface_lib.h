#pragma once
#include "libraries.h"

#define MAX_CH_TEXT_BOX 50		// maximum number of characters in a text box

struct Plane {
	SDL_Texture* texture;
	SDL_Rect rect;
	bool show;
};

struct Label {
	SDL_Texture* texture;
	SDL_Rect rect;
	bool show;
	int attach_offset_x;
	int attach_offset_y;
	int* ptr_attach_x;
	int* ptr_attach_y;
	bool attached;
};

struct TextBox {
	SDL_Texture* texture_wo_cursor;
	SDL_Texture* texture_w_cursor;
	SDL_Texture* background;
	//SDL_Texture* background_highlighted;		// Not implemented
	SDL_Rect rect_box;
	SDL_Rect rect_text_w;
	SDL_Rect rect_text_wo;
	SDL_Color color;
	TTF_Font* font;
	char text[MAX_CH_TEXT_BOX];
	bool show;
	bool selected;
	int size;
};

#define BTN_STATE_MOUSE_OVER			0
#define BTN_STATE_SELECTED				1
#define BTN_STATE_UNSELECTED			2

struct Button {
	SDL_Texture* texture_mouse_over;
	SDL_Texture* texture_selected;
	SDL_Texture* texture_unselected;
	SDL_Texture* texture_text;
	SDL_Rect rect_box;
	SDL_Rect rect_text;
	int state;
	bool show;
};

// Plane
void interface_setup_plane(struct Plane* p, SDL_Texture* texture, int x, int y, int w, int h, bool show);
void interface_render_plane(struct Plane* p, SDL_Renderer* r);

// Text labels
void interface_setup_label(struct Label* l, SDL_Renderer* renderer, char* text, TTF_Font* f, SDL_Color color, int x, int y, bool show);
void interface_render_label(struct Label* l, SDL_Renderer* r);
void interface_attach_label(struct Label *l, int* ptr_x, int* ptr_y, int x_offset, int y_offset);

// Text box
void interface_setup_textbox(struct TextBox* tb, SDL_Texture* background_text, SDL_Renderer* rend, TTF_Font *f, SDL_Color c, SDL_Rect box);
void appendInTextBox(struct TextBox* tb, char* msg, SDL_Renderer* rend);
void interface_render_textbox(struct TextBox* tb, SDL_Renderer* r);
void clearTextBox(struct TextBox* tb, SDL_Renderer* rend);
void removeLastFromTextBox(struct TextBox* tb, SDL_Renderer* r);

void interface_setup_button(struct Button* btn, SDL_Renderer* rend, int x, int y, SDL_Texture* txt_mouse_over, SDL_Texture* txt_selected, SDL_Texture* txt_unselected, char* text, TTF_Font* font, SDL_Color text_color);
void interface_render_button(struct Button* btn, SDL_Renderer* rend);
