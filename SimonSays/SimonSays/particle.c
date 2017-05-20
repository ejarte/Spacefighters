/*
*	File		:	particle.c
*	Author(s)	:	Tiago Redaelli
*	Modified	:
*	Version		:	0.2
*
*	Basic particle emitter with dynamic memory allocation and a linked list for iterating through the particles
*
*	Change-log
*	0.2 Fixed a bug that never deallocated dead particles
*/

#include "particle.h"
#include "graphics.h"
#include "definition.h"

#define MAX_PARTICLES 5000

struct Particle_type {
	int x;					// center x
	int y;					// center y 
	int w;					// width
	int h;					// height
	int life;				// life
	int vx;					// velocity x
	int vy;					// velocity y
	SDL_Texture* texture;	// Texture used

	//Particle *next;			// Node for linked index
};

Particle* particleHead = NULL;			// particle index head
Particle* particleTail = NULL;			// particle index tail
Particle* removedHead;
Particle* removedTail;
bool particle_initialized = false;

int cur_p;								// Current amount of particles

Particle particle[MAX_PARTICLES];

void particle_init()
{
	cur_p = 0;
}

void createParticle(int x, int y, int w, int h, int life, double angleInDeg, double speed, SDL_Texture* texture)
{
	particle[cur_p].x = x;
	particle[cur_p].y = y;
	particle[cur_p].w = w;
	particle[cur_p].h = h;
	particle[cur_p].life = life;
	particle[cur_p].vx = cos(angleInDeg * M_PI / 180) * speed;
	particle[cur_p].vy = sin(angleInDeg * M_PI / 180) * speed;
	particle[cur_p].texture = texture;
	cur_p++;
}

void particle_tick_all()
{
	for (int i = 0; i < cur_p; i++) {
		particle[i].life -= 1;
		particle[i].x += particle[i].vx;
		particle[i].y += particle[i].vy;
		if (particle[i].life <= 0) {
			particle[i] = particle[cur_p - 1];
			cur_p--;
			i--;
		}
	}
}
void particle_render(SDL_Renderer* renderer, Particle* p)
{
	SDL_Rect dsrect = { p->x - p->w / 2, p->y - p->w / 2, p->w, p->h };
	SDL_RenderCopy(renderer, p->texture, NULL, &dsrect);
}

void particle_render_all(SDL_Renderer* renderer)
{
	for (int i = 0; i < cur_p; i++) {
		particle_render(renderer, &particle[i]);
	}
}