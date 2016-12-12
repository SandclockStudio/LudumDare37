#ifndef __ModulePoints_H__
#define __ModulePoints_H__


#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"

using namespace std;

class ModulePoints : public Module
{
public:

	ModulePoints(Application* app, bool start_enabled = true);
	~ModulePoints();
	bool Start();
	update_status Update();
	bool CleanUp();
	int points;

private:


	SDL_Texture* graphics;

};
#endif // !