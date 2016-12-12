#include "Globals.h"
#include "Application.h"
#include "ModulePoints.h"

ModulePoints::ModulePoints(Application * app, bool start_enabled) : Module(app, start_enabled)
{}

ModulePoints::~ModulePoints()
{

}

bool ModulePoints::Start()
{
	points = 0;
	return true;
}
update_status ModulePoints::Update()
{

	return UPDATE_CONTINUE;
}
bool ModulePoints::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	return true;
}
