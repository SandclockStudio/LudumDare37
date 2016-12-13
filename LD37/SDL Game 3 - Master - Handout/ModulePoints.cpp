#include "Globals.h"
#include "Application.h"
#include "ModulePoints.h"
#include "p2Point.h"

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
	if (App->bath_scene->IsEnabled())
	{
		p2Point<int> pointP2;
		pointP2 = giveNumbers(points);

		if (pointP2.x == 0)
		{
			App->particles->AddParticle(App->particles->zero, SCREEN_WIDTH - 50, 20);
		}
		if (pointP2.x == 1)
		{
			App->particles->AddParticle(App->particles->one, SCREEN_WIDTH - 50, 20);
		}
		if (pointP2.x == 2)
		{
			App->particles->AddParticle(App->particles->two, SCREEN_WIDTH - 50, 20);
		}
		if (pointP2.x == 3)
		{
			App->particles->AddParticle(App->particles->three, SCREEN_WIDTH - 50, 20);
		}
		if (pointP2.x == 4)
		{
			App->particles->AddParticle(App->particles->four, SCREEN_WIDTH - 50, 20);
		}
		if (pointP2.x == 5)
		{
			App->particles->AddParticle(App->particles->five, SCREEN_WIDTH - 50, 20);
		}
		if (pointP2.x == 6)
		{
			App->particles->AddParticle(App->particles->six, SCREEN_WIDTH - 50, 20);
		}
		if (pointP2.x == 7)
		{
			App->particles->AddParticle(App->particles->seven, SCREEN_WIDTH - 50, 20);
		}
		if (pointP2.x == 8)
		{
			App->particles->AddParticle(App->particles->eight, SCREEN_WIDTH - 50, 20);
		}
		if (pointP2.x == 9)
		{
			App->particles->AddParticle(App->particles->nine, SCREEN_WIDTH - 50, 20);
		}



		if (pointP2.y == 0)
		{
			App->particles->AddParticle(App->particles->zero, SCREEN_WIDTH - 80, 20);
		}
		if (pointP2.y == 1)
		{
			App->particles->AddParticle(App->particles->one, SCREEN_WIDTH - 80, 20);
		}
		if (pointP2.y == 2)
		{
			App->particles->AddParticle(App->particles->two, SCREEN_WIDTH - 80, 20);
		}
		if (pointP2.y == 3)
		{
			App->particles->AddParticle(App->particles->three, SCREEN_WIDTH - 80, 20);
		}
		if (pointP2.y == 4)
		{
			App->particles->AddParticle(App->particles->four, SCREEN_WIDTH - 80, 20);
		}
		if (pointP2.y == 5)
		{
			App->particles->AddParticle(App->particles->five, SCREEN_WIDTH - 80, 20);
		}
		if (pointP2.y == 6)
		{
			App->particles->AddParticle(App->particles->six, SCREEN_WIDTH - 80, 20);
		}
		if (pointP2.y == 7)
		{
			App->particles->AddParticle(App->particles->seven, SCREEN_WIDTH - 80, 20);
		}
		if (pointP2.y == 8)
		{
			App->particles->AddParticle(App->particles->eight, SCREEN_WIDTH - 80, 20);
		}
		if (pointP2.y == 9)
		{
			App->particles->AddParticle(App->particles->nine, SCREEN_WIDTH - 80, 20);
		}



	}
	
	return UPDATE_CONTINUE;
}
bool ModulePoints::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	return true;
}

p2Point<int> ModulePoints::giveNumbers(int number)
{
	p2Point<int> pointP2;
	pointP2.x = number / 10;
	pointP2.y = number % 10;
	return pointP2;

}


