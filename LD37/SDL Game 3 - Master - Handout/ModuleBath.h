#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include <random>
#include <chrono>
#include <time.h>
using namespace std;


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
	double randomVar;
	double randomVar2;
	mt19937_64 range2;
	mt19937_64 range3;
	uint64_t timeSeed2;
	uint64_t timeSeed3;
	SDL_Texture* background;
	Uint64 t1, t2;

};