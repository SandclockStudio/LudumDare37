#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct Collider;

class ModuleBath : public Module
{
public:
	ModuleBath(Application* app, bool start_enabled = true);
	~ModuleBath();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* background;
	SDL_Texture* stars;
};