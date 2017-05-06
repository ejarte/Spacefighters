#include "interface_lib.h"

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

void interface_render_plane(struct Plane* p, SDL_Renderer* r)
{
	if (p->show)
		SDL_RenderCopy(r, p->texture, NULL, &p->rect);
}

void interface_setup_label(struct Label* l, SDL_Renderer* renderer, char* text, TTF_Font* f, SDL_Color color, int x, int y, bool show)
{
	SDL_Surface* surface = TTF_RenderText_Solid(f, text, color);
	l->texture = SDL_CreateTextureFromSurface(renderer, surface);
	l->rect.x = x;
	l->rect.y = y;
	l->rect.w = surface->w;
	l->rect.h = surface->h;
	l->show = show;
	SDL_FreeSurface(surface);	
	l->attached = false;
}

void interface_attach_label(struct Label *l, int* ptr_x, int* ptr_y, int x_offset, int y_offset)
{
	l->attached = true;
	l->attach_offset_x = x_offset;
	l->attach_offset_y = y_offset;
	l->ptr_attach_x = ptr_x;
	l->ptr_attach_y = ptr_y;
}

void interface_render_label(struct Label* l, SDL_Renderer* r)
{
	if (l->show) {
		if (l->attached) {
			l->rect.x = *l->ptr_attach_x + l->attach_offset_x;
			l->rect.y = *l->ptr_attach_y + l->attach_offset_y;
		}
		SDL_RenderCopy(r, l->texture, NULL, &l->rect);
	}
}

/*
struct TextBox {
	SDL_Texture* texture;
	SDL_Rect rect_text;
	SDL_Rect rect_box;
	char message[100];
	int max_ch;
	bool show;
	bool selected;
};
*/

/*
SDL_Surface* surface = TTF_RenderText_Solid(f, text, color);
l->texture = SDL_CreateTextureFromSurface(renderer, surface);
l->rect.x = x;
l->rect.y = y;
l->rect.w = surface->w;
l->rect.h = surface->h;
l->show = show;
SDL_FreeSurface(surface);
l->attached = false;
*/

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
}

void appendInTextBox(struct TextBox* tb, char* msg, SDL_Renderer* rend)
{
	SDL_Surface* surface;
	SDL_Texture* t;
	int w, h;
	char* str = malloc(100);
	str[0] = '\0';
	strcat(tb->text, msg);
	strcat(str, tb->text);
	strcat(str, "| ");

	// Creates a sample of the desired output
	surface = TTF_RenderText_Solid(tb->font, str, tb->color);
	t = SDL_CreateTextureFromSurface(rend, surface);
	SDL_QueryTexture(tb->texture_w_cursor, NULL, NULL, &w, &h);
	if (tb->rect_box.w - 10 < w) {
		printf("Error: Text did not fit inside the box\n");
	}
	else {
		// Remove previous textures
		tb->size += strlen(msg);
		SDL_DestroyTexture(tb->texture_wo_cursor);
		SDL_DestroyTexture(tb->texture_w_cursor);
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
