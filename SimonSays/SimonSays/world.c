#include "world.h"
#include "graphics.h"

struct Camera {
	int x_min;
	int y_min;
	int x_max;
	int y_max;
};

struct World {
	int width;
	int height;
};

bool isInsideWorld(int x, int y)
{
	return (x > 0 && x < getWindowWidth() && y > 0 && y < getWindowHeight());
}

