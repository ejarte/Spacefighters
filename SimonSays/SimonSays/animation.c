#include "animation.h"

struct Animation_type {
	int *sprite_col_seq;
	int *sprite_row_seq;
	int length;
	int cyclesPerFrame;
	int index;				// Current row and col
	int size;
	int time;
	bool completed;			// Flag
};

Animation* createAnimation(int length, int cyclesPerFrame)
{
	Animation *a = malloc(sizeof(Animation));
	a->sprite_col_seq = malloc(sizeof(int) * (length + 1));
	a->sprite_row_seq = malloc(sizeof(int) * (length + 1));
	a->length = length;
	a->size = 0;
	a->time = 0;
	a->cyclesPerFrame = cyclesPerFrame;
	a->index = 0;
	a->completed = false;
	return a;
}

Animation* copyAnimationType(Animation *srcs_a)
{	
	Animation *dest_a = createAnimation(srcs_a->length, srcs_a->cyclesPerFrame);

	for (int i = 0; i < srcs_a->length; i++) {
		dest_a->sprite_col_seq[i] = srcs_a->sprite_col_seq[i];
		dest_a->sprite_row_seq[i] = srcs_a->sprite_row_seq[i];
	}
	dest_a->size = srcs_a->size;

	return dest_a;
}

void destroyAnimation(Animation *a)
{
	free(a->sprite_col_seq);
	free(a->sprite_row_seq);
	free(a);
}

int anim_getCurCol(Animation *a)
{
	return a->sprite_col_seq[a->index];
}

int anim_getCurRow(Animation *a)
{
	return a->sprite_row_seq[a->index];
}

void anim_setCyclesPerFrame(Animation *a,  int cyclesPerFrame)
{
	if (cyclesPerFrame > 0) { // catch invalid input
		a->cyclesPerFrame = cyclesPerFrame;
	}
}

int anim_getFrameTime(Animation *a)
{
	return a->cyclesPerFrame;
}

void anim_addFrameColRow(Animation *a, int col, int row)
{
	if (a->size < a->length) {
		a->sprite_col_seq[a->size] = col;
		a->sprite_row_seq[a->size] = row;
		a->size += 1;
		if (a->size == a->length) {
			printf("Animation was configured properly...\n");
		}
	}
	else {
		printf("ERROR: IndexOutOfBounds(%d).\n", a->index);
	}
}

void anim_print(Animation *a)
{
	printf("-----------------------------------------\n");
	printf("- Animation -----------------------------\n");
	printf("-----------------------------------------\n");
	printf("Frame\t| Col\t| Row\t|\n");
	for (int i = 0; i < a->length; i++) {
		printf("%d\t| %d\t| %d\t|\n", i, a->sprite_col_seq[i], a->sprite_row_seq[i]);
	}
	printf("-----------------------------------------\n");
}

void anim_tick(Animation *a)
{
	if (a->completed) {
		a->completed = false;
	}
	a->time += 1;
	if (a->time == a->cyclesPerFrame) {
		// next frame
		a->time = 0;
		a->index += 1;
		if (a->index == a->size) {
			// Reset animation
			a->index = 0;
			a->completed = true;
		}
	}
}

bool anim_isFinished(Animation *a)
{
	if (a == NULL) {
		printf("Error: anim_isFinished - null pointer reference.\n");
		return true;
	}
	return a->completed;
}