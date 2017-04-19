#include "effect.h"

struct Effect_type {
	Animation *anim;
	Sprite **sprite;
	bool finished;
	bool oneShot;
	bool render;
};

Effect *createEffect(Sprite **s, Animation *anim_type, bool oneShot)
{
	Effect *e = malloc(sizeof(Effect));
	e->sprite = s;
	e->anim = copyAnimationType(anim_type);
	e->finished = false;
	e->oneShot = oneShot;
	e->render = true;
	return e;
}

void destroyEffect(Effect *e)
{
	free(e);
}

void effect_tick(Effect *e)
{
	anim_tick(e->anim);
	// If the animation is flagged as oneShot stop rendering it
	if (anim_isFinished(e->anim) && e->oneShot == true) {
		e->finished = true;
		e->render = false;
	}
}

void effect_render(SDL_Renderer* renderer, Effect *e, SDL_Rect disp_rect)
{
	if (e->render == true) {
		Sprite **s = e->sprite;
		Sprite *s2 = *s;
		sprite_RenderCopy(renderer, s2, anim_getCurCol(e->anim), anim_getCurRow(e->anim), disp_rect);
	}
}

void effect_reset(Effect *e)
{
	e->finished = false;
	e->render = true;
	e->anim = copyAnimationType(e->anim);
}