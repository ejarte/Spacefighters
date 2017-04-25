#include "projectile.h"

struct Projectile_type {
	int damage;				// Damage on impact
	Object* obj;			// Projectile object
	Spaceship* source;		// Spaceship source
};

Projectile* createProjectile(Object* projectileObj, Spaceship* source, int damage)
{
	int i;	// index of projectile object
	int j;	// index of spaceship body
		
	i = object_getObjId(projectileObj);
	if (projectile[i] == NULL)
		projectile[i] = malloc(sizeof(Projectile));

	projectile[i]->obj = projectileObj;
	projectile[i]->source = source;
	projectile[i]->damage = damage;

	Object *ObjSource = spaceship_getBody(source);
	j = object_getObjId(ObjSource);
	object_setCustomId(projectile[i]->obj, j);

	printf("debug: %d\n", object_getCustomId(projectile[i]->obj));

	//printf("created projectile: ij: %d %d\n", i, j);
	return projectile[i];
}

void destroyProjectile(Projectile *p)
{
}

// Byt namn på detta till source t.ex.
/* if the custom value of the object is equal to the object id of the other it means that one of them is a projectile */
bool projectile_isSource(Object* proj_obj, Object* other_obj)
{
	return object_getCustomId(proj_obj) == object_getObjId(other_obj);
}

bool projectile_ObjIsValidTarget(Object* source, Object* target)
{

}