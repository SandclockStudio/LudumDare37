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

	int w = 48, h = 64;

	idle.frames.PushBack({ 8 + h, 0, w, h});
	idle.frames.PushBack({ 8 + h * 3, 0, w, h });
	idle.speed = 0.03;

	towel.frames.PushBack({ 8, 6 * h, w, h });
	towel.loop = false;
	towel.speed = 0.1f;

	//Unclogging
	unclogging.frames.PushBack({ 8, h * 6,		w,h});
	unclogging.frames.PushBack({ 8 + h, 6 * h,	w,h });
	towel.loop = true;
	towel.speed = 0.1f;

	// move upwards - OK
	up.frames.PushBack({ 8,			h * 2,		w, h});
	up.frames.PushBack({ 8 + h,		h * 2,		w, h });
	up.frames.PushBack({ 8,			h * 2,		w, h });
	up.frames.PushBack({ 8 + h * 2, h * 2,		w, h });

	up.loop = true;
	up.speed = 0.3f;
	
	// Move down - OK
	down.frames.PushBack({ 8,			h,		w, h });
	down.frames.PushBack({ 8 + h,		h,		w, h });
	down.frames.PushBack({ 8,			h,		w, h });
	down.frames.PushBack({ 8 + h * 2,	h,		w, h });

	down.loop = true;
	down.speed = 0.3f;

	// move left
	
	left.frames.PushBack({ 8 + h * 2, h * 5,		w, h });
	left.frames.PushBack({ 8 + h * 3, h * 5,		w, h });
	left.frames.PushBack({ 8 + h * 4, h * 5,		w, h });
	left.frames.PushBack({ 8 + h * 2, h * 6,		w, h });
	left.frames.PushBack({ 8 + h * 3, h * 6,		w, h });
	left.frames.PushBack({ 8 + h * 4, h * 6,		w, h });
	
	left.loop = true;
	left.speed = 0.3f;


	// move right
	right.frames.PushBack({ 8 + h * 0, h * 3,		w, h });
	right.frames.PushBack({ 8 + h * 1, h * 3,		w, h });
	right.frames.PushBack({ 8 + h * 2, h * 3,		w, h });
	right.frames.PushBack({ 8 + h * 0, h * 4,		w, h });
	right.frames.PushBack({ 8 + h * 1, h * 4,		w, h });
	right.frames.PushBack({ 8 + h * 2, h * 4,		w, h });
	right.loop = true;
	right.speed = 0.3f;


	// move up with plunger
	upPlunger.frames.PushBack({ 8 + h * 3, h * 2, w, h });
	upPlunger.frames.PushBack({ 8 + h * 4, h * 2, w, h });
	upPlunger.frames.PushBack({ 8 + h * 3, h * 2, w, h });
	upPlunger.frames.PushBack({ 8 + h * 5, h * 2, w, h });
	upPlunger.loop = true;
	upPlunger.speed = 0.1f;


	// move down with plunger
	downPlunger.frames.PushBack({ 8 + h * 3, h * 1, w, h });
	downPlunger.frames.PushBack({ 8 + h * 4, h * 1, w, h });
	downPlunger.frames.PushBack({ 8 + h * 3, h * 1, w, h });
	downPlunger.frames.PushBack({ 8 + h * 5, h * 1, w, h });
	downPlunger.loop = true;
	downPlunger.speed = 0.1f;

	// move left with plunger
	leftPlunger.frames.PushBack({ 0, 0, w, h });
	leftPlunger.loop = true;
	leftPlunger.speed = 0.1f;

	// move right with plunger
	rightPlunger.frames.PushBack({ 0, 0, w, h });
	rightPlunger.loop = true;
	rightPlunger.speed = 0.1f;

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("ld37/spritesheet-maincharacter.png");

	position.x = 150;
	position.y = 120;
	collider = App->collision->AddCollider({position.x+20, position.y+25, 25, 40}, COLLIDER_PLAYER, this);
	giveTowel = false;
	exploding = false;
	collision = false;
	plunger = false;
	paper = false;
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

		if (current_animation != &left && collision == false && giveTowel == false)
		{
			left.Reset();
			leftPlunger.Reset();
		}

		if (plunger) current_animation = &leftPlunger;
		else 
			current_animation = &left;
		
	}

	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && collision == false && giveTowel == false)
	{
		position.x += speed;

		if (current_animation != &right && collision == false && giveTowel == false)
		{
			rightPlunger.Reset();
			right.Reset();
		}
		
		if (plunger) 
			current_animation = &rightPlunger;
		else
			current_animation = &right;

	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && collision == false && giveTowel == false)
	{
		position.y += speed;
		if(current_animation != &down  && collision == false && giveTowel == false)
		{
			down.Reset();
			downPlunger.Reset();
		}

		if (plunger) current_animation = &downPlunger;
		else current_animation = &down;
	}

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && collision == false && giveTowel == false)
	{
		position.y -= speed;
		if(current_animation != &up && collision == false && giveTowel == false)
		{
			up.Reset();
			upPlunger.Reset();
		}

		if (plunger) current_animation = &upPlunger;
		else current_animation = &up;
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE && collision == false && giveTowel == false)
		current_animation = &idle;

	collider->SetPos(position.x + 10, position.y + 25);

	// Draw everything --------------------------------------

	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

// Collision detection
void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	collision = true;
	//izquierda
	if ((c1->rect.x < c2->rect.x + c2->rect.w) && ((c2->rect.x + c2->rect.w) - c1->rect.x) < c1->rect.w && ((c2->rect.y + c2->rect.h) - c1->rect.y) >4 && (c2->rect.y - (c1->rect.h + c1->rect.y)) <-4)
	{
		position.x += ( (c2->rect.x + c2->rect.w)- c1->rect.x );
		collision = false;
	}
	else
	{
		//derecha
		if (c1->rect.x + c1->rect.w > c2->rect.x && ((c2->rect.y + c2->rect.h) - c1->rect.y) >4 && (c2->rect.y - (c1->rect.h + c1->rect.y)) <-4)
		{
			position.x += (c2->rect.x - (c1->rect.x + c1->rect.w) );
			collision = false;
		}
		else
		{
			//abajo
			if( (c1->rect.y < c2->rect.y + c2->rect.h) && ( (c1->rect.h + c1->rect.y)-c2->rect.y) > c1->rect.h)
			{
				position.y += ((c2->rect.y + c2->rect.h) - c1->rect.y) ;
				collision = false;
			}
			else
			{
				//arriba
				if (c1->rect.h + c1->rect.y > c2->rect.y)
				{
					position.y += (c2->rect.y-(c1->rect.h + c1->rect.y)) ;
					collision = false;
				}
			}
		}
	}
}
