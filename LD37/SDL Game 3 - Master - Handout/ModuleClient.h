#ifndef __ModuleCLient_H__
#define __ModuleCLient_H__
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleBathroom.h"
#include "ModuleSilk.h"
#include "conio.h"


struct Client
{
	Animation* current_animation;
	Animation idle, walking, washing;
	unsigned int timeBath, timeWaiting, timeSink, fx;
	unsigned int shitRest,paperRest;
	p2Point<int> position;
	Uint32 born;
	Uint32 life;
	bool fx_played;
	bool cleanRequest,handCleaned;
	Collider* collider;
	Bath* assignedBath;
	Silk* assignedSilk;
	bool waiting = false;
	bool ocuppied = false;
	int complainMeter = 0;
	bool pooping = false;
	bool pooped = false;
	bool washingHands;
	Uint64 t1, t2;
	


	Client();
	Client(const Client& c);
	bool Update();



	p2Point<int> GoToPosition(p2Point<int> target);
	void WaitForBath();
	p2Point<int> SearchBath();
	void Poop();

	p2Point<int> SearchSilk();
	void WashHands();
	

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
	Client* getClient(p2Point<int> pos);
	void AssignBaths(Client* c);
	void AssignSilks(Client* c);
private:
	SDL_Texture* graphics;
	p2List<Client*> active;

public:
	p2Point<int> position;
	Collider* collider;
	Client normal;
	Client fat;
	Animation* current_animation;


	
	
};

#endif // __ModuleCLient_H__
