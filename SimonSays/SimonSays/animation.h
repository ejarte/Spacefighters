#pragma once

#include "libraries.h"
#include "definition.h"

void animation_setup(struct Animation *a, int col, int row, int cyclesPerFrame);
void animation_addFrameColRow(struct Animation *a, int col, int row);
void animation_tick(struct Animation *a);
bool animation_copy(struct Animation *source, struct Animation *dest);
int animation_getCurColumn(struct Animation *a);
int animation_getCurRow(struct Animation *a);
bool animation_isComplete(struct Animation *a);




//=====================//
// ~~ GAMMALT NEDAN ~~ // 
//=====================//



/*
struct Animation {
	int cyclesPerFrame;					// Number of cycles per frame
	int numOfFrames;					// Total number of frames			
	int frameCol[MAX_FRAME_TOT];
	int frameRow[MAX_FRAME_TOT];
	int tick;
	int index;
	int size;
	int col;
	int row;
	bool complete;
};

/*
#include "libraries.h"

typedef struct Animation_type Animation;

Animation* createAnimation(int length, int cyclesPerFrame);

Animation *copyAnimationType(Animation *srcs_a);

void destroyAnimation(Animation *a);

int anim_getCurCol(Animation *a);

int anim_getCurRow(Animation *a);

void anim_setCyclesPerFrame(Animation *a, int frameTime);

int anim_getFrameTime(Animation *a);

void anim_addFrameColRow(Animation *a, int col, int row);

void anim_tick(Animation *a);

void anim_print(Animation *a);

bool anim_isFinished(Animation *a);
*/