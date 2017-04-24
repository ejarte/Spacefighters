#include "world.h"
#include "graphics.h"
#include "object.h"

void initWorld()
{
	
}

bool isInsideWorld(int x, int y)
{
	return (x > 0 && x < getWindowWidth() && y > 0 && y < getWindowHeight());
}

