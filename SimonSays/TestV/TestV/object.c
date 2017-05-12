#include "object.h"

int obj_recycled[MAX_NUM_OBJ];
int obj_recycle_size;

void object_init()
{
	objHead = UNDEFINED;
	objTail = UNDEFINED;
	objIndex_size = 0;
	obj_recycle_size = 0;
	printf("Object Index Initialized...\n");

	for (int i = 0; i < MAX_NUM_OBJ; i++) {
		object[i].next = UNDEFINED;
	}
}

int object_index()
{
	int index;

	// Gets a unique index number

	// First it looks for a recycled number
	if (obj_recycle_size > 0) {
		obj_recycle_size--;
		index = obj_recycled[obj_recycle_size];
	}
	// Otherwise it generates a new one
	else {
		index = objIndex_size++;
	}

	// Links the new index into the chain

	// Add first
	if (objHead == UNDEFINED) {
		objHead = index;
		objHead = index;
		if (objTail == UNDEFINED) {
			objTail = index;
		}
		//	object[index].prev = UNDEFINED;	// define previous node
	}
	// Add after
	else {
		object[objTail].next = index;
		//object[index].prev = objTail;	// define previous node
		objTail = index;
	}
	object[index].next = UNDEFINED;		// define next node

	printf("%d indexed.\n", index);

	return index;
}


void  object_deindex(int index)
{

	int prev, next;

	// Recycles the number
	obj_recycled[obj_recycle_size++] = index;

	printf("Object deindexed: %d\n", index);

	// Removes the index from the linked list chain

	// Remove first
	if (objHead == index) {
		objHead = object[index].next;
	}
	// Remove after
	else {
		int prev = objHead;
		int cur = object[objHead].next;
		while (cur != UNDEFINED) {
			if (index == cur) {
				object[prev].next = object[cur].next;
				// remove tail
				if (index == objTail) {
					objTail = prev;
				}
				break;
			}
			prev = cur;
			cur = object[cur].next;
		}
		object[index].next = UNDEFINED;
	}
}


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