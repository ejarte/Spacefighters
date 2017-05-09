#include "interface_lib.h"

/*	Author(s):	Tiago Redaelli
*	Modified:	09-05-2017
*	Version:	0.

	File includes API for configuring different type of interface structs such as plane, label and button,
	as well as some support functionality for said structs. 
*/



// Configures a plane with a texture with given x, y, w, h properties for the rect and a flag for if it's shown or not.
// @p					: Plane struct
// @rend				: renderer

void interface_setup_plane(struct Plane* p, SDL_Texture* texture, int x, int y, int w, int h, bool show)
{
	int w_, h_;
	if (texture != NULL) {
		SDL_QueryTexture(texture, NULL, NULL, &w_, &h_);
		p->texture = texture;
		if (w <= 0) {
			p->rect.w = w_;
		}
		else {
			p->rect.w = w;
		}
		if (h <= 0) {
			p->rect.h = h_;
		}
		else {
			p->rect.h = h;
		}
		p->rect.x = x;
		p->rect.y = y;
		p->show = show;
	}
	else {
		printf("ERROR: failed to create Plane, no texture found.\n");
	}
}

// Renders the plane if it's set to be shown
// @p					: Plane struct
// @rend				: renderer

void interface_render_plane(struct Plane* p, SDL_Renderer* rend)
{
	if (p->show)
		SDL_RenderCopy(rend, p->texture, NULL, &p->rect);
}

// Configures a text label, takes: renderer, font, text, color, x, y, show (flag) and renders a texture based on the text
// @l					: Label struct
// @rend				: renderer
// @text				: displayed text
// @font				: text font
// @color				: text color
// @x					: topX of the label
// @Y					: topY of the label

void interface_setup_label(struct Label* l, SDL_Renderer* rend, char* text, TTF_Font* font, SDL_Color color, int x, int y, bool show)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
	l->texture = SDL_CreateTextureFromSurface(rend, surface);
	l->rect.x = x;
	l->rect.y = y;
	l->rect.w = surface->w;
	l->rect.h = surface->h;
	l->show = show;
	SDL_FreeSurface(surface);	
	l->attached = false;
}

// Attaches the x and y coordinates of the label to x and y pointers with a given offset
// @l				: Label struct
// @ptr_x			: x-coordinate pointer
// @ptr_y			: y-coordinate pointer
// @x_offset		: offset from the x coordinate (redefines the configured topX)
// @x_offset		: offset from the y coordinate (redefines the configured topY)

void interface_attach_label(struct Label *l, int* ptr_x, int* ptr_y, int x_offset, int y_offset)
{
	l->attached = true;
	l->attach_offset_x = x_offset;
	l->attach_offset_y = y_offset;
	l->ptr_attach_x = ptr_x;
	l->ptr_attach_y = ptr_y;
}

// Renders the text label
// @l				: Label struct
// @r				: renderer

void interface_render_label(struct Label* l, SDL_Renderer* r)
{
	if (l->show) {
		if (l->attached) {	// if it has been attached reconfigure the rect.x and rect.y to the pointer x and y
			l->rect.x = *l->ptr_attach_x + l->attach_offset_x;
			l->rect.y = *l->ptr_attach_y + l->attach_offset_y;
		}
		SDL_RenderCopy(r, l->texture, NULL, &l->rect);
	}
}

// Configures a text box with a given background texture, font, text color, as well as a box dimension
// @tb					: TextBox struct
// @background_texture	: the texture inside the box
// @rend				: renderer
// @f					: text font
// @c					: text color
// @box					: rect that defines the parameters of the textbox

void interface_setup_textbox(struct TextBox* tb, SDL_Texture* background_text, SDL_Renderer* rend, TTF_Font *f, SDL_Color c, SDL_Rect box)
{
	SDL_Surface* surface;
	tb->size = 0;
	tb->rect_box = box;
	tb->rect_text_w = box;
	tb->rect_text_wo = box;
	tb->selected = false;
	tb->text[0] = '\0';
	tb->color = c;
	tb->font = f;
	tb->show = false;
	tb->background = background_text;
	surface = TTF_RenderText_Solid(tb->font, "|", tb->color);
	tb->texture_w_cursor = SDL_CreateTextureFromSurface(rend, surface);
	surface = TTF_RenderText_Solid(tb->font, " ", tb->color);
	tb->texture_wo_cursor = SDL_CreateTextureFromSurface(rend, surface);
	SDL_QueryTexture(tb->texture_w_cursor, NULL, NULL, &tb->rect_text_w.w, &tb->rect_text_w.h);
	SDL_QueryTexture(tb->texture_wo_cursor, NULL, NULL, &tb->rect_text_wo.w, &tb->rect_text_wo.h);
	SDL_FreeSurface(surface);
	// Adjust the text to be displayed in the center height of the chat box
	tb->rect_text_w.y = tb->rect_box.y + tb->rect_box.h / 2 - tb->rect_text_w.h / 2;		
	tb->rect_text_wo.y = tb->rect_box.y + tb->rect_box.h / 2 - tb->rect_text_wo.h / 2;
	// Adjust the text to be displayed slightly from the left edge
	tb->rect_text_w.x = tb->rect_box.x + 5;
	tb->rect_text_wo.x = tb->rect_box.x + 5;
}

void appendInTextBox(struct TextBox* tb, char* msg, SDL_Renderer* rend)
{
	SDL_Surface* surface;
	SDL_Texture* t;
	int w, h;
	char* str = malloc(100);
	str[0] = '\0';
	strcat(str, tb->text);
	strcat(str, msg);
	strcat(str, "| ");

	// Creates a sample of the desired output
	surface = TTF_RenderText_Solid(tb->font, str, tb->color);
	t = SDL_CreateTextureFromSurface(rend, surface);
	SDL_QueryTexture(t, NULL, NULL, &w, &h);
	if (tb->rect_box.w < w && tb->rect_box.h < h) {
		printf("Error: Text did not fit inside the box\n");
		SDL_DestroyTexture(t);
	}
	else {
		// Remove previous textures
		tb->size += strlen(msg);
		SDL_DestroyTexture(tb->texture_wo_cursor);
		SDL_DestroyTexture(tb->texture_w_cursor);
		strcat(tb->text, msg);
		// Set a texture with a cursor
		tb->texture_w_cursor = t;
		// Creates a texture without a cursor
		surface = TTF_RenderText_Solid(tb->font, tb->text, tb->color);
		tb->texture_wo_cursor = SDL_CreateTextureFromSurface(rend, surface);
		SDL_QueryTexture(tb->texture_w_cursor, NULL, NULL, &tb->rect_text_w.w, &tb->rect_text_w.h);		
		SDL_QueryTexture(tb->texture_wo_cursor, NULL, NULL, &tb->rect_text_wo.w, &tb->rect_text_wo.h);
	}

	SDL_FreeSurface(surface);
	free(str);
}

void removeLastFromTextBox(struct TextBox* tb, SDL_Renderer* rend)
{
	if (tb->size > 0) {
		char* str;
		SDL_Surface* surface;
		tb->size--;
		tb->text[tb->size] = '\0';
		SDL_DestroyTexture(tb->texture_wo_cursor);
		SDL_DestroyTexture(tb->texture_w_cursor);
		surface = TTF_RenderText_Solid(tb->font, tb->text, tb->color);
		tb->texture_wo_cursor = SDL_CreateTextureFromSurface(rend, surface);
		str = malloc(100);
		str[0] = '\0';
		strcat(str, tb->text);
		strcat(str, "| ");
		surface = TTF_RenderText_Solid(tb->font, str, tb->color);
		tb->texture_w_cursor = SDL_CreateTextureFromSurface(rend, surface);
		SDL_QueryTexture(tb->texture_w_cursor, NULL, NULL, &tb->rect_text_w.w, &tb->rect_text_w.h);
		SDL_QueryTexture(tb->texture_wo_cursor, NULL, NULL, &tb->rect_text_wo.w, &tb->rect_text_wo.h);
		free(str);
		SDL_FreeSurface(surface);
	}
}

void clearTextBox(struct TextBox* tb, SDL_Renderer* rend)
{
	if (tb->size > 0) {
		char* str;
		SDL_Surface* surface;
		tb->size = 0;
		tb->text[0] = '\0';
		SDL_DestroyTexture(tb->texture_wo_cursor);
		SDL_DestroyTexture(tb->texture_w_cursor);
		surface = TTF_RenderText_Solid(tb->font, tb->text, tb->color);
		tb->texture_wo_cursor = SDL_CreateTextureFromSurface(rend, surface);
		str = malloc(100);
		str[0] = '\0';
		strcat(str, tb->text);
		strcat(str, "| ");
		surface = TTF_RenderText_Solid(tb->font, str, tb->color);
		tb->texture_w_cursor = SDL_CreateTextureFromSurface(rend, surface);
		SDL_QueryTexture(tb->texture_w_cursor, NULL, NULL, &tb->rect_text_w.w, &tb->rect_text_w.h);
		SDL_QueryTexture(tb->texture_wo_cursor, NULL, NULL, &tb->rect_text_wo.w, &tb->rect_text_wo.h);
		free(str);
		SDL_FreeSurface(surface);
	}
}

void interface_render_textbox(struct TextBox* tb, SDL_Renderer* r)
{
	if (tb->show == true) {
		SDL_RenderCopy(r, tb->background, NULL, &tb->rect_box);
		if (tb->selected && SDL_GetTicks() % 1200 < 600) {
			SDL_RenderCopy(r, tb->texture_wo_cursor, NULL, &tb->rect_text_wo);
		}
		else {
			SDL_RenderCopy(r, tb->texture_w_cursor, NULL, &tb->rect_text_w);
		}
	}
}


// void interface_setup_textbox(struct TextBox* tb, SDL_Texture* background_text, SDL_Renderer* rend, TTF_Font *f, SDL_Color c, SDL_Rect box)

void interface_setup_button(struct Button* btn, SDL_Renderer* rend, int x, int y, SDL_Texture* txt_mouse_over, SDL_Texture* txt_selected, SDL_Texture* txt_unselected, char* text, TTF_Font* font, SDL_Color text_color)
{ 
	int w = 0;
	int h = 0;
	btn->rect_box.x = x;
	btn->rect_box.y = y;
	btn->texture_unselected = txt_unselected;
	btn->texture_selected = txt_selected;
	btn->texture_mouse_over = txt_mouse_over;
	SDL_QueryTexture(btn->texture_unselected, NULL, NULL, &w, &h);
	btn->rect_box.w = w;
	btn->rect_box.h = h;
	printf("%d %d\n", btn->rect_box.w, btn->rect_box.h);

	SDL_Surface* surface = TTF_RenderText_Solid(font, text, text_color);
	btn->texture_text = SDL_CreateTextureFromSurface(rend, surface);
	SDL_QueryTexture(btn->texture_text, NULL, NULL, &btn->rect_text.w, &btn->rect_text.h);
	btn->rect_text.x = btn->rect_box.x + btn->rect_box.w / 2 - btn->rect_text.w / 2;
	btn->rect_text.y = btn->rect_box.y + btn->rect_box.h / 2 - btn->rect_text.h / 2;
	btn->show = true;
	btn->state = BTN_STATE_UNSELECTED;
}

void interface_render_button(struct Button* btn, SDL_Renderer* rend)
{
	if (btn->show) {
		if (btn->state == BTN_STATE_MOUSE_OVER) {
			SDL_RenderCopy(rend, btn->texture_mouse_over, NULL, &btn->rect_box);
		}
		else if (btn->state == BTN_STATE_SELECTED) {
			SDL_RenderCopy(rend, btn->texture_selected, NULL, &btn->rect_box);
		}
		else {
			SDL_RenderCopy(rend, btn->texture_unselected, NULL, &btn->rect_box);
		}
		SDL_RenderCopy(rend, btn->texture_text, NULL, &btn->rect_text);
	}
}