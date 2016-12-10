
#include "Globals.h"
#include "Application.h"
#include "ModuleBathroom.h"
#include "Module.h"

ModuleBathroom::ModuleBathroom(Application * app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleBathroom::~ModuleBathroom()
{
}

bool ModuleBathroom::Start()
{
	return false;
}

update_status ModuleBathroom::Update()
{
	return update_status();
}

bool ModuleBathroom::CleanUp()
{
	return false;
}

void ModuleBathroom::OnCollision(Collider * c1, Collider * c2)
{
}

bool Bath::Update()
{
	return false;
}
