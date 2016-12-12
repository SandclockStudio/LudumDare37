#ifndef __ModuleCloset_H__
#define __ModuleCloset_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"


class ModuleCloset : public Module
{
public:
	ModuleCloset(Application* app, bool start_enabled = true);
	~ModuleCloset();

	bool Start();
	update_status Update();
	bool CleanUp();

public: 
	SDL_Texture* graphics;
	SDL_Texture* stars;



};
#endif