
#include "Globals.h"
#include "Application.h"
#include "ModuleBathroom.h"
#include "Module.h"
#include "Application.h"

ModuleBathroom::ModuleBathroom(Application * app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleBathroom::~ModuleBathroom()
{
}

bool ModuleBathroom::Start()
{
	LOG("Loading baths");
	graphics = graphics = App->textures->Load("IMAGESHEET-BAÑO");
 
	// Animacion baño 
	bath.fx = App->audio->LoadFx("SONIDO-BAÑO-AL-ABRIRSE");
	bath.anim.frames.PushBack({ 274, 296, 33, 30 });
	bath.anim.loop = false;
	bath.anim.speed = 0.3f;

	return true;
}

update_status ModuleBathroom::Update()
{
	return update_status();
}

bool ModuleBathroom::CleanUp()
{
	return false;
}

void ModuleBathroom::OnCollision(Collider * c1, Collider * c2)
{
}

void ModuleBathroom::AddBathroom(const Bath& bathroom, int x, int y, COLLIDER_TYPE collider_type)
{
	Bath* p = new Bath(bathroom);
	p->position.x = x;
	p->position.y = y;

	if (collider_type != COLLIDER_NONE)
	{
		p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 0, 0 }, collider_type, this);
	}

}


Bath::Bath()
{

	
}

Bath::Bath(const Bath & p)
{
	shitCount = p.shitCount;
	paperCount = p.paperCount;
	fx_played = false;
	busy = p.busy;
}



bool Bath::Update()
{
	return false;
}
