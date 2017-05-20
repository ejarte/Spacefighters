#include "libraries.h"
#include "definition.h"
#include "sprite.h"

typedef struct Particle_type Particle;
int particle_count;;
bool particle_debug_enabled;
void particle_init();
void createParticle(int x, int y, int w, int h, int life, double angleInDeg, double speed, SDL_Texture* texture);

void destroyParticle(Particle *p);
void particle_update(Particle *p);
bool particle_isDead(Particle *p);
void particle_render_all(SDL_Renderer* renderer);
void particle_render(SDL_Renderer* renderer, Particle* p);
void indexParticle(Particle *p);
void deindexParticle(Particle *p);
void particle_tick_all();
