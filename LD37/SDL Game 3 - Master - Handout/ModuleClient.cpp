#include "Globals.h"
#include "Application.h"
#include "ModuleClient.h"
#include "ModulePoints.h"

ModuleClient::ModuleClient(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{
}

ModuleClient::~ModuleClient()
{}

// Load assets
bool ModuleClient::Start()
{
	
	LOG("Loading Clients");
	graphics = App->textures->Load("ld37/spritesheet-npc-1.png");
	
	// Animacion normal idle
	int w = 48, h = 64;
	float walkAnimSpeed = 0.3f;

	normal.idle.frames.PushBack({ 8, 0, w, h });
	normal.idle.frames.PushBack({ 8 + h * 3, 0, w, h });
	normal.idle.speed = 0.02f;
	normal.idle.loop = true;

	//Animacion normal cagar
	normal.poopingAnim.frames.PushBack({ 8, h * 8, w, h });
	normal.poopingAnim.frames.PushBack({ 8 + h, h * 8, w, h });
	normal.poopingAnim.speed = 0.02f;
	normal.poopingAnim.loop = true;

	//Animacion normal izquierda
	normal.walking_left.frames.PushBack({ 8,	h * 5, w, h });
	normal.walking_left.frames.PushBack({ 8 + h, h * 5, w, h });
	normal.walking_left.frames.PushBack({ 8,	h * 5, w, h });
	normal.walking_left.frames.PushBack({ 8 + h * 2, h * 5, w, h });
	normal.walking_left.speed = walkAnimSpeed;
	normal.walking_left.loop = true;

	//Animacion normal derecha
	normal.walking_right.frames.PushBack({ 8, h * 4, w, h });
	normal.walking_right.frames.PushBack({ 8 + h, h * 4, w, h });
	normal.walking_right.frames.PushBack({ 8, h * 4, w, h });
	normal.walking_right.frames.PushBack({ 8 + h * 2, h * 4, w, h });
	normal.walking_right.speed = walkAnimSpeed;
	normal.walking_right.loop = true;

	//Animacion normal arriba
	normal.walking_up.frames.PushBack({ 8, h * 3, w, h });
	normal.walking_up.frames.PushBack({ 8 + h, h * 3, w, h });
	normal.walking_up.frames.PushBack({ 8, h * 3, w, h });
	normal.walking_up.frames.PushBack({ 8 + h * 2, h * 3, w, h });
	normal.walking_up.speed = walkAnimSpeed;
	normal.walking_up.loop = true;

	//Animacion normal abajo
	normal.walking_down.frames.PushBack({ 8, h * 2, w, h });
	normal.walking_down.frames.PushBack({ 8 + h, h * 2, w, h });
	normal.walking_down.frames.PushBack({ 8, h * 2, w, h });
	normal.walking_down.frames.PushBack({ 8 + h * 2, h * 2, w, h });
	normal.walking_down.speed = walkAnimSpeed;
	normal.walking_down.loop = true;


	//Animacion fat idle
	//Animacion fat cagar
	//Animacion fat izquierda
	//Animacion fat derecha
	//Animacion fat arriba
	//Animacion fat abajo

	normal.assignedBath = new Bath();
	normal.current_animation = &normal.walking_left;


	normal.shitRest = 5;
	normal.paperRest = 1;

	fat.shitRest = 4;
	fat.paperRest = 2;
	return true;
}

// Unload assets
bool ModuleClient::CleanUp()
{
	LOG("Unloading clients");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleClient::Update() 
{
	p2List_item<Client*>* tmp = active.getFirst();
	p2List_item<Client*>* tmp_next = active.getFirst();
	while (tmp != NULL)
	{
		Client* c = tmp->data;
		tmp_next = tmp->next;
		App->point->points += tmp->data->pointClient;
		tmp->data->pointClient = 0;
		if (c->Update() == false)
		{
			active.del(tmp);
			delete c;
		}
		else if (SDL_GetTicks() >= c->born)
		{
			AssignBaths(c);
			//AssignSilks(c);

			if (c->pooping)	{
				c->current_animation = &c->poopingAnim;
			}
			else if (c->waiting) {
				c->current_animation = &c->idle;
			}
			else {
				
				if (abs(c->targetPosition.x) < abs(c->targetPosition.y)) {
					if (c->targetPosition.y > 0)
						c->current_animation = &c->walking_down;
					else
						c->current_animation = &c->walking_up;
				}
				else {
		
					if (c->targetPosition.x > 0)
						c->current_animation = &c->walking_right;
					else
						c->current_animation = &c->walking_left;
				}
			}
			App->renderer->Blit(graphics, c->position.x, c->position.y, &(c->current_animation->GetCurrentFrame()));

		
			if (c->fx_played == false)
			{
				c->fx_played = true;
				App->audio->PlayFx(c->fx);
			}
		}

		
		if (tmp->data->pooped && tmp->data->position.x >= SCREEN_WIDTH-20 )
		{
			//tmp->data->collider->type = COLLIDER_NONE;
			//delete tmp->data;
			active.del(tmp);

			break;
		}
		
		tmp = tmp_next;

	}

	return UPDATE_CONTINUE;
}

// Collision detection
void ModuleClient::OnCollision(Collider* c1, Collider* c2)
{
	p2List_item<Client*>* tmp = active.getFirst();


	while (tmp != NULL)
	{


		Collider* aux = tmp->data->collider;

		//Colision player cliente.
		if (aux == c1 && (c2->type == COLLIDER_PLAYER || c2->type == COLLIDER_WALL || c2->type == COLLIDER_SILK || c2->type == COLLIDER_CLIENT))
		{
			if ((c1->rect.x < c2->rect.x + c2->rect.w) && ((c2->rect.x + c2->rect.w) - c1->rect.x) < c1->rect.w && ((c2->rect.y + c2->rect.h) - c1->rect.y) >4 && (c2->rect.y - (c1->rect.h + c1->rect.y)) <-4)
			{
				tmp->data->position.x += ((c2->rect.x + c2->rect.w) - c1->rect.x);

			}
			else
			{
				//derecha
				if (c1->rect.x + c1->rect.w > c2->rect.x && ((c2->rect.y + c2->rect.h) - c1->rect.y) >4 && (c2->rect.y - (c1->rect.h + c1->rect.y)) <-4)
				{
					tmp->data->position.x += (c2->rect.x - (c1->rect.x + c1->rect.w));

				}
				else
				{
					//abajo
					if ((c1->rect.y < c2->rect.y + c2->rect.h) && ((c1->rect.h + c1->rect.y) - c2->rect.y) > c1->rect.h)
					{
						tmp->data->position.y += ((c2->rect.y + c2->rect.h) - c1->rect.y);

					}
					else
					{
						//arriba
						if (c1->rect.h + c1->rect.y > c2->rect.y)
						{
							tmp->data->position.y += (c2->rect.y - (c1->rect.h + c1->rect.y));

						}
					}
				}
			}
			
		}

		
	
		tmp = tmp->next;
	}
	

	

}
void ModuleClient::AddClient(const Client& client, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Client* p = new Client(client);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;
	

	if (collider_type != COLLIDER_NONE)
	{
		p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 48, 48 }, collider_type, this);
	}

	active.add(p);
}

Client::Client() : collider(NULL)
{
	waiting = false;
	ocuppied = false;
	complainMeter = 0;
	pooped = false;
	cleanRequest = false;
	handCleaned = false;
	exiting = false;
	pooping = false;
}

Client::Client(const Client & c) : collider(c.collider)
{

	fx = c.fx;
	born = c.born;
	life = c.life;
	timeBath = c.timeBath;
	timeWaiting = c.timeWaiting;
	timeSink = c.timeSink;
	current_animation = c.current_animation;
	waiting = c.waiting;
	ocuppied = c.ocuppied;
	complainMeter = c.complainMeter;
	pooped = c.pooped;
	cleanRequest = c.cleanRequest;
	handCleaned = c.cleanRequest;
	exiting = c.exiting;
	poopingAnim = c.poopingAnim;
	idle = c.idle;
	walking_down = c.walking_down;
	walking_up = c.walking_up;
	walking_left = c.walking_left;
	walking_right = c.walking_right;
	shitRest = c.shitRest;
	paperRest = c.paperRest;
	assignedBath = c.assignedBath;
	t1 = 0;
	t2 = 0;

	
}


bool Client::Update()
{


	if (collider != NULL)
	{

		SDL_Rect r = current_animation->PeekCurrentFrame();
		collider->rect = { position.x, position.y+25, r.w, r.h-25 };

	}
	else
	{
		SDL_Rect r = current_animation->PeekCurrentFrame();
		collider->rect = { 1000, position.y, r.w, r.h };
	}

	//Posicion de ejemplo
	p2Point<int> bath = SearchBath();
	p2Point<int> silk = SearchSilk();
	p2Point<int> door = p2Point<int>();
	door.x = SCREEN_WIDTH;
	door.y = 125;

	//silk.y += 10;

	p2Point<int> target;
	if (pooped == true)
		target = door;
	else
		target = bath;

	p2Point<int> exit;
	exit.x = SCREEN_WIDTH;
	exit.y = SCREEN_HEIGHT/2-125;

	p2Point<int> temp = target;
	temp -= position;

	targetPosition = temp;


	// Si hemos llegado al baño(nuestro objetivo) , hacemos caca
	if (temp.IsZero() && ocuppied == true && pooped == false || ocuppied == true && pooping == true)
	{

		position = assignedBath->getCenter();
		position.y -=23;
		position.x -=24 ;
		


		if (t1 == 0)
		{
			pooping = true;
			t1 = SDL_GetPerformanceCounter();
		}
			

		Poop();
	}


	// Si hemos llegado al silk(nuestro objetivo) , nos lavamos las manos
	if (temp.IsZero() && pooped == true && handCleaned == false)
	{

		if (t1 == 0)
		{
			washingHands = true;
			t1 = SDL_GetPerformanceCounter();
		}


		WashHands();
	}

	// si no hemos hecho caca, y tenemos baño asignado, estamos buscando nuestro baño
	if (pooped == false && ocuppied == true && pooping == false)
	{
		position += GoToPosition(bath);

	}

	//hemos hecho caca, tengo request de lavarme las manos, no me las he lavado -> vamos a lavarnos las manos
	/*
	if (pooped == true && cleanRequest == true && washingHands == false)
	{
		LOG("going to silk ");
		position += GoToPosition(silk);
	}
	*/

	// si hemos hecho caca y nos hemos lavado las manos nos dirijimos a la salida
	if (pooped == true && pooping == false)
	{
		LOG("going to exit ");

		if (exiting == false)
		{
			if (position.y < 200)
				position.y += 1;
			else exiting = true;
		}
		
		position += GoToPosition(exit);

	}


	return true;


}

p2Point<int> Client::GoToPosition(p2Point<int> target)
{


	float max_speed = 1.0f;

	int length = position.Length();

	int distance = position.DistanceTo(target);

	p2Point<int> vec = p2Point<int>(target);
	vec -= position;

	//normalizar y escalar
	p2Point<int> velocity =  vec.Normalize().Scale(max_speed);


	return velocity;
}



p2Point<int> Client::SearchBath()
{
	//Si tenemos un baño asignado
	if (ocuppied == true)
	{
		return assignedBath->position;
	}
	return  position; // sino devolver mi position

}

p2Point<int> Client::SearchSilk()
{
	//Si tenemos un baño asignado
	if (cleanRequest == true)
	{
		p2Point<int> temp = assignedSilk->position;
		temp.y -= 50;
		//temp.y += 10;
		//temp.x += 40;
		return temp;
	}
	return  position; // sino devolver mi position

}


void Client::WaitForBath()
{

	this->t2 = SDL_GetPerformanceCounter();

	LOG("Waiting for the bath");



	Uint64 time = (double)((t2 - t1) * 1000 / SDL_GetPerformanceFrequency());

	if (time > 4000)
	{

		waiting = false;
		complainMeter += 1;

	}
	else waiting = true;

}

void Client::WaitForSilk()
{


	this->t2 = SDL_GetPerformanceCounter();

	LOG("Waiting for Silk");

	//TODO AÑADIR ANIMACION CAGAR


	Uint64 time = (double)((t2 - t1) * 1000 / SDL_GetPerformanceFrequency());

	if (time > 4000)
	{
		waiting = false;
		complainMeter += 1;
	}
	else waiting = true;

}

void ModuleClient::AssignBaths(Client* c)
{

	//Si no tiene baño asignado y comprobamos que no este esperando quejandose
	if (c->ocuppied == false && c->waiting == false && c->pooped == false)
	{

		p2List_item<Bath*>* tmp = App->bathrooms->active.getFirst();
		p2List_item<Bath*>* tmp_next = App->bathrooms->active.getFirst();

		while (tmp != NULL)
		{
			//Cogemos el siguiente baño
			Bath* b = tmp->data;
			tmp_next = tmp->next;

			LOG("Checking bath");

			//asignamos el  baño si no esta asignado
			if (b->busy == false && c->pooped == false)
			{
				LOG("Bath assigned");
				c->assignedBath = b;
				c->ocuppied = true;
				b->busy = true;
				break;
			}

			tmp = tmp_next;

		}

		//si no se ha podido asignar ningun baño al cliente: Esperar y quejarse
		if ((tmp == NULL) && (c->ocuppied == false))
		{
			// HACER QUE ESPERE EL CLIENTE: sleep(4000) for eixample
			if(c->waiting == false)
				c->t1 = SDL_GetPerformanceCounter();
			c->WaitForBath();

		}

	}
}


void ModuleClient::AssignSilks(Client* c)
{

	//Si no tiene baño asignado y comprobamos que no este esperando quejandose
	if (c->cleanRequest == false && c->pooped == true && c->handCleaned == false && c->washingHands == false)
	//if (c->cleanRequest == false && c->pooped == true && c->handCleaned == false)
	{
		
		p2List_item<Silk*>* tmp = App->silks->active.getFirst();
		p2List_item<Silk*>* tmp_next = App->silks->active.getFirst();

		while (tmp != NULL)
		{
			//Cogemos el siguiente baño
			Silk* s = tmp->data;
			tmp_next = tmp->next;

			LOG("Checking silk");

			//asignamos el  baño si no esta asignado
			if (s->busy == false && c->waiting == false)
			{
				LOG("Silk assigned");
				c->assignedSilk = s;
				c->cleanRequest = true;
				s->busy = true;
				break;
			}

			tmp = tmp_next;

		}

		//si no se ha podido asignar ningun silk al cliente: Esperar y quejarse
		if ((tmp == NULL) && (c->ocuppied == false))
		{
			// HACER QUE ESPERE EL CLIENTE: sleep(4000) for eixample
			if (c->waiting == false)
				c->t1 = SDL_GetPerformanceCounter();
			c->WaitForSilk();

		}

		/*//Si se ha podido asignar un baño al cliente: COSAS NAZIS
		if (c->ocuppied == true)
		{
			//c ocupado hasta el final
			//c->SearchBath();
		}*/

	}
}
void Client::Poop()
{
	this->t2 = SDL_GetPerformanceCounter();

	LOG("Pooping");

	//TODO AÑADIR ANIMACION CAGAR


	Uint64 time = (double)((t2 - t1) * 1000 / SDL_GetPerformanceFrequency());


	if (time >= 6000 && pooped == false)
	{
		


		if (assignedBath->shitCount <= 0 || (assignedBath->paperCount <= 0))
		{

			if (assignedBath->shitCount <= 0)
			{
				assignedBath->current_animation = &assignedBath->clogged;
				assignedBath->busy = true;
				assignedBath->cloggedFlagAnim = true;
				pooped = true;
				position = assignedBath->position;
				//TODO cambiar posicion 
				position.y -= 70;

				ocuppied = false;
				assignedBath->busy = false;
				//assignedBath = NULL;
				t1 = 0;
				t2 = 0;
				pooping = false;
			}



			if (assignedBath->paperCount <= 0)
			{
				LOG("Sin Papel");
				if (assignedBath->paperRefresh == true)
				{
					//TODO ANIMACION SALIR BAÑO
					pooped = true;
					position = assignedBath->position;
					//TODO cambiar posicion 
					position.y -= 70;
					if (pointClient == 0)
						pointClient += 1;

					ocuppied = false;
					assignedBath->busy = false;
					assignedBath = NULL;
					assignedBath->shitCount -= shitRest;
					assignedBath->paperCount -= paperRest;
					t1 = 0;
					t2 = 0;
					pooping = false;
				}
				else
				{
					//CAMBIAR ANIMACION
					assignedBath->current_animation = &assignedBath->outOfPaper;
					assignedBath->busy = true;
				}

			}

	}
		else
		{

			if (pointClient == 0)
				pointClient += 5;
			//TODO ANIMACION SALIR BAÑO
			pooped = true;
			position = assignedBath->position;
			//TODO cambiar posicion 
			position.y -= 70;

			ocuppied = false;
			assignedBath->shitCount -= shitRest;
			assignedBath->paperCount -= paperRest;
			assignedBath->busy = false;
			//assignedBath = NULL;
			t1 = 0;
			t2 = 0;
			pooping = false;





		}

		





	}

}

void Client::WashHands()
{
	this->t2 = SDL_GetPerformanceCounter();


	Uint64 time = (double)((t2 - t1) * 1000 / SDL_GetPerformanceFrequency());

	if (time >= 4000 && handCleaned == false && pooped == true )
	{
		LOG("Washing Hands");
		//TODO ANIMACION SALIR BAÑO
		//pooped = true;
		//position = assignedBath->position;
		//TODO cambiar posicion 
		//position.y -= 20;



		ocuppied = false;

//		assignedSilk->busy = false;
		
		
		//assignedSilk = NULL;
		t1 = 0;
		t2 = 0;
		washingHands = false;
		handCleaned = true;

	}

}

Client* ModuleClient:: getClient(p2Point<int> pos)
{
	p2List_item<Client*>* tmp = active.getFirst();
	p2List_item<Client*>* tmp_next = active.getFirst();


	while (tmp != NULL)
	{
		Client* c = tmp->data;
		tmp_next = tmp->next;

		if (abs(c->position.x - pos.x)<=30 && abs(c->position.y- pos.y)<=30)
		{
			return c;
		}
			
		tmp = tmp_next;
	}
	return NULL;

}


