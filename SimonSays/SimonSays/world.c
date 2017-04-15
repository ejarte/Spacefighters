#include "world.h"
#include "graphics.h"

bool isInsideWorld(int x, int y)
{
	int w = getWindowWidth();
	int h = getWindowHeight();
	return (x > 0 && x < w && y > 0 && y < h);
}
