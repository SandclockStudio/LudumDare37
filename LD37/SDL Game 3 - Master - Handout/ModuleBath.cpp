#include "Globals.h"
#include "Application.h"
#include "ModuleBath.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBath::ModuleBath(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	background = NULL;

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
	t1 = SDL_GetPerformanceCounter();
	App->renderer->camera.x = App->renderer->camera.y = 0;
	App->client->AddClient(App->client->normal, 50, 50, COLLIDER_CLIENT);
	int scale = 4;



	// Añadir lavabos

	App->bathrooms->AddBathroom(App->bathrooms->bath, 8 * SCALE, 124 * SCALE, COLLIDER_BATHROOM);

	App->bathrooms->AddBathroom(App->bathrooms->bath, (8 + 40)* SCALE, 124 * SCALE, COLLIDER_BATHROOM);

	App->bathrooms->AddBathroom(App->bathrooms->bath, (8 + 40 * 2) * SCALE, 124 * SCALE, COLLIDER_BATHROOM);

	App->bathrooms->AddBathroom(App->bathrooms->bath, (8 + 40 * 3) * SCALE, 124 * SCALE, COLLIDER_BATHROOM);

	App->bathrooms->AddBathroom(App->bathrooms->bath, (8 + 40 * 4) * SCALE, 124 * SCALE, COLLIDER_BATHROOM);

	App->bathrooms->AddBathroom(App->bathrooms->bath, (8 + 40 * 5) * SCALE, 124 * SCALE, COLLIDER_BATHROOM);

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

	//random seed
	
	seed_seq ss{ uint32_t(timeSeed2 & 0xffffffff), uint32_t(timeSeed2 >> 32) };

	timeSeed2 = chrono::high_resolution_clock::now().time_since_epoch().count();
	range2.seed(ss);
	uniform_real_distribution<double> unif(0, 1);
	randomVar = unif(range2);
	t2 = SDL_GetPerformanceCounter();
	Uint64 time = (double)((t2 - t1) * 1000 / SDL_GetPerformanceFrequency());

	if(randomVar <=  0.2 && time >= 3000)
	{
		time = 0;
		t1 = SDL_GetPerformanceCounter();
		App->client->AddClient(App->client->normal, 50, 50, COLLIDER_CLIENT);
	}
	


	


	// Move camera forward if needed -----------------------------
	int scroll_speed = 0;

	SDL_Rect bground	= { 0 * SCALE, 0 * SCALE,	256 * SCALE, 192 * SCALE };

	SDL_Rect overlay	= { 256 * SCALE, 0 * SCALE,	256 * SCALE, 192 * SCALE };

	//SDL_Rect wcs = { 0 * SCALE, 326 * SCALE,	200 * SCALE, 64 * SCALE };



	//SDL_Rect sink		= { 0 * SCALE, 192 * SCALE,	160 * SCALE, 22 * SCALE};

	SDL_Rect sink		= { 0 * SCALE, 192 * SCALE,	41 * SCALE, 22 * SCALE };

	SDL_Rect closet		= { 0 * SCALE, 214 * SCALE, 48 * SCALE, 56 * SCALE };

	SDL_Rect door		= { 236 * SCALE, 192 * SCALE,	20 * SCALE, 27 * SCALE };


	App->renderer->Blit(background, 0, 0, &bground,0.0f);

	App->renderer->Blit(background, 236 * SCALE, 56 * SCALE, &door, 0.0f);

	App->renderer->Blit(background, 52 * SCALE, 4 * SCALE, &sink , 0.0f);
	App->renderer->Blit(background, (52 + 41) * SCALE, 4 * SCALE, &sink, 0.0f);
	App->renderer->Blit(background, (52 + 41 * 2) * SCALE, 4 * SCALE, &sink, 0.0f);
	App->renderer->Blit(background, (52 + 41 * 3) * SCALE, 4 * SCALE, &sink, 0.0f);
	App->renderer->Blit(background, (52 + 41 * 4) * SCALE, 4 * SCALE, &sink, 0.0f);



	App->renderer->Blit(background, 4 * SCALE, 4 * SCALE, &closet, 0.0f);

	App->renderer->Blit(background, 0 * SCALE, 0 * SCALE, &overlay, 0.0f);


	
	return UPDATE_CONTINUE;
}