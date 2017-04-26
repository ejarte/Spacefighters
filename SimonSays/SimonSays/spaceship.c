#include "spaceship.h"
#include "graphics.h"
#include "Object.h"

#define STATUS_DEAD				1
#define STATUS_ALIVE			2
#define STATUS_ALIVE_MOBILE		3
#define STATUS_ALIVE_INMOBILE	4
#define STATUS_ALIVE_INVUL		5
#define STATUS_ALIVE_SPEEDY		6

#define SPACESHIP_MASS	10

struct Spaceship_type {

	// Representation
	Object* body;

	// Position
	SDL_Point* p;

	// Speed
	double max_speed;
	double speed_x;
	double speed_y;
	double drag;
	double acc;
	double mass;
	bool mobile;

	// Status
	int status;
	double hp;
	double armor;
	double damage;
};

Spaceship *createSpaceship(Object *body)
{
	printf("Spaceship created...\n");
	Spaceship* s = malloc(sizeof(Spaceship));
	s->body = body;
	s->speed_x = 0;
	s->speed_y = 0;
	s->mobile = true;
	s->p = object_getPosPtr(body);
	return s;
}

// Not complete

Spaceship* copySpaceship(Spaceship* srcs, int x, int y, double facing)
{
	//Object* o = createObjectCopy(srcs->body, x, y, facing);
	Object* o;
	//Spaceship *dest = createSpaceship(x, y, facing, o);
	return o;
}

/*
Object* createObjectCopy(Object* srcs, int x, int y, double facing)
{
Object* dest = createObject(srcs->type, x, y, srcs->w, srcs->h, facing, srcs->sprite, srcs->anim, srcs->show, srcs->collision.enabled);
dest->scale = srcs->scale;
return dest;
}

*/

// Not complete
void destroySpaceship(Spaceship* s)
{
	// The body is not freed!
	free(s);
}

void spaceship_setBody(Spaceship* s,  Object* o)
{
	s->body = o;
}

Object* spaceship_getBody(Spaceship* s)
{
	return s->body;
}

// Position

int spaceship_getX(Spaceship* s) {
	return s->p->x;
}

int spaceship_getY(Spaceship* s) {
	return s->p->y;
}

SDL_Point spaceship_getPosition(Spaceship* s)
{
	SDL_Point p;
	p.x = s->p->x;
	p.y = s->p->y;
	return p;
}

// Facing Angle

void spaceship_setFacingAngle(Spaceship*s, double angle)
{
	object_setFacingAngle(s->body, angle);
}

void spaceship_setFacingToPoint(Spaceship* s, SDL_Point p)
{
	double newAngle, dx, dy;
	dx = s->p->x - p.x;
	dy = s->p->y - p.y;
	newAngle = (atan2(dx, dy) * 180.0) / M_PI *-1;			// får ut vinkeln i grader mellan muspekaren och bilden
	object_setFacingAngle(s->body, newAngle);
}

// Speed 

void spaceship_setSpeedX(Spaceship* s, double speed)
{
	s->speed_x = speed;
}

void spaceship_setSpeedY(Spaceship* s, double speed)
{
	s->speed_y = speed;
}

double spaceship_getSpeedX(Spaceship* s)
{
	return s->speed_x;
}

double spaceship_getSpeedY(Spaceship* s)
{
	return s->speed_y;
}

void spaceship_accelerateX(Spaceship *s)
{
	s->speed_x += s->acc;
	if (s->speed_x > s->max_speed)
		s->speed_x = s->max_speed;
}

void spaceship_accelerateY(Spaceship* s)
{
	s->speed_y += s->acc;
	overSpeedlimit(&s);
}

void spaceship_deaccelerateX(Spaceship *s)
{
	s->speed_x -= s->acc;
	if (s->speed_x < -1*s->max_speed)
		s->speed_x = -1*s->max_speed;
}

void spaceship_deaccelerateY(Spaceship *s)
{
	s->speed_y -= s->acc;
	overSpeedlimit(&s);
}

double overSpeedlimit(Spaceship *s)
{
	if (s->speed_y > s->max_speed && s->speed_y > 0)
	{
		s->speed_y = 0;//s->max_speed;
	}
	else if (s->speed_y < -s->max_speed && s->speed_y < 0)
	{
		s->speed_y = 0; //-s->max_speed;
	}
}

void spaceship_setDrag(Spaceship* s, double drag)
{
	s->drag = drag;
}

void spaceship_setAcceleration(Spaceship* s, double acc)
{
	s->acc = acc;
}

void spaceship_setMaxSpeed(Spaceship* s, double max)
{
	s->max_speed = max;
}

void spaceship_setMass(Spaceship* s, double max)
{
	s->mass = SPACESHIP_MASS;
}

void spaceship_move(Spaceship* s) {
	//printf("delta_X OBJ: %d\n", object_getDeltaX(s->body));
	if (s->mobile) {
		s->speed_x *= s->drag;
		s->speed_y *= s->drag;
		int spx = s->speed_x;
		int spy = s->speed_y;
		s->speed_x -= spx;
		s->speed_y -= spy;
		//printf("%d %d %f %f\n", spx, spy, s->speed_x, s->speed_y);
		object_addToDelta(s->body, spx, spy);

	}
}

bool spaceship_isMobile(Spaceship* s) 
{
	return s->mobile;
}

void spaceship_enableMobility(Spaceship *s)
{
	s->mobile = true;
}

void spaceship_disableMobility(Spaceship *s)
{
	s->mobile = false;
}

// Actions

void spaceship_onMove() 
{

}

void spaceship_onDeath(Spaceship* s)
{

}