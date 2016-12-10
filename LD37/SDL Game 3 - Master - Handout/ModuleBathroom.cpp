
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
	bath.busyAnim.loop = true;
	bath.busyAnim.speed = 0.3f;

	// Animacion baño sin papel
	bath.fx = App->audio->LoadFx("SONIDO-BAÑO-AL-QUEDARSE-SIN-PAPEL");
	bath.outOfPaper.frames.PushBack({ 274, 296, 33, 30 });
	bath.outOfPaper.loop = true;
	bath.outOfPaper.speed = 0.3f;

	// Animacion baño atascado
	bath.fx = App->audio->LoadFx("SONIDO-BAÑO-AL-ATASCARSE");
	bath.clogged.frames.PushBack({ 274, 296, 33, 30 });
	bath.clogged.loop = true;
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
		
		if (p->paperCount > 0)
		{
			p->outOfPaperFlagAnim = true;
		}

		if (p->shitCount > 0)
		{
			p->outOfPaperFlagAnim = true;
		}

		//Animacion abrir puerta
		if(p->openDoorAnim == true)
		{
			current_animation = &p->openDoor;
			
			if (p->fx_played == false)
			{
				p->fx_played = true;
				App->audio->PlayFx(p->fx);
			}
		}

		//Animacion ocupado
		if (p->busyFlagAnim == true)
		{
			current_animation = &p->busyAnim;
			
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
			current_animation = &p->outOfPaper;
			if (p->fx_played == false)
			{
				p->fx_played = true;
				App->audio->PlayFx(p->fx);
			}

			
		}

		//Animacion atascado
		if (p->cloggedFlagAnim == true)
		{
			current_animation = &p->clogged;
			
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

		//Colision entrar en baño cliente.
		if (aux == c1 && c2->type == COLLIDER_CLIENT)
		{
		
			tmp->data->openDoorAnim = true;
			tmp->data->t1 = clock();
			Client* aux = App->client->getClient(tmp->data->position);
			tmp->data->shitCount -= aux->shitRest;
			tmp->data->paperCount -= aux->shitRest;
			break;
		}

		//Colision para arreglar papel
		if (aux == c1 && c2->type == COLLIDER_PLAYER   && App->player->paper == true && tmp->data->paperCount > 10)
		{
			tmp->data->outOfPaperFlagAnim = false;
			break;
		}

		//Colision para arreglar atasco
		if (aux == c1 && c2->type == COLLIDER_PLAYER && App->player->plunger == true && tmp->data->shitCount > 15)
		{
			tmp->data->cloggedFlagAnim = false;
			break;
		}
		tmp = tmp->next;
	}

	
}

void ModuleBathroom::AddBathroom(const Bath& bathroom, int x, int y, COLLIDER_TYPE collider_type)
{
	Bath* p = new Bath(bathroom);
	p->position.x = x;
	p->position.y = y;
	
	int scale = 4;

	if (collider_type != COLLIDER_NONE)
	{
		p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 22 * scale, 24 * scale }, collider_type, this);
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
