#include "Globals.h"
#include "ModuleSilk.h"
#include "Application.h"

ModuleSilk::ModuleSilk(Application * app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSilk::~ModuleSilk()
{
}

bool ModuleSilk::Start()
{
	LOG("Loading sinks");
	graphics = App->textures->Load("ld37/spritesheet-bathroom.png");

	// Animacion grifo
	silk.fx = App->audio->LoadFx("rtype/starting.wav");
	silk.waterOpen.frames.PushBack({ 40 * SCALE, 192 * SCALE, 40 * SCALE, 22 * SCALE });
	silk.waterOpen.frames.PushBack({ 80 * SCALE, 192 * SCALE, 40 * SCALE, 22 * SCALE });
	silk.waterOpen.frames.PushBack({ 120 * SCALE, 192 * SCALE, 40 * SCALE, 22 * SCALE });
	silk.waterOpen.loop = false;
	silk.waterOpen.speed = 0.3f;

	return true;
}

update_status ModuleSilk::Update()
{
	p2List_item<Silk*>* tmp = active.getFirst();
	p2List_item<Silk*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		Silk* p = tmp->data;
		tmp_next = tmp->next;
		current_animation = &p->waterOpen;
		if (p->busy == true)
		{
			current_animation = &p->waterOpen;

			if (p->fx_played == false)
			{
				p->fx_played = true;
				App->audio->PlayFx(p->fx);
			}
		}



		App->renderer->Blit(graphics, p->position.x, p->position.y, &(current_animation->GetCurrentFrame()));
		tmp = tmp_next;
	}

	return UPDATE_CONTINUE;
}

void ModuleSilk::OnCollision(Collider * c1, Collider * c2)
{
	p2List_item<Silk*>* tmp = active.getFirst();


	while (tmp != NULL)
	{

		Collider* aux = tmp->data->collider;

		//Colision cliente pila
		if (aux == c1 && c2->type == COLLIDER_CLIENT && !tmp->data->busy)
		{
			tmp->data->busy = true;
			break;
		}

		//Colision para secar cliente
		if (aux == c1 && c2->type == COLLIDER_PLAYER   && tmp->data->busy)
		{
			App->player->giveTowel = true;
			tmp->data->busy = false;
			break;
		}

		tmp = tmp->next;
	}


}

void ModuleSilk::AddSilk(const Silk& sink, int x, int y, COLLIDER_TYPE collider_type)
{
	Silk* s = new Silk(sink);
	s->position.x = x;
	s->position.y = y;

	int scale = 4;

	if (collider_type != COLLIDER_NONE)
	{
		s->collider = App->collision->AddCollider({ s->position.x, s->position.y, 20 * scale, 10 * scale }, collider_type, this);
	}

	active.add(s);
}


Silk::Silk()
{
}

Silk::Silk(const Silk & p)
{
	fx_played = false;
	busy = false;
}

p2Point<int> Silk::getCenter(int offsetX, int offsetY)
{
	p2Point<int> center;
	center.x = (position.x + (20 * 4)) + offsetX;	
	center.y = (position.y + (17 * 4)) + offsetY;
	return center;
}

bool Silk::Update()
{
	return false;
}
