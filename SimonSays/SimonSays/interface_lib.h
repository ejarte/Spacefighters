#pragma once
#include "libraries.h"

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

// Plane
void interface_setup_plane(struct Plane* p, SDL_Texture* texture, int x, int y, int w, int h, bool show);
void interface_render_plane(struct Plane* p, SDL_Renderer* r);

// Text labels
void interface_setup_label(struct Label* l, SDL_Renderer* renderer, char* text, TTF_Font* f, SDL_Color color, int x, int y, bool show);
void interface_render_label(struct Label* l, SDL_Renderer* r);
void interface_attach_label(struct Label *l, int* ptr_x, int* ptr_y, int x_offset, int y_offset);