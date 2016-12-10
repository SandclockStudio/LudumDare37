#include "Globals.h"
#include "Application.h"
#include "ModuleAI.h"
#include "Module.h"


ModuleAI::ModuleAI(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleAI::~ModuleAI()
{
}

bool ModuleAI::Start()
{
	return true;
}

update_status ModuleAI::Update()
{
	return update_status();
}

bool ModuleAI::CleanUp()
{
	return true;
}

void ModuleAI::OnCollision(Collider * c1, Collider * c2)
{
}

