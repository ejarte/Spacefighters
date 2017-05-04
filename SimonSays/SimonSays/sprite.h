#pragma once

#include "libraries.h"
#include "definition.h"

void sprite_setup(struct Sprite *s, SDL_Renderer* renderer, char* filepath, int columns, int rows, SDL_Color colorKey);
SDL_Rect sprite_getClipRect(struct Sprite *s, int col, int row);
void sprite_RenderCopy(struct Sprite *s, SDL_Renderer* renderer, int col, int row, SDL_Rect dsrect);
SDL_Texture* sprite_getTexture(struct Sprite *s);
