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
}

void interface_render_label(struct Label* l, SDL_Renderer* r)
{
	if (l->show)
		SDL_RenderCopy(r, l->texture, NULL, &l->rect);

}