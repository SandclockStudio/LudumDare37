#include "Globals.h"
#include "Application.h"
#include "ModuleCloset.h"


ModuleCloset::ModuleCloset(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModuleCloset::~ModuleCloset()
{}

// Load assets
bool ModuleCloset::Start()
{	
	return true;
}

// UnLoad assets
bool ModuleCloset::CleanUp()
{
	return true;
}

// Update: draw background
update_status ModuleCloset::Update()
{
	if (App->player->position.x > 0 && App->player->position.x < 100 && App->player->position.y>50 && App->player->position.y < 60)
	{
		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_UP)
		{
			App->particles->AddParticle(App->particles->plunger, 50, 50);
			App->player->plunger = true;
		}
		if (App->input->GetKey(SDL_SCANCODE_E) == KEY_UP)
		{
			App->particles->AddParticle(App->particles->paper, 50, 50);
			App->player->paper = true;
		}
	}

	return UPDATE_CONTINUE;
}