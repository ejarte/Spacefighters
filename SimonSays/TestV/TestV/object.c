#include "object.h"

void object_setup(struct Object* o, int index, int type, int x, int y, int w, int h, double facingAng)
{
	o->id_index = index;
	o->id_type = type;
	o->center_x = x;
	o->center_y = y;
	o->prev_x = x;
	o->prev_y = y;
	o->w = w;
	o->h = h;

	o->ptr_center_x = &o->center_x;
	o->ptr_center_y = &o->center_y;

	o->facing = facingAng;
	o->show = true;
	o->delta_x = 0;
	o->delta_y = 0;
	o->speed_x = 0;
	o->speed_y = 0;
	o->speed_max = DEFAULT_MAX_SPEED;
	o->drag = DEFAULT_DRAG;
	o->acc = DEFAULT_ACC;
	o->collision.enabled = false;
	o->dmg_on_impact;				// used by projectiles
	o->next = UNDEFINED;			// used to iterate through all objects
	o->source_id = UNDEFINED;		// used by projectiles
	o->power_id = UNDEFINED;
}