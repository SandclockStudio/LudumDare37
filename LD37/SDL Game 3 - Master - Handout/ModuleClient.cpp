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
	current_animation = NULL;
	graphics = App->textures->Load("rtype/ship.png");
	// idle animation normal client
	normal.idle.frames.PushBack({ 66, 1, 32, 14 });

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
	current_animation = &normal.idle;

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
			App->renderer->Blit(graphics, c->position.x, c->position.y, &(current_animation->GetCurrentFrame()));
			if (c->fx_played == false)
			{
				c->fx_played = true;
				App->audio->PlayFx(c->fx);
			}
		}

		tmp = tmp_next;
	}

	return UPDATE_CONTINUE;
}

// Collision detection
void ModuleClient::OnCollision(Collider* c1, Collider* c2)
{
	
}
void ModuleClient::AddClient(const Client& client, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Client* p = new Client(client);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;
	

	if (collider_type != COLLIDER_NONE)
	{
		p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 0, 0 }, collider_type, this);
	}

	active.add(p);
}

Client::Client()
{
	
}

Client::Client(const Client& c) 
{
	fx = c.fx;
	born = c.born;
	life = c.life;
	timeBath = c.timeBath;
	timeWaiting = c.timeWaiting;
	timeSink = c.timeSink;
}


bool Client::Update()
{
	return true;
}
