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
	float walkAnimSpeed = 0.3;
	float idleAnimSpeed = 0.01;

	idle.frames.PushBack({ 8 + h, 0, w, h});
	idle.frames.PushBack({ 8 + h * 3, 0, w, h });
	idle.loop = true;
	idle.speed = idleAnimSpeed;

	idlePlunger.frames.PushBack({ 8 + h * 5, 0, w, h });
	idlePlunger.frames.PushBack({ 8 + h * 7, 0, w, h });
	idlePlunger.loop = true;
	idlePlunger.speed = idleAnimSpeed;

	idlePaper.frames.PushBack({ 8 + h, h * 7, w, h });
	idlePaper.frames.PushBack({ 8 + h * 3, h * 7, w, h });
	idlePaper.loop = true;
	idlePaper.speed = idleAnimSpeed;

	towel.frames.PushBack({ 8, h * 5, w, h });
	towel.frames.PushBack({ 8 + h, h * 5, w, h });
	towel.loop = false;
	towel.speed = 0.1f;

	//Unclogging
	unclogging.frames.PushBack({ 8, h * 6,		w,h});
	unclogging.frames.PushBack({ 8 + h, 6 * h,	w,h });
	unclogging.loop = true;
	unclogging.speed = 0.3f;

	// move upwards - OK
	up.frames.PushBack({ 8,			h * 2,		w, h});
	up.frames.PushBack({ 8 + h,		h * 2,		w, h });
	up.frames.PushBack({ 8,			h * 2,		w, h });
	up.frames.PushBack({ 8 + h * 2, h * 2,		w, h });
	up.loop = true;
	up.speed = walkAnimSpeed;
	
	// Move down - OK
	down.frames.PushBack({ 8,			h,		w, h });
	down.frames.PushBack({ 8 + h,		h,		w, h });
	down.frames.PushBack({ 8,			h,		w, h });
	down.frames.PushBack({ 8 + h * 2,	h,		w, h });
	down.loop = true;
	down.speed = walkAnimSpeed;

	// move left
	left.frames.PushBack({ 8 + h * 7, h * 5,		w, h });
	left.frames.PushBack({ 8 + h * 6, h * 5,		w, h });
	left.frames.PushBack({ 8 + h * 5, h * 5,		w, h });
	left.frames.PushBack({ 8 + h * 7, h * 6,		w, h });
	left.frames.PushBack({ 8 + h * 6, h * 6,		w, h });
	left.frames.PushBack({ 8 + h * 5, h * 6,		w, h });
	left.loop = true;
	left.speed = walkAnimSpeed;


	// move right
	right.frames.PushBack({ 8 + h * 0, h * 3,		w, h });
	right.frames.PushBack({ 8 + h * 1, h * 3,		w, h });
	right.frames.PushBack({ 8 + h * 2, h * 3,		w, h });
	right.frames.PushBack({ 8 + h * 0, h * 4,		w, h });
	right.frames.PushBack({ 8 + h * 1, h * 4,		w, h });
	right.frames.PushBack({ 8 + h * 2, h * 4,		w, h });
	right.loop = true;
	right.speed = walkAnimSpeed;


	// move up with plunger
	upPlunger.frames.PushBack({ 8 + h * 3, h * 2, w, h });
	upPlunger.frames.PushBack({ 8 + h * 4, h * 2, w, h });
	upPlunger.frames.PushBack({ 8 + h * 3, h * 2, w, h });
	upPlunger.frames.PushBack({ 8 + h * 5, h * 2, w, h });
	upPlunger.loop = true;
	upPlunger.speed = walkAnimSpeed;


	// move down with plunger
	downPlunger.frames.PushBack({ 8 + h * 3, h * 1, w, h });
	downPlunger.frames.PushBack({ 8 + h * 4, h * 1, w, h });
	downPlunger.frames.PushBack({ 8 + h * 3, h * 1, w, h });
	downPlunger.frames.PushBack({ 8 + h * 5, h * 1, w, h });
	downPlunger.loop = true;
	downPlunger.speed = walkAnimSpeed;

	// move left with plunger
	leftPlunger.frames.PushBack({ 8 + h * 4, h * 5, w, h });
	leftPlunger.frames.PushBack({ 8 + h * 3, h * 5, w, h });
	leftPlunger.frames.PushBack({ 8 + h * 2, h * 5, w, h });
	leftPlunger.frames.PushBack({ 8 + h * 4, h * 6, w, h });
	leftPlunger.frames.PushBack({ 8 + h * 3, h * 6, w, h });
	leftPlunger.frames.PushBack({ 8 + h * 2, h * 6, w, h });
	leftPlunger.loop = true;
	leftPlunger.speed = walkAnimSpeed;

	// move right with plunger
	rightPlunger.frames.PushBack({ 8 + h * 3, 3 * h, w, h });
	rightPlunger.frames.PushBack({ 8 + h * 4, 3 * h, w, h });
	rightPlunger.frames.PushBack({ 8 + h * 5, 3 * h, w, h });
	rightPlunger.frames.PushBack({ 8 + h * 3, 4 * h, w, h });
	rightPlunger.frames.PushBack({ 8 + h * 4, 4 * h, w, h });
	rightPlunger.frames.PushBack({ 8 + h * 5, 4 * h, w, h });
	rightPlunger.loop = true;
	rightPlunger.speed = walkAnimSpeed;


	// move up with paper
	upPaper.frames.PushBack({ 8 + h * 0, h * 9, w, h });
	upPaper.frames.PushBack({ 8 + h * 1, h * 9, w, h });
	upPaper.frames.PushBack({ 8 + h * 0, h * 9, w, h });
	upPaper.frames.PushBack({ 8 + h * 2, h * 9, w, h });
	upPaper.loop = true;
	upPaper.speed = walkAnimSpeed;


	// move down with paper
	downPaper.frames.PushBack({ 8 + h * 0, h * 8, w, h });
	downPaper.frames.PushBack({ 8 + h * 1, h * 8, w, h });
	downPaper.frames.PushBack({ 8 + h * 0, h * 8, w, h });
	downPaper.frames.PushBack({ 8 + h * 2, h * 8, w, h });
	downPaper.loop = true;
	downPaper.speed = walkAnimSpeed;

	// move left with paper
	leftPaper.frames.PushBack({ 8 + h * 7, h * 12, w, h });
	leftPaper.frames.PushBack({ 8 + h * 6, h * 12, w, h });
	leftPaper.frames.PushBack({ 8 + h * 5, h * 12, w, h });
	leftPaper.frames.PushBack({ 8 + h * 7, h * 13, w, h });
	leftPaper.frames.PushBack({ 8 + h * 6, h * 13, w, h });
	leftPaper.frames.PushBack({ 8 + h * 5, h * 13, w, h });
	leftPaper.loop = true;
	leftPaper.speed = walkAnimSpeed;

	// move right with paper
	rightPaper.frames.PushBack({ 8 + h * 0, 10 * h, w, h });
	rightPaper.frames.PushBack({ 8 + h * 1, 10 * h, w, h });
	rightPaper.frames.PushBack({ 8 + h * 2, 10 * h, w, h });
	rightPaper.frames.PushBack({ 8 + h * 0, 11 * h, w, h });
	rightPaper.frames.PushBack({ 8 + h * 1, 11 * h, w, h });
	rightPaper.frames.PushBack({ 8 + h * 2, 11 * h, w, h });
	rightPaper.loop = true;
	rightPaper.speed = walkAnimSpeed;

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

	if (giveTowel == true) {
		current_animation = &towel;
		if (towel.Finished())
		{
			towel.Reset();
			giveTowel = false;
		}
	}
	if (unclog == true) {

		unclogging.Reset();
		current_animation = &unclogging;
	}

	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && collision == false && giveTowel == false)
	{
		position.x -= speed;

		if (current_animation != &left && current_animation != &leftPlunger && current_animation != &leftPaper && collision == false && giveTowel == false)
		{
			left.Reset();
			leftPaper.Reset();
			leftPlunger.Reset();
		}

		if (plunger) current_animation = &leftPlunger;
		else if (paper) current_animation = &leftPaper;
		else current_animation = &left;
		
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && collision == false && giveTowel == false)
	{
		position.x += speed;

		if (current_animation != &right && current_animation != &rightPlunger && current_animation != &rightPaper && collision == false && giveTowel == false)
		{
			right.Reset();
			rightPaper.Reset();
			rightPlunger.Reset();
		}

		if (plunger) current_animation = &rightPlunger;
		else if (paper) current_animation = &rightPaper;
		else current_animation = &right;

	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && collision == false && giveTowel == false)
	{
		position.y += speed;
		
		if (current_animation != &down && current_animation != &downPlunger && current_animation != &downPaper && collision == false && giveTowel == false)
		{
			down.Reset();
			downPaper.Reset();
			downPlunger.Reset();
		}

		if (plunger) current_animation = &downPlunger;
		else if (paper) current_animation = &downPaper;
		else current_animation = &down;
	}

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && collision == false && giveTowel == false)
	{
		position.y -= speed;
		
		if (current_animation != &up && current_animation != &upPlunger && current_animation != &upPaper && collision == false && giveTowel == false)
		{
			up.Reset();
			upPaper.Reset();
			upPlunger.Reset();
		}

		if (plunger) current_animation = &upPlunger;
		else if (paper) current_animation = &upPaper;
		else current_animation = &up;
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE && collision == false && giveTowel == false) {
		if (plunger) current_animation = &idlePlunger;
		else if (paper) current_animation = &idlePaper;
		else current_animation = &idle;

	}


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
