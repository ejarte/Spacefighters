#include "particle.h"

struct Particle_type {
	int x;
	int y;
	int w;
	int h;
	int life;
	int vx;
	int vy;
	SDL_Texture* sprite;
	Particle *next;
};

Particle* particleHead = NULL;
Particle* particleTail = NULL;
bool particle_debug_enabled = true;
int particle_count = 0;

Particle* createParticle(int x, int y, int w, int h, int life, double angleInDeg, double speed, SDL_Texture* texture)
{
	particle_count++;
	Particle* p = malloc(sizeof(Particle));
	p->x = x;
	p->y = y;
	p->w = w;
	p->h = h;
	p->life = life;
	p->vx = cos(angleInDeg * M_PI / 180) * speed;
	p->vy = sin(angleInDeg * M_PI / 180) * speed;
	p->sprite = texture;
	p->next = NULL;
	indexParticle(p);
	return p;
}

void destroyParticle(Particle *p)
{
	particle_count--;
	free(p);
}

void particle_update(Particle *p)
{
	p->life -= 1;
	p->x += p->vx;
	p->y += p->vy;
}

bool particle_isDead(Particle *p)
{
	return p->life <= 0.;
}

void particle_render_all(SDL_Renderer* renderer)
{
	Particle *p = particleHead;
	while (p != NULL) {
		particle_render(renderer, p);
		p = p->next;
	}
}
void particle_render(SDL_Renderer* renderer, Particle* p)
{
	SDL_Rect dsrect = { p->x - p->w / 2, p->y - p->w / 2, p->w, p->h };
	SDL_RenderCopy(renderer, p->sprite, NULL, &dsrect);
}

void indexParticle(Particle *p)
{
	if (particleHead == NULL) {
		particleHead = p;
		particleTail = p;
	}
	else if (particleTail == particleHead) {
		particleHead->next = p;
		particleTail = p;
	}
	else {
		particleTail->next = p;
		particleTail = p;
	}
}

void deindexParticle(Particle *p)
{
	Particle *curParticle = particleHead;
	Particle *prevParticle = NULL;
	while (curParticle != NULL) {


		if (curParticle == p) {

			if (p == particleHead) {
				if (p == particleTail) {
					particleHead = particleTail = NULL;
				}
				else
					particleHead = particleHead->next;
			}
			else {
				if (curParticle == particleTail) {
					particleTail = prevParticle;
				}
				prevParticle->next = curParticle->next;
			}
		}
		prevParticle = curParticle;
		curParticle = curParticle->next;
	}
}

void particle_tick_all()
{
	Particle *curParticle = particleHead;
	Particle *next;
	while (curParticle != NULL) {
		next = curParticle->next;
		particle_update(curParticle);
		if (particle_isDead(curParticle)) {
			deindexParticle(curParticle);
			destroyParticle(curParticle);
		}
		curParticle = next;
	}
}
