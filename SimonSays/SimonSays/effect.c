#include "effect.h"
#include "object.h"
#include "animation.h"

#define MAX_EFFECTS 300
bool effect_initialized = false;

struct Effects {
	Effect* eff[MAX_EFFECTS];
	int size;
};

struct Effects effects;

struct Effect_type {
	Object* object;
	bool oneShot;
	int index;
};

Effect *createEffect(Object *o)
{
	Effect* lastCreatedEffect = malloc(sizeof(Effect));	// allocates memory for effect

	if (effect_initialized == false) {
		effect_initialized = true;
		effects.size = 0;
	}
	int i = effects.size;								// gets the current index
	effects.eff[i] = lastCreatedEffect;					// indexes the last created effect
	effects.eff[i]->object = o;							// effect now points to a object to show on the screen
	effects.size++;										// increase the size of the effect index

	if (effects.size == 1) {							// Start a new thread to check if the effect is ready to be cleaned up
		// SDL_Thread *thread_server = SDL_CreateThread(startServer, "startServer", (int*)NULL);
	}
	return lastCreatedEffect;							// returns the last created effect.
}

void destroyEffect(Effect *e)
{
	destroyObject(e->object);
	free(e);
}

Object* effect_getObject(Effect* e)
{
	return e->object;
}

void removeFinishedEffects()
{
	if (effects.size == 0) {
		return;
	}

	Animation* a;
	Object* o;

	for (int i = 0; i < effects.size; i++) {
		o = effect_getObject(effects.eff[i]);
		a = object_getAnimation(o);
		if (anim_isFinished(a)) {
			printf("finished!\n");
			destroyEffect(effects.eff[i]);
			effects.size--;
			if (i < effects.size ) {
				effects.eff[i] = effects.eff[effects.size];
			}
		}
	}
}