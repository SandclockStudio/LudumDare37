#include "Globals.h"
#include "Application.h"
#include "ModuleBath.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBath::ModuleBath(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	background = NULL;
	stars = NULL;
}

ModuleBath::~ModuleBath()
{}

// Load assets
bool ModuleBath::Start()
{
	LOG("Loading space scene");
	
	background = App->textures->Load("ld37/spritesheet.png");

	App->collision->Enable(); // enable before player
	App->player->Enable();
	App->client->Enable();
	App->audio->PlayMusic("rtype/stage1.ogg", 1.0f);

	App->renderer->camera.x = App->renderer->camera.y = 0;
	App->client->AddClient(App->client->normal, 50, 50, COLLIDER_CLIENT);
	int scale = 4;



	App->bathrooms->AddBathroom(App->bathrooms->bath,8,280,COLLIDER_BATHROOM);

	App->bathrooms->AddBathroom(App->bathrooms->bath, 24*scale, 280, COLLIDER_BATHROOM);

	App->bathrooms->AddBathroom(App->bathrooms->bath, 44*scale , 280 , COLLIDER_BATHROOM);

	App->bathrooms->AddBathroom(App->bathrooms->bath, 64*scale , 280 , COLLIDER_BATHROOM);

	App->bathrooms->AddBathroom(App->bathrooms->bath, 84*scale , 280 , COLLIDER_BATHROOM);

	App->bathrooms->AddBathroom(App->bathrooms->bath, 104 * scale, 280, COLLIDER_BATHROOM);
	return true;
}

// UnLoad assets
bool ModuleBath::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background);
	App->player->Disable();
	App->collision->Disable();
	App->client->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleBath::Update()
{
	// Move camera forward if needed -----------------------------
	int scroll_speed = 0;

	int scale = 6;

	SDL_Rect bground = { 0 * scale,0 * scale,128 * scale, 96 * scale };
	
	SDL_Rect wcs = { 0,755,492,96 };

	SDL_Rect sink = {0,2003,495,71};

	
	
	
	App->renderer->Blit(background, 0, 0, &bground,0.0f);

	App->renderer->Blit(background, 8, 280,&wcs , 0.0f);

	App->renderer->Blit(background, 8, 7, &sink, 0.0f);


	
	return UPDATE_CONTINUE;
}