#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

public:

	bool plunger, paper;
	SDL_Texture* graphics;
	Collider* collider;
	Animation* current_animation;
	Animation idle;
	Animation idlePaper;
	Animation idlePlunger;

	Animation towel;
	Animation up;
	Animation down;
	Animation right;
	Animation left;

	Animation upPaper;
	Animation downPaper;
	Animation rightPaper;
	Animation leftPaper;

	Animation upPlunger;
	Animation downPlunger;
	Animation rightPlunger;
	Animation leftPlunger;

	Animation winGame;
	Animation loseGame;


	p2Point<int> position;
	bool exploding;
	bool giveTowel;
	bool collision;
};