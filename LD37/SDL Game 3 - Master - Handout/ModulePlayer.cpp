#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	collider = NULL;
	current_animation = NULL;
	exploding = false;

	// idle animation (just the ship)
	idle.frames.PushBack({66, 1, 32, 14});

	
	towel.frames.PushBack({ 100, 1, 32, 14 });
	towel.frames.PushBack({ 132, 0, 32, 14 });
	towel.loop = false;
	towel.speed = 0.1f;

	// move upwards
	up.frames.PushBack({100, 1, 32, 14});
	up.frames.PushBack({132, 0, 32, 14});
	up.loop = false;
	up.speed = 0.1f;
	
	// Move down
	down.frames.PushBack({33, 1, 32, 14});
	down.frames.PushBack({0, 1, 32, 14});
	down.loop = false;
	down.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("rtype/ship.png");

	position.x = 150;
	position.y = 120;
	collider = App->collision->AddCollider({position.x, position.y, 32, 14}, COLLIDER_PLAYER, this);
	giveTowel = false;
	exploding = false;
	collision = false;
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	if(exploding == true)
		return UPDATE_CONTINUE;

	int speed = 3;
	if (giveTowel == true)
	{
		current_animation = &towel;
		if (towel.Finished())
		{
			towel.Reset();
			giveTowel = false;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && collision == false && giveTowel == false)
	{
		position.x -= speed;
	}

	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && collision == false && giveTowel == false)
	{
		position.x += speed;
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && collision == false && giveTowel == false)
	{
		position.y += speed;
		if(current_animation != &down  && collision == false && giveTowel == false)
		{
			down.Reset();
			current_animation = &down;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && collision == false && giveTowel == false)
	{
		position.y -= speed;
		if(current_animation != &up && collision == false && giveTowel == false)
		{
			up.Reset();
			current_animation = &up;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP && collision == false && giveTowel == false)
	{
		App->particles->AddParticle(App->particles->laser, position.x + 28, position.y, COLLIDER_PLAYER_SHOT);
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && collision == false && giveTowel == false)
		current_animation = &idle;

	collider->SetPos(position.x, position.y);

	// Draw everything --------------------------------------

	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

// Collision detection
void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	collision = true;
	if ((c1->rect.x < c2->rect.x + c2->rect.w) && ((c2->rect.x + c2->rect.w) - c1->rect.x) < c1->rect.w && ((c2->rect.y + c2->rect.h) - c1->rect.y) >3 && (c2->rect.y - (c1->rect.h + c1->rect.y)) <-3)
	{
		position.x += ( (c2->rect.x + c2->rect.w)- c1->rect.x )+1;
		collision = false;
	}
	else
	{
		if (c1->rect.x + c1->rect.w > c2->rect.x && ((c2->rect.y + c2->rect.h) - c1->rect.y) > 2 && ((c2->rect.y + c2->rect.h) - c1->rect.y) >3 && (c2->rect.y - (c1->rect.h + c1->rect.y)) <-3)
		{
			position.x += (c2->rect.x - (c1->rect.x + c1->rect.w) ) -1;
			collision = false;
		}
		else
		{
			if( (c1->rect.y < c2->rect.y + c2->rect.h) && ( (c1->rect.h + c1->rect.y)-c2->rect.y) > c1->rect.h)
			{
				position.y += ((c2->rect.y + c2->rect.h) - c1->rect.y) + 1;
				collision = false;
			}
			else
			{
				if (c1->rect.h + c1->rect.y > c2->rect.y)
				{
					position.y += (c2->rect.y-(c1->rect.h + c1->rect.y)) - 1;
					collision = false;
				}
			}
		}
	}
}
