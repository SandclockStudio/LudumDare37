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
	
	background = App->textures->Load("ld37/spritesheet-bathroom.png");

	App->collision->Enable(); // enable before player
	App->player->Enable();
	App->client->Enable();
	App->audio->PlayMusic("rtype/stage1.ogg", 1.0f);

	App->renderer->camera.x = App->renderer->camera.y = 0;
	App->client->AddClient(App->client->normal, 50, 50, COLLIDER_CLIENT);
	int scale = 4;


	// Añadir lavabos
	App->bathrooms->AddBathroom(App->bathrooms->bath, 8, 280, COLLIDER_BATHROOM);

	App->bathrooms->AddBathroom(App->bathrooms->bath, 24*scale, 280, COLLIDER_BATHROOM);

	App->bathrooms->AddBathroom(App->bathrooms->bath, 44*scale , 280 , COLLIDER_BATHROOM);

	App->bathrooms->AddBathroom(App->bathrooms->bath, 64*scale , 280 , COLLIDER_BATHROOM);

	App->bathrooms->AddBathroom(App->bathrooms->bath, 84*scale , 280 , COLLIDER_BATHROOM);

	App->bathrooms->AddBathroom(App->bathrooms->bath, 104 * scale, 280, COLLIDER_BATHROOM);

	//Añadir pilas
	
	App->silks->AddSilk(App->silks->silk, 24*scale, 2*scale, COLLIDER_SILK);

	App->silks->AddSilk(App->silks->silk, 45 * scale, 2 * scale, COLLIDER_SILK);

	App->silks->AddSilk(App->silks->silk, 65 * scale, 2 * scale, COLLIDER_SILK);

	App->silks->AddSilk(App->silks->silk, 85 * scale, 2 * scale, COLLIDER_SILK);

	App->silks->AddSilk(App->silks->silk, 105 * scale, 2 * scale, COLLIDER_SILK);

	App->collision->AddCollider({ 0, 0, 8, SCREEN_HEIGHT }, COLLIDER_WALL, this);
	App->collision->AddCollider({ SCREEN_WIDTH-8, 0, 8, 150 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ SCREEN_WIDTH - 8, 240, 8, 150 }, COLLIDER_WALL, this);
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
	App->silks->Disable();
	App->bathrooms->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleBath::Update()
{
	// Move camera forward if needed -----------------------------
	int scroll_speed = 0;

	int scale = 2;

	SDL_Rect bground	= { 0 * scale, 0 * scale,	256 * scale, 192 * scale };

	SDL_Rect overlay	= { 256 * scale, 0 * scale,	256 * scale, 192 * scale };
	
	SDL_Rect wcs		= { 0 * scale, 326 * scale,	200 * scale, 64 * scale };

	SDL_Rect sink		= { 0 * scale, 192 * scale,	160 * scale, 22 * scale};

	
	

	App->renderer->Blit(background, 0, 0, &bground,0.0f);

	App->renderer->Blit(background, 52 * scale, 4 * scale, &sink , 0.0f);

	App->renderer->Blit(background, 8 * scale, 124 * scale, &wcs, 0.0f);

	App->renderer->Blit(background, 0 * scale, 0 * scale, &overlay, 0.0f);


	
	return UPDATE_CONTINUE;
}