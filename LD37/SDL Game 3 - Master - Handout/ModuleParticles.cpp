#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleParticles.h"

ModuleParticles::ModuleParticles(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");

	graphics = App->textures->Load("ld37/spritesheet-UI.png");
	iconPlunger.anim.frames.PushBack({ 612, 0, 50, 50});
	iconPlunger.anim.loop = true;
	iconPlunger.anim.speed = 0.05f;

	iconPaper.anim.frames.PushBack({ 762, 0, 50, 50 });
	iconPaper.anim.loop = true;
	iconPaper.anim.speed = 0.05f;

	
	graphics2 = App->textures->Load("ld37/numbers.png");
	one.anim.frames.PushBack({ 5,1,25,29 });
	one.anim.loop = true;
	one.anim.speed = 0.1f;

	two.anim.frames.PushBack({ 37,1,25,29 });
	two.anim.loop = true;
	two.anim.speed = 0.1f;

	three.anim.frames.PushBack({ 69,1,25,29 });
	three.anim.loop = true;
	two.anim.speed = 0.1f;

	four.anim.frames.PushBack({ 101,1,25,29 });
	four.anim.loop = true;
	four.anim.speed = 0.1f;

	five.anim.frames.PushBack({ 5,32,25,29 });
	five.anim.loop = true;
	five.anim.speed = 0.1f;

	six.anim.frames.PushBack({ 37,32,25,29 });
	six.anim.loop = true;
	six.anim.speed = 0.1f;

	seven.anim.frames.PushBack({ 69,32,25,29 });
	seven.anim.loop = true;
	seven.anim.speed = 0.1f;

	eight.anim.frames.PushBack({ 101,32,25,29 });
	eight.anim.loop = true;
	eight.anim.speed = 0.1f;

	nine.anim.frames.PushBack({ 5,66,25,29 });
	nine.anim.loop = true;
	nine.anim.speed = 0.1f;

	zero.anim.frames.PushBack({ 37,66,25,29 });
	zero.anim.loop = true;
	zero.anim.speed = 0.1f;
	//Animacion atascado
	//plogged.anim.frames.PushBack({ 512 + 56 * 2, 0, 56, 56 });

	// Animacion no plunger
	//noplunger.anim.frames.PushBack({ 0 * SCALE, 270 * SCALE, 48 * SCALE, 56 * SCALE });
	//noplunger.anim.frames.PushBack({ 48 * SCALE, 270 * SCALE, 48 * SCALE, 56 * SCALE });
	//noplunger.anim.frames.PushBack({ 96 * SCALE, 270 * SCALE, 48 * SCALE, 56 * SCALE });
	//noplunger.anim.frames.PushBack({ 144 * SCALE, 270 * SCALE, 48 * SCALE, 56 * SCALE });
	//noplunger.anim.loop = false;
	//noplunger.anim.speed = 0.3f;

	// Explosion particle
	//graphics = App->textures->Load("rtype/spritesheet-bathroom");
	//explosion.fx = App->audio->LoadFx("rtype/explosion.wav");
	//explosion.anim.frames.PushBack({274, 296, 33, 30});
	//explosion.anim.frames.PushBack({313, 296, 33, 30});
	//explosion.anim.frames.PushBack({346, 296, 33, 30});
	//explosion.anim.frames.PushBack({382, 296, 33, 30});
	//explosion.anim.frames.PushBack({419, 296, 33, 30});
	//explosion.anim.frames.PushBack({457, 296, 33, 30});
	//explosion.anim.loop = false;
	//explosion.anim.speed = 0.3f;

	//// Laser particle
	//laser.fx = App->audio->LoadFx("rtype/slimeball.wav");
	//laser.anim.frames.PushBack({200, 120, 32, 12});
	//laser.anim.frames.PushBack({230, 120, 32, 12});
	//laser.speed.x = 7;
	//laser.life = 1000;
	//laser.anim.speed = 0.05f;

	//Paper particle
	//Plunger particle

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);
	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	p2List_item<Particle*>* tmp = active.getFirst();
	p2List_item<Particle*>* tmp_next = active.getFirst();

	while(tmp != NULL)
	{
		Particle* p = tmp->data;
		tmp_next = tmp->next;

		if(p->Update() == false)
		{
			active.del(tmp);
			delete p;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->renderer->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			App->renderer->Blit(graphics2, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				App->audio->PlayFx(p->fx);
			}
		}
		

		tmp = tmp_next;
	}

	return UPDATE_CONTINUE;
}

// Always destroy particles that collide
void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
  	p2List_item<Particle*>* tmp = active.getFirst();


	while(tmp != NULL)
	{
		if(tmp->data->collider == c1 )
		{
			
			App->particles->AddParticle(App->particles->explosion, tmp->data->position.x, tmp->data->position.y);
			delete tmp->data;
			active.del(tmp);
			break;
		}

	
		tmp = tmp->next;
	}
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;

	if(collider_type != COLLIDER_NONE)
	{
		p->collider = App->collision->AddCollider({p->position.x, p->position.y, 0, 0}, collider_type, this);
	}

	active.add(p);
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle() : fx(0), born(0), life(0), fx_played(false), collider(NULL)
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : anim(p.anim), position(p.position), speed(p.speed), fx_played(false), collider(p.collider)
{
	fx = p.fx;
	born = p.born;
	life = p.life;
}

bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{
		if((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if(anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if(collider != NULL)
	{
		SDL_Rect r = anim.PeekCurrentFrame();
		collider->rect = {position.x, position.y, r.w, r.h};
	}

	return ret;
}