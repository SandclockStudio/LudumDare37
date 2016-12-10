
#include "Globals.h"
#include "Application.h"
#include "ModuleBathroom.h"
#include "Module.h"
#include "Application.h"

ModuleBathroom::ModuleBathroom(Application * app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleBathroom::~ModuleBathroom()
{
}

bool ModuleBathroom::Start()
{
	LOG("Loading baths");
	graphics = graphics = App->textures->Load("IMAGESHEET-BAÑO");
 
	// Animacion abrir baño
	bath.fx = App->audio->LoadFx("SONIDO-BAÑO-AL-ABRIRSE");
	bath.openDoor.frames.PushBack({ 274, 296, 33, 30 });
	bath.openDoor.loop = false;
	bath.openDoor.speed = 0.3f;

	// Animacion baño ocupado
	bath.fx = App->audio->LoadFx("SONIDO-BAÑO-AL-OCUPARSE");
	bath.busyAnim.frames.PushBack({ 274, 296, 33, 30 });
	bath.busyAnim.loop = false;
	bath.busyAnim.speed = 0.3f;

	// Animacion baño sin papel
	bath.fx = App->audio->LoadFx("SONIDO-BAÑO-AL-QUEDARSE-SIN-PAPEL");
	bath.outOfPaper.frames.PushBack({ 274, 296, 33, 30 });
	bath.outOfPaper.loop = false;
	bath.outOfPaper.speed = 0.3f;

	// Animacion baño atascado
	bath.fx = App->audio->LoadFx("SONIDO-BAÑO-AL-ATASCARSE");
	bath.clogged.frames.PushBack({ 274, 296, 33, 30 });
	bath.clogged.loop = false;
	bath.clogged.speed = 0.3f;



	return true;
}

update_status ModuleBathroom::Update()
{
	p2List_item<Bath*>* tmp = active.getFirst();
	p2List_item<Bath*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		Bath* p = tmp->data;
		tmp_next = tmp->next;
		
		//Animacion abrir puerta
		if(p->openDoorAnim == true)
		{
			App->renderer->Blit(graphics, p->position.x, p->position.y, &(p->openDoor.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				App->audio->PlayFx(p->fx);
			}
			if (p->openDoor.Finished())
			{
				p->openDoorAnim = false;
			}
		}

		//Animacion ocupado
		if (p->busyFlagAnim == true)
		{
			App->renderer->Blit(graphics, p->position.x, p->position.y, &(p->busyAnim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				App->audio->PlayFx(p->fx);
			}
			p->t2 = clock();
			if (difftime(p->t2, p->t1) > 5)
			{
				p->busyFlagAnim = false;
			}
		}



		//Animacion outOfPaper
		if (p->outOfPaperFlagAnim == true)
		{
			App->renderer->Blit(graphics, p->position.x, p->position.y, &(p->outOfPaper.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				App->audio->PlayFx(p->fx);
			}
			p->t2 = clock();
			if (difftime(p->t2, p->t1) > 5)
			{
				p->busyFlagAnim = false;
			}
		}

		tmp = tmp_next;
	}

	return UPDATE_CONTINUE;
}

bool ModuleBathroom::CleanUp()
{
	return false;
}

void ModuleBathroom::OnCollision(Collider * c1, Collider * c2)
{
	p2List_item<Bath*>* tmp = active.getFirst();


	while (tmp != NULL)
	{
		Collider* aux = tmp->data->collider;
		if (aux == c1 && c2->type == COLLIDER_CLIENT)
		{
			

			tmp->data->openDoorAnim = true;
			tmp->data->t1 = clock();

			break;
		}

		if (aux == c1 && c2->type == COLLIDER_PLAYER   && App->player->paper == true && tmp->data->paperCount > 10)
		{
			tmp->data->animDoor = true;
			break;
		}

		if (aux == c1 && c2->type == COLLIDER_PLAYER && App->player->paper == true && tmp->data->shitCount > 15)
		{
			tmp->data->animDoor = true;
			break;
		}
	}

	tmp = tmp->next;
}

void ModuleBathroom::AddBathroom(const Bath& bathroom, int x, int y, COLLIDER_TYPE collider_type)
{
	Bath* p = new Bath(bathroom);
	p->position.x = x;
	p->position.y = y;

	if (collider_type != COLLIDER_NONE)
	{
		p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 0, 0 }, collider_type, this);
	}

}


Bath::Bath()
{}

Bath::Bath(const Bath & p)
{
	shitCount = p.shitCount;
	paperCount = p.paperCount;
	fx_played = false;
	busy = p.busy;
}



bool Bath::Update()
{
	return false;
}
