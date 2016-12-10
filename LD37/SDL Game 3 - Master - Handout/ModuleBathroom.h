#ifndef __ModuleBathroom_H__
#define __ModuleBathroom_H__


#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleCollision.h"
#include <time.h>
using namespace std;

struct Bath
{
	Animation openDoor,busyAnim, outOfPaper, clogged;

	unsigned int fx;
	p2Point<int> position;
	int shitCount;
	int paperCount;
	bool fx_played;
	bool busy;
	Collider* collider;
	bool openDoorAnim = false, busyFlagAnim = false, outOfPaperFlagAnim = false, cloggedFlagAnim = false;
	clock_t t1,t2;


	Bath();
	Bath(const Bath& p);

	bool Update();
};


class ModuleBathroom : public Module
{
public:

	ModuleBathroom(Application* app, bool start_enabled = true);
	~ModuleBathroom();
	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	void AddBathroom(const Bath & bathroom, int x, int y, COLLIDER_TYPE collider_type);
	Bath bath;
	Animation* current_animation;

	private:

	p2List<Bath*> active;
	SDL_Texture* graphics;

};

#endif // !