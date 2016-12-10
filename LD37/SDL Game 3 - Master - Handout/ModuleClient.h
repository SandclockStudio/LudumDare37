#ifndef __ModuleCLient_H__
#define __ModuleCLient_H__
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

class ModuleClient : public Module
{
public:
	ModuleClient(Application* app, bool start_enabled);
	~ModuleClient();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics;
	Collider* collider;
	Animation* current_animation;
	Animation idle;
	Animation up;
	Animation down;
	p2Point<int> position;
	bool exploding;
};

#endif // __ModuleCLient_H__
