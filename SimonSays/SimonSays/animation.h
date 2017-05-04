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
