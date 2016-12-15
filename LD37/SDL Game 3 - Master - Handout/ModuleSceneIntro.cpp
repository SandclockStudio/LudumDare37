#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	fx = 0;

	
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	menu = EXIT;

	graphics = App->textures->Load("ld37/spritesheet-UI.png");


	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	// Draw everything --------------------------------------	
	App->renderer->Blit(graphics, 0, 0, NULL);

	if(App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_UP && menu == START)
	{
		App->audio->PlayFx(fx);
		App->fade->FadeToBlack(this, App->bath_scene,1.0f);
	}

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_UP && menu == EXIT)
	{
		return UPDATE_STOP;
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP && menu == START)
	{
		menu = EXIT;
	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_UP && menu == EXIT)
	{
		menu = START;
	}

	if (menu == START)
	{
		SDL_Rect menu = { 511, 384,	512, 384 };
		App->renderer->Blit(graphics, 0, 0, &menu, 0.0f);
	}
	
	if (menu == EXIT)
	{
		SDL_Rect menu = { 0, 384,	512, 384 };
		App->renderer->Blit(graphics, 0, 0, &menu, 0.0f);
	}

	return UPDATE_CONTINUE;
}