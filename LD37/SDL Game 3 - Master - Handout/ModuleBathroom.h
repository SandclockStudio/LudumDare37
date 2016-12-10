#ifndef __ModuleBathroom_H__
#define __ModuleBathroom_H__


#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleCollision.h"

struct Bath
{
	Animation anim;
	unsigned int fx;
	p2Point<int> position;
	int shitCount;
	int paperCount;
	bool fx_played;
	Collider* collider;

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
	p2List<Bath> myBaths;


};

#endif // !