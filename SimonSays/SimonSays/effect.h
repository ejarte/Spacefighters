#pragma once

#include "libraries.h"
#include "sprite.h"
#include "animation.h"


typedef struct Effect_type Effect;


Effect *createEffect(Object* o, bool oneShot);
void destroyEffect(Effect *e);;
//void effect_tick(Effect *e);
//void effect_render(SDL_Renderer* renderer, Effect *e, SDL_Rect disp_rect);

//void effect_reset(Effect *e);