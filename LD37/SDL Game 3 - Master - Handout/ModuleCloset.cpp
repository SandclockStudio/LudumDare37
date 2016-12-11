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
	// Animacion plunger
	

	return true;
}

// UnLoad assets
bool ModuleCloset::CleanUp()
{
	return true;
}

update_status ModuleCloset::Update()
{
	if (App->player->position.x > 0 && App->player->position.x < 100 && App->player->position.y>0 && App->player->position.y < 100)
	{
		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN )//&& App->player->plunger == false)
		{
			App->particles->AddParticle(App->particles->plunger, 8, 8);
			App->player->plunger = true;
		}
		if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN && App->player->paper == false)
		{
			App->particles->AddParticle(App->particles->paper, 50, 50 );
			App->player->paper = true;
		}
	}

	return UPDATE_CONTINUE;
}