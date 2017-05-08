#include "animation.h"

void animation_setup(struct Animation *a, int col, int row, int cyclesPerFrame)
{
	a->cyclesPerFrame = cyclesPerFrame;
	a->tick = 0;
	a->index = 0;
	a->size = 0;
	a->complete = false;
	a->numOfFrames = col*row;
	a->col = col;
	a->row = row;
	//printf("Animation created: %d frames and %d cycles per frame.\n", a->numOfFrames, a->cyclesPerFrame);
}

void animation_addFrameColRow(struct Animation *a, int col, int row) {
	if (a->size < a->numOfFrames) {
		a->frameCol[a->size] = col;
		a->frameRow[a->size] = row;
		a->size++;
		if (a->size == a->numOfFrames) {
			printf("Animation was configured properly... Number of frames: %d. Configured: %d.\n", a->size, a->numOfFrames);
		}
		else if (a->size > a->numOfFrames) {
			printf("Error: Animationed was not configured properly.\n");
		}
	}
}

bool animation_copy(struct Animation *source, struct Animation *dest)
{
	animation_setup(dest, source->col, source->row, source->cyclesPerFrame);
	for (int i = 0; i < dest->numOfFrames; i++) {
		dest->frameCol[i] = source->frameCol[i];
		dest->frameRow[i] = source->frameRow[i];
		dest->size += 1;
	}
}

bool animation_isComplete(struct Animation *a)
{
	return a->complete;
}

void animation_tick(struct Animation *a)
{
	a->complete = false;
	a->tick += 1;
	if (a->tick == a->cyclesPerFrame) {
		a->tick = 0;
		a->index += 1;
		if (a->index >= a->numOfFrames) {
			a->index = 0;
			a->complete = true;
		}
	}
}

int animation_getCurColumn(struct Animation *a)
{
	return a->frameCol[a->index];
}

int animation_getCurRow(struct Animation *a)
{
	return a->frameRow[a->index];
}