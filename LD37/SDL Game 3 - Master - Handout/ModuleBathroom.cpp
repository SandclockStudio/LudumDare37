#include "Globals.h"
#include "Application.h"
#include "ModuleBathroom.h"
#include "Application.h"

ModuleBathroom::ModuleBathroom(Application * app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleBathroom::~ModuleBathroom()
{
}

bool ModuleBathroom::Start()
{
	LOG("Loading baths");
	graphics = App->textures->Load("ld37/spritesheet-bathroom.png");
	
	//Animacion idle
	bath.idle.frames.PushBack({ 40 * SCALE, 326 * SCALE, 40 * SCALE, 64 * SCALE });
	bath.idle.loop = true;
	bath.idle.speed = 0.3f;

	// Animacion abrir baño
	bath.fx = App->audio->LoadFx("SONIDO-BAÑO-AL-ABRIRSE");
	bath.openDoor.frames.PushBack({ 40 * SCALE, 326 * SCALE, 40 * SCALE, 64 * SCALE });
	bath.openDoor.frames.PushBack({ 80 * SCALE, 326 * SCALE, 40 * SCALE, 64 * SCALE });
	bath.openDoor.frames.PushBack({ 120 * SCALE, 326 * SCALE, 40 * SCALE, 64 * SCALE });
	bath.openDoor.frames.PushBack({ 160 * SCALE, 326 * SCALE, 40 * SCALE, 64 * SCALE });
	bath.openDoor.frames.PushBack({ 40 * SCALE, 326 * SCALE, 40 * SCALE, 64 * SCALE });
	bath.openDoor.loop = false;
	bath.openDoor.speed = 0.1f;

		//icono idle 
	bath.fx = App->audio->LoadFx("SONIDO-BAÑO-AL-ATASCARSE");
	//bath.idle_particle.frames.PushBack({ 0 * SCALE, 200 * SCALE, 40 * SCALE, 64 * SCALE });
	bath.idle_particle.loop = true;
	bath.idle_particle.speed = 0.3f;

	// Animacion baño sin papel
	bath.fx = App->audio->LoadFx("SONIDO-BAÑO-AL-QUEDARSE-SIN-PAPEL");
	bath.outOfPaper.frames.PushBack({ 40 * SCALE, (326 + 64) * SCALE, 40 * SCALE, 64 * SCALE });
	bath.outOfPaper.loop = true;
	bath.outOfPaper.speed = 0.3f;

	bath.openDoorNoPaper.frames.PushBack({ 40 * SCALE, (326 + 64) * SCALE, 40 * SCALE, 64 * SCALE });
	bath.openDoorNoPaper.frames.PushBack({ 80 * SCALE, (326 + 64) * SCALE, 40 * SCALE, 64 * SCALE });
	bath.openDoorNoPaper.frames.PushBack({ 120 * SCALE, (326 + 64) * SCALE, 40 * SCALE, 64 * SCALE });
	bath.openDoorNoPaper.frames.PushBack({ 160 * SCALE, (326 + 64) * SCALE, 40 * SCALE, 64 * SCALE });
	bath.openDoorNoPaper.frames.PushBack({ 40 * SCALE, (326 + 64) * SCALE, 40 * SCALE, 64 * SCALE });
	bath.openDoorNoPaper.loop = false;
	bath.openDoorNoPaper.speed = 0.1f;

	// Animacion baño atascado
	bath.fx = App->audio->LoadFx("SONIDO-BAÑO-AL-ATASCARSE");
	bath.clogged.frames.PushBack({ 0 * SCALE, 200 * SCALE, 40 * SCALE, 64 * SCALE });
	bath.clogged.loop = true;
	bath.clogged.speed = 0.3f;


	


	return true;
}

update_status ModuleBathroom::Update()
{
	p2List_item<Bath*>* tmp = active.getFirst();
	p2List_item<Bath*>* tmp_next = active.getFirst();
	int checkBathColapsing = 0;

	while (tmp != NULL)
	{
		Bath* p = tmp->data;
		tmp_next = tmp->next;

		p->animation_particle = &p->idle_particle;

		if (p->paperCount <=  0)
		{
			p->outOfPaperFlagAnim = true;
			p->busy = true;
			
		}

		if (p->shitCount <= 0)
		{
			p->outOfPaperFlagAnim = true;
			p->busy = true;
		}

		if (p->outOfPaperFlagAnim)
			p->current_animation = &p->outOfPaper;
		else
			p->current_animation = &p->idle;

		

		//Animacion abrir puerta
		if(p->openDoorAnim == true )
		{
			
			if (p->outOfPaperFlagAnim) p->current_animation = &p->openDoorNoPaper;
			else p->current_animation = &p->openDoor;
			
			p->t2 = clock();
			if (difftime(p->t2, p->t1) > 300)
			{
				p->openDoor.Reset();
				p->openDoorNoPaper.Reset();
				p->openDoorAnim = false;
				p->busyFlagAnim = false;
			}

		}


	

		//Animacion atascado
		if (p->cloggedFlagAnim == true)
		{
			p->animation_particle = &p->clogged;
		
		}

		if(SDL_GetTicks() >= p->born)
		{
			App->renderer->Blit(graphics, p->position.x, p->position.y, &(p->current_animation->GetCurrentFrame()));
			App->renderer->Blit(graphics, p->position.x, p->position.y, &(p->animation_particle->GetCurrentFrame()));
		}

		if (p->outOfPaperFlagAnim || p->cloggedFlagAnim)
		{
			checkBathColapsing++;
			
		}

		/*
		if (checkBathColapsing >= 4)
		{
			App->bath_scene->CleanUp();

			App->fade->FadeToBlack(this, App->scene_intro, 0.0f);
			
			
		}
		*/

		tmp = tmp_next;
	}

	return UPDATE_CONTINUE;
}

bool ModuleBathroom::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	return true;
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
			
			tmp->data->t1 = clock();
			Client* aux = App->client->getClient(tmp->data->position);
			if (aux != NULL && tmp->data->openDoorAnim == false)
			{
				tmp->data->shitCount -= aux->shitRest;
				tmp->data->paperCount -= aux->paperRest;
				tmp->data->openDoorAnim = true;
				
			}

			break;
		}
		

		//Colision para arreglar papel
		if (aux == c1 && c2->type == COLLIDER_PLAYER   && App->player->paper == true && tmp->data->paperCount <= 0)
		{
			tmp->data->idle.Reset();
			tmp->data->outOfPaper.Reset();
			tmp->data->paperCount = 15;
			tmp->data->outOfPaperFlagAnim = false;
			tmp->data->busy = false;
			App->player->paper = false;
			tmp->data->paperRefresh = true;
			break;
		}

		//Colision para arreglar atasco
		if (aux == c1 && c2->type == COLLIDER_PLAYER && App->player->plunger == true && tmp->data->shitCount <= 0)
		{
			tmp->data->cloggedFlagAnim = false;
			tmp->data->busy = false;
			tmp->data->shitCount = 10;
			break;
		}
		tmp = tmp->next;
	}

}

void ModuleBathroom::AddBathroom(const Bath& bathroom, int x, int y, COLLIDER_TYPE collider_type)
{
	Bath* p = new Bath(bathroom);
	p->born = SDL_GetTicks();
	p->position.x = x;
	p->position.y = y;

	if (collider_type != COLLIDER_NONE)
	{
		p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 40 * SCALE, 64 * SCALE }, collider_type, this);
	}

	active.add(p);
}


p2Point<int> Bath::getCenter()
{
	p2Point<int> center;

	center.x = position.x + ((40 * SCALE) / 2);
	center.y = position.y + ((64 * SCALE) / 2);

	return center;
}

Bath::Bath()
{
	shitCount = 15;
	paperCount = 2;
	fx_played = false;
	busy = false;
	openDoorAnim = false;
	busyFlagAnim = false;
	outOfPaperFlagAnim = false;
	cloggedFlagAnim = false;
}

Bath::Bath(const Bath & p)
{
	shitCount = 15;
	paperCount = 2;

	openDoor = p.openDoor;
	busyAnim = p.busyAnim;
	outOfPaper = p.outOfPaper;
	clogged = p.clogged;
	idle = p.idle;
	idle_particle = p.idle_particle;
	openDoorNoPaper = p.openDoorNoPaper;

	fx_played = false;
	busy = false;
	openDoorAnim = false;
	//busyFlagAnim = false;
	outOfPaperFlagAnim = false;
	cloggedFlagAnim = false;

	//outOfPaperFlagAnim = false;
}



bool Bath::Update()
{
	return false;
}
