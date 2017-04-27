#include "projectile.h"

struct Projectile_type {
	double damage;			// Damage on impact
	Object* obj;			// Projectile object
	Spaceship* source;		// Spaceship source
	int index;				// index of projectile
};

Projectile* createProjectile(Object* projectileObj, Spaceship* source, double damage)
{
	int i;	// index of projectile object
	int j;	// index of spaceship body
		
	i = object_getObjId(projectileObj);

	if (projectile[i] == NULL)
		projectile[i] = malloc(sizeof(Projectile));

	projectile[i]->obj = projectileObj;
	projectile[i]->source = source;
	projectile[i]->damage = damage;
	projectile[i]->index = i;

	Object *ObjSource = spaceship_getBody(source);
	j = object_getObjId(ObjSource);
	object_setCustomId(projectile[i]->obj, j);

	printf("debug: %d\n", object_getCustomId(projectile[i]->obj));

	//printf("created projectile: ij: %d %d\n", i, j);
	return projectile[i];
}

void destroyProjectile(Projectile *p)
{
	if (p == NULL) {
		printf("Error: destroyProjectile - null pointer reference!");
		return;
	}
	printf("projectile removed: %d\n.", p->index);
	int i = p->index;
	free(projectile[i]);
	projectile[i] = NULL;
}

/* if the custom value of the object is equal to the object id of the other it means that one of them is a projectile */
bool projectile_objectIsSource(Object* proj_obj, Object* other_obj)
{
	return object_getCustomId(proj_obj) == object_getObjId(other_obj);
}

double projectile_getDamage(Projectile *p)
{
	if (p == NULL) {
		printf("Error: projectile_getDamage - null pointer reference!\n");
		return 0.;
	}
	return p->damage;
}