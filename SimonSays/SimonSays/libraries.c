#include "libraries.h"


SDL_Rect createRect(int x, int y, int w, int h)
{
	SDL_Rect r = { x, y, w, h };
	return r;
}

SDL_Color createColor(int r, int g, int b, int a)
{
	SDL_Color c;
	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return c;
}

double distanceBetweenPointsCoordinates(int x1, int x2, int y1, int y2)
{
	int dx = x1 - x2;
	int dy = y1 - y2;
	return sqrt(dx*dx + dy*dy);
}

double distanceBetweenPoints(SDL_Point p1, SDL_Point p2)
{
	int dx = p1.x - p2.x;
	int dy = p1.y - p2.y;
	return sqrt(dx*dx + dy*dy);
}


/* Returns the angle between two coordinates in radians.*/
double angleBetweenPointsRad(SDL_Point p1, SDL_Point p2)
{
	int dx = p1.x - p2.x;
	int dy = p1.y - p2.y;

	double ax = (int)sqrt(dx*dx);	// side of triangle: x-axis
	double by = (int)sqrt(dy*dy);	// side of triangle: y-axis
	double angle = atan2(by, ax);	// funkar för klockan 3-6

	// Adjuct angle depending on quadrant

	if (dx > 0 && dy < 0) //klockan 6-9 - behöver ta reda på skillnaden mellan angle och 90 grader. Dubbla den vinkeln och lägg på angle.
		return (M_PI / 2 - angle) * 2 + angle;
	else if (dx > 0 && dy > 0) //klockan 9-12 - Ta vinkeln - 180 grader
		return M_PI + angle;
	else if (dx < 0 && dy > 0) //klockan 12-3 - Samma som klockan 3-6 fast 0 grader som riktlinje
		return angle - angle * 2;
	return angle;
}

SDL_Point getPolarProjectionPoint(SDL_Point source, double distance, double angle_rad)
{
	SDL_Point p;
	p.x = source.x + distance * cos(angle_rad);
	p.y = source.y + distance * sin(angle_rad);
	return p;
}

double radiansToDegrees(double radians)
{
	return radians * 180 / M_PI;
}

double degreesToRadians(double degree)
{
	return degree * (M_PI / 180);
}

double pointToAngle(double VectorX, double VectorY)
{
	return atan2(VectorY, VectorX);
}