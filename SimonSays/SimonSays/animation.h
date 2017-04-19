#pragma once
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
