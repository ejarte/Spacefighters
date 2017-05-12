#include "definitions.h"
#include "libaries.h"

int objHead;
int objTail;
int objIndex_size;


void object_init();					// Initializes the object index
int object_index();
void  object_deindex(int index);
void object_setup(struct Object* o, int index, int type, int x, int y, int w, int h, double facingAng);