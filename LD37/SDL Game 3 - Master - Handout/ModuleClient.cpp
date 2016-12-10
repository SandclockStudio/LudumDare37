#include "Globals.h"
#include "Application.h"
#include "ModuleClient.h"

ModuleClient::ModuleClient(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	collider = NULL;
	current_animation = NULL;
	//exploding = false;

	// idle animation
	idle.frames.PushBack({ 66, 1, 32, 14 });

	// move upwards
	up.frames.PushBack({ 100, 1, 32, 14 });
	up.frames.PushBack({ 132, 0, 32, 14 });
	up.loop = false;
	up.speed = 0.1f;

	// Move down
	down.frames.PushBack({ 33, 1, 32, 14 });
	down.frames.PushBack({ 0, 1, 32, 14 });
	down.loop = false;
	down.speed = 0.1f;
}

ModuleClient::~ModuleClient()
{}

// Load assets
bool ModuleClient::Start()
{
	LOG("Loading client");

	graphics = App->textures->Load("rtype/ship.png");

	position.x = 150;
	position.y = 50;
	collider = App->collision->AddCollider({ position.x, position.y, 32, 14 }, COLLIDER_CLIENT, this);
	exploding = false;

	return true;
}

// Unload assets
bool ModuleClient::CleanUp()
{
	LOG("Unloading client");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleClient::Update()
{
	if (exploding == true)
		return UPDATE_CONTINUE;

	int speed = 1;

	collider->SetPos(position.x, position.y);

	// Draw everything --------------------------------------
	current_animation = &idle;
	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

// Collision detection
void ModuleClient::OnCollision(Collider* c1, Collider* c2)
{
	if (exploding == false)
	{
		App->fade->FadeToBlack(App->scene_space, App->scene_intro);
		exploding = true;
		App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	}
}
