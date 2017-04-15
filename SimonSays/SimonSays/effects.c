#include "effects.h"
#include "graphics.h"

#define SPEFF_COUNT				2	// List size: Number of effects

struct SpecialEffectType effect[SPEFF_COUNT];
int texture_count = -1;

struct SpecialEffectType {
	SDL_Texture* texture;
	SDL_Rect* frame;
	int cyclesBetweenFrames;
	int frIndex;
};
		
struct SpecialEffectType createSpecialEffectType(char* path, int cycleBetweenFrames)
{	
	struct SpecialEffectType sp;
	loadTexture(path, &sp.texture);
	if (sp.texture != NULL) {
		printf("Created SpecialEffect: %s.\n", path);
	}
	else {
		printf("Error: Failed to add SpecialEffect. %s.\n", path);
	}
	sp.frIndex = 0;
	sp.cyclesBetweenFrames = cycleBetweenFrames;
	return sp;
}

void addFrameToSpecialEffectType(struct SpecialEffectType speff, int x, int y, int w, int h)
{
	speff.frame[speff.frIndex].x = x;
	speff.frame[speff.frIndex].y = y;
	speff.frame[speff.frIndex].w = w;
	speff.frame[speff.frIndex].h = h;
	printf("Added frame [%d]: %d, %d, %d, %d.\n", speff.frIndex, x, y, w, h);
	speff.frIndex++;
}

void initSpecialEffectTypes()
{
	// explosion1
	effect[0] = createSpecialEffectType("images/explosion1.png");

	// spaceship
	effect[1] = createSpecialEffectType("images/spaceship.png", 4);
	addFrameToSpecialEffect(effect[1], 0, 0, 99, 154);
	addFrameToSpecialEffect(effect[1], 99, 0, 99, 154);
	addFrameToSpecialEffect(effect[1], 198, 0, 99, 154);
	addFrameToSpecialEffect(effect[1], 297, 0, 99, 154);

	// beams
	effect[2] = createSpecialEffectType("images/beams.png");
}

void cleanSpecialEffectTypes()
{
	for (int i = 0; i < SPEFF_COUNT; i++) {
		effect[i].texture = NULL;
	}
}

typedef struct SpecialEffect {
	unsigned int startTime;
	unsigned int stopTime;
	struct SpecialEffectType type;
	int currentFrame;
	int frameTime;
};

struct SpecialEffect createSpecialEffect(int x, int y, int indexType, int duration)
{	
	int time = SDL_GetTicks();
	struct SpecialEffect sp;
	sp.startTime = time;
	sp.stopTime = time + duration;
	sp.type = effect[indexType];
	sp.currentFrame = 0;
	sp.frameTime = 0;
}

void playEffect(struct SpecialEffect speff)
{
	speff.frameTime++;
	if (speff.frameTime == speff.type.cyclesBetweenFrames) {
		speff.currentFrame++;
		if (speff.currentFrame == speff.type.frIndex) {
			speff.currentFrame = 0;
		}
	}
}

