#ifndef __ModuleCLient_H__
#define __ModuleCLient_H__
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct Client
{
	Animation idle, walking, washing;
	unsigned int timeBath, timeWaiting, timeSink, fx;
	p2Point<int> position;
	Uint32 born;
	Uint32 life;
	bool fx_played;
	Collider* collider;
	Client();
	Client(const Client& c);
	bool Update();

};

class ModuleClient : public Module
{
public:
	ModuleClient(Application* app, bool start_enabled);
	~ModuleClient();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	void AddClient(const Client& client, int x, int y, COLLIDER_TYPE = COLLIDER_NONE, Uint32 delay = 0);

private:
	SDL_Texture* graphics;
	p2List<Client*> active;

public:
	Client normal;
	
	
};

#endif // __ModuleCLient_H__
