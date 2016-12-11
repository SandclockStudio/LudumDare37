#include "Globals.h"
#include "Application.h"
#include "ModuleClient.h"

ModuleClient::ModuleClient(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{
}

ModuleClient::~ModuleClient()
{}

// Load assets
bool ModuleClient::Start()
{
	LOG("Loading Clients");
	graphics = App->textures->Load("rtype/ship.png");
	// idle animation normal client

	normal.idle.frames.PushBack({ 66, 1, 32, 14 });
	normal.current_animation = &normal.idle;

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

		if (c->Update() == false)
		{
			active.del(tmp);
			delete c;
		}
		else if (SDL_GetTicks() >= c->born)
		{
			AssignBaths(c);
			App->renderer->Blit(graphics, c->position.x, c->position.y, &(normal.current_animation->GetCurrentFrame()));

			if (c->fx_played == false)
			{
				c->fx_played = true;
				App->audio->PlayFx(c->fx);
			}
		}

		if (tmp->data->pooped && tmp->data->handCleaned && tmp->data->position.x > SCREEN_WIDTH && tmp->data->position.y > SCREEN_HEIGHT)
		{
			delete tmp->data;
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
		if (aux == c1 && (c2->type == COLLIDER_PLAYER || c2->type == COLLIDER_WALL || c2->type == COLLIDER_SILK))
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

		//Colision cliente y pila.
		if (aux == c1 && c2->type == COLLIDER_SILK && tmp->data->cleanRequest == true)
		{
			tmp->data->cleanRequest = false;
			break;
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
		p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 32, 14 }, collider_type, this);
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

	t1 = 0;
	t2 = 0;

	
}


bool Client::Update()
{


	if (collider != NULL)
	{

		SDL_Rect r = current_animation->PeekCurrentFrame();
		collider->rect = { position.x, position.y, r.w, r.h };

	}


	//Posicion de ejemplo

	p2Point<int> target = SearchBath();

	p2Point<int> exit;
	exit.x = 600;
	exit.y = 150;

	p2Point<int> temp = target;
	temp -= position;

	// Si hemos llegado al baño(nuestro objetivo) , hacemos caca
	if (temp.IsZero() && ocuppied == true || ocuppied == true && pooping == true)
	{

		position = assignedBath->getCenter();
		if (t1 == 0)
		{
			pooping = true;
			t1 = SDL_GetPerformanceCounter();
		}
			

		Poop();
	}

	// si no hemos hecho caca, y tenemos baño asignado, estamos buscando nuestro baño
	if (pooped == false && ocuppied == true && pooping == false)
	{
		position += GoToPosition(target);

	}

	// si hemos hecho caca, nos dirijimos a la salida
	if (pooped == true && pooping == false)
	{
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

void Client::WaitForBath()
{

	LOG("Waiting for the bath");

	waiting = true;
	complainMeter += 1;
	//Sleep?
	//Sleep(4000);
	//Cambiar animacion a quejarse;


	//TODO comprobar que el medidor sea 2 o 3 y si es asi, hacer caca o POOP en el suelo.
	if (complainMeter == 2)
	{
		Poop();
	}


	waiting = false;

}

void ModuleClient::AssignBaths(Client* c)
{

	LOG("Assigning baths");
//Si no tiene baño asignado y comprobamos que no este esperando quejandose
if (c->ocuppied == false && c->waiting == false)
{
	// TODO FALLO en la lista, no la coge bien
	p2List_item<Bath*>* tmp = App->bathrooms->active.getFirst();
	p2List_item<Bath*>* tmp_next = App->bathrooms->active.getFirst();

	while (tmp != NULL)
	{
		//Cogemos el siguiente baño
		Bath* b = tmp->data;
		tmp_next = tmp->next;

		LOG("Checking bath");

		//asignamos el  baño si no esta asignado
		if (b->busy == false)
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
		c->WaitForBath();

	}

	//Si se ha podido asignar un baño al cliente: COSAS NAZIS
	if (c->ocuppied == true)
	{
		//c ocupado hasta el final
		//c->SearchBath();
	}

}
}

void Client::Poop()
{
	this->t2 = SDL_GetPerformanceCounter();

	LOG("Pooping");

	//TODO AÑADIR ANIMACION CAGAR


	Uint64 time = (double)((t2 - t1) * 1000 / SDL_GetPerformanceFrequency());

	if (time >= 6000) 
	{

		//TODO ANIMACION SALIR BAÑO
		pooped = true;
		position = assignedBath->position;
		//TODO cambiar posicion 
		position.y -= 20;

		ocuppied = false;
		assignedBath->busy = false;
		assignedBath = NULL;
		t1 = -1;
		t2 = 0;
		pooping = false;

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

		if (c->Update() == false)
		{
			active.del(tmp);
			delete c;
		}
		
		if (abs(c->position.x - pos.x)<=3 && abs(c->position.y- pos.y)<=3)
		{
			return c;
		}
			

		tmp = tmp_next;
	}
	return NULL;

}


