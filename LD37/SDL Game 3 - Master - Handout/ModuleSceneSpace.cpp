#include "Globals.h"
#include "Application.h"
#include "ModuleSceneSpace.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneSpace::ModuleSceneSpace(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	background = NULL;
	stars = NULL;
}

ModuleSceneSpace::~ModuleSceneSpace()
{}

// Load assets
bool ModuleSceneSpace::Start()
{
	LOG("Loading space scene");
	
	background = App->textures->Load("rtype/background.png");

	App->collision->Enable(); // enable before player
	App->player->Enable();
	App->client->Enable();
	App->audio->PlayMusic("rtype/stage1.ogg", 1.0f);

	App->renderer->camera.x = App->renderer->camera.y = 0;
	App->client->AddClient(App->client->normal, 30, 50, COLLIDER_CLIENT);

	App->collision->AddCollider({0,224,3930, 16}, COLLIDER_WALL);
	App->collision->AddCollider({142, 192, 63, 48}, COLLIDER_WALL);
	App->collision->AddCollider({1376, 0, 560, 15}, COLLIDER_WALL);
	App->collision->AddCollider({1376, 15, 112, 79}, COLLIDER_WALL);
	App->collision->AddCollider({ 720, 192, 53, 45 }, COLLIDER_WALL);

	return true;
}

// UnLoad assets
bool ModuleSceneSpace::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background);
	App->player->Disable();
	App->collision->Disable();
	App->client->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneSpace::Update()
{
	// Move camera forward if needed -----------------------------
	int scroll_speed = 0;

	
	// Draw everything --------------------------------------
	App->renderer->Blit(background, 0, 0, NULL);

	
	return UPDATE_CONTINUE;
}