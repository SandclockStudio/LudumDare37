#pragma once
#include "Application.h"

Application::Application()
{
	collision = new ModuleCollision(this, false);
	renderer = new ModuleRender(this);
	window = new ModuleWindow(this);
	textures = new ModuleTextures(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this, false);
	bath_scene = new ModuleBath(this, false);
	player = new ModulePlayer(this, false);
	client = new ModuleClient(this, false);
	scene_intro = new ModuleSceneIntro(this, true);
	fade = new ModuleFadeToBlack(this);
	particles = new ModuleParticles(this);
	ai = new ModuleAI(this,false);
	bathrooms = new ModuleBathroom(this, true);
	silks = new ModuleSilk(this, true);
	closet = new ModuleCloset(this, true);
	point = new ModulePoints(this, true);


	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(renderer);
	AddModule(textures);
	AddModule(input);
	AddModule(audio);
	
	
	
	// Scenes
	AddModule(bath_scene);
	AddModule(scene_intro);

	
	// Characters
	AddModule(player);
	AddModule(point);

	// Misc
	AddModule(particles);
	AddModule(collision);

	AddModule(client);
	AddModule(bathrooms);
	AddModule(closet);
	AddModule(silks);
	
	AddModule(ai);

	AddModule(fade); // let this after all drawing

}

Application::~Application()
{
	delete renderer;
	delete window;
	delete textures;
	delete input;
	delete particles;
	delete audio;
	delete scene_intro;
	delete bath_scene;
	delete player;
	delete client;
	delete fade;
	delete collision;
	delete bathrooms;
	delete silks;
	delete closet;
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	p2List_item<Module*>* item = list_modules.getFirst();

	while(item != NULL && ret == true)
	{
		ret = item->data->Init();
		item = item->next;
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	item = list_modules.getFirst();

	while(item != NULL && ret == true)
	{
		if(item->data->IsEnabled())
			ret = item->data->Start();
		item = item->next;
	}
	
	return ret;
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	p2List_item<Module*>* item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
			ret = item->data->PreUpdate();
		item = item->next;
	}

	item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
			ret = item->data->Update();
		item = item->next;
	}

	item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
			ret = item->data->PostUpdate();
		item = item->next;
	}

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	p2List_item<Module*>* item = list_modules.getLast();

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.add(mod);
}