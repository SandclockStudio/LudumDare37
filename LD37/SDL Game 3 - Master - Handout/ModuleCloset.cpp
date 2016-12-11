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
	fx = App->audio->LoadFx("SONIDO-BAÑO-AL-ABRIRSE");
	plunger.frames.PushBack({ 0 * SCALE, 214 * SCALE, 48 * SCALE, 56 * SCALE });
	plunger.frames.PushBack({ 48 * SCALE, 214 * SCALE, 48 * SCALE, 56 * SCALE });
	plunger.frames.PushBack({ 96 * SCALE, 214 * SCALE, 48 * SCALE, 56 * SCALE });
	plunger.frames.PushBack({ 144 * SCALE, 214 * SCALE, 48 * SCALE, 56 * SCALE });
	plunger.frames.PushBack({ 0 * SCALE, 270 * SCALE, 48 * SCALE, 56 * SCALE });
	plunger.loop = false;
	plunger.speed = 0.3f;

	// Animacion no plunger
	noplunger.frames.PushBack({ 0 * SCALE, 270 * SCALE, 48 * SCALE, 56 * SCALE });
	noplunger.frames.PushBack({ 48 * SCALE, 270 * SCALE, 48 * SCALE, 56 * SCALE });
	noplunger.frames.PushBack({ 96 * SCALE, 270 * SCALE, 48 * SCALE, 56 * SCALE });
	noplunger.frames.PushBack({ 144 * SCALE, 270 * SCALE, 48 * SCALE, 56 * SCALE });
	noplunger.loop = false;
	noplunger.speed = 0.3f;

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
		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_UP && App->player->plunger == false)
		{
			App->particles->AddParticle(App->particles->plunger, 50, 50);
			App->player->plunger = true;
		}
		if (App->input->GetKey(SDL_SCANCODE_E) == KEY_UP)
		{
			App->particles->AddParticle(App->particles->paper, 50, 50 && App->player->paper == false);
			App->player->paper = true;
		}
	}

	return UPDATE_CONTINUE;
}