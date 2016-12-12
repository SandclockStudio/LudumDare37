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

	float walkingSpeed = 0.2f;

	idle.frames.PushBack({ 8 + h, 0, w, h});
	idle.frames.PushBack({ 8 + h * 3, 0, w, h });
	idle.speed = 0.03;

	// idle when you have paper
	idlePaper.frames.PushBack({8 + h, h * 7, w, h });
	idlePaper.frames.PushBack({ 8 + h * 3, h * 7, w, h });
	idlePaper.speed = 0.03;
	idlePaper.loop = true; 


	// idle when you have plunger
	idlePlunger.frames.PushBack({ 8 + h * 5, h * 7, w, h });
	idlePlunger.frames.PushBack({ 8 + h * 7, h * 7, w, h });
	idlePlunger.speed = 0.03;
	idlePlunger.loop = true;

	towel.frames.PushBack({ 8, 6 * h, w, h });
	towel.loop = false;
	towel.speed = walkingSpeed;

	//Unclogging
	unclogging.frames.PushBack({ 8, h * 6,		w,h});
	unclogging.frames.PushBack({ 8 + h, 6 * h,	w,h });
	unclogging.loop = true;
	unclogging.speed = 0.1f;

	// move upwards - OK
	up.frames.PushBack({ 8,			h * 2,		w, h});
	up.frames.PushBack({ 8 + h,		h * 2,		w, h });
	up.frames.PushBack({ 8,			h * 2,		w, h });
	up.frames.PushBack({ 8 + h * 2, h * 2,		w, h });
	up.loop = true;
<<<<<<< HEAD
	up.speed = walkingSpeed;
=======
	up.speed = 0.3f;
>>>>>>> f44c31a9f1e50b54d4a952345795943884ab5915
	
	// Move down - OK
	down.frames.PushBack({ 8,			h,		w, h });
	down.frames.PushBack({ 8 + h,		h,		w, h });
	down.frames.PushBack({ 8,			h,		w, h });
	down.frames.PushBack({ 8 + h * 2,	h,		w, h });
	down.loop = true;
<<<<<<< HEAD
	down.speed = walkingSpeed;
=======
	down.speed = 0.3f;
>>>>>>> f44c31a9f1e50b54d4a952345795943884ab5915

	// move left
	left.frames.PushBack({ 8 + h * 5, h * 5,		w, h });
	left.frames.PushBack({ 8 + h * 6, h * 5,		w, h });
	left.frames.PushBack({ 8 + h * 7, h * 5,		w, h });
	left.frames.PushBack({ 8 + h * 5, h * 6,		w, h });
	left.frames.PushBack({ 8 + h * 6, h * 6,		w, h });
	left.frames.PushBack({ 8 + h * 7, h * 6,		w, h });
	left.loop = true;
<<<<<<< HEAD
	left.speed = walkingSpeed;
=======
	left.speed = 0.3f;
>>>>>>> f44c31a9f1e50b54d4a952345795943884ab5915


	// move right
	right.frames.PushBack({ 8 + h * 0, h * 3,		w, h });
	right.frames.PushBack({ 8 + h * 1, h * 3,		w, h });
	right.frames.PushBack({ 8 + h * 2, h * 3,		w, h });
	right.frames.PushBack({ 8 + h * 0, h * 4,		w, h });
	right.frames.PushBack({ 8 + h * 1, h * 4,		w, h });
	right.frames.PushBack({ 8 + h * 2, h * 4,		w, h });
	right.loop = true;
<<<<<<< HEAD
	right.speed = walkingSpeed;
=======
	right.speed = 0.3f;
>>>>>>> f44c31a9f1e50b54d4a952345795943884ab5915


	// move up with plunger
	upPlunger.frames.PushBack({ 8 + h * 3, h * 2, w, h });
	upPlunger.frames.PushBack({ 8 + h * 4, h * 2, w, h });
	upPlunger.frames.PushBack({ 8 + h * 3, h * 2, w, h });
	upPlunger.frames.PushBack({ 8 + h * 5, h * 2, w, h });
	upPlunger.loop = true;
	upPlunger.speed = walkingSpeed;


	// move down with plunger
	downPlunger.frames.PushBack({ 8 + h * 3, h * 1, w, h });
	downPlunger.frames.PushBack({ 8 + h * 4, h * 1, w, h });
	downPlunger.frames.PushBack({ 8 + h * 3, h * 1, w, h });
	downPlunger.frames.PushBack({ 8 + h * 5, h * 1, w, h });
	downPlunger.loop = true;
	downPlunger.speed = walkingSpeed;

	// move left with plunger
	leftPlunger.frames.PushBack({ 8 + h * 2, h * 5,		w, h });
	leftPlunger.frames.PushBack({ 8 + h * 3, h * 5,		w, h });
	leftPlunger.frames.PushBack({ 8 + h * 4, h * 5,		w, h });
	leftPlunger.frames.PushBack({ 8 + h * 2, h * 6,		w, h });
	leftPlunger.frames.PushBack({ 8 + h * 3, h * 6,		w, h });
	leftPlunger.frames.PushBack({ 8 + h * 4, h * 6,		w, h });
	leftPlunger.loop = true;
	leftPlunger.speed = walkingSpeed;

	// move right with plunger
	rightPlunger.frames.PushBack({ 8 + h * 3, h * 4,		w, h });
	rightPlunger.frames.PushBack({ 8 + h * 4, h * 4,		w, h });
	rightPlunger.frames.PushBack({ 8 + h * 5, h * 4,		w, h });
	rightPlunger.frames.PushBack({ 8 + h * 3, h * 5,		w, h });
	rightPlunger.frames.PushBack({ 8 + h * 4, h * 5,		w, h });
	rightPlunger.frames.PushBack({ 8 + h * 5, h * 5,		w, h });
	rightPlunger.loop = true;
	rightPlunger.speed = walkingSpeed;

	// move up with paper
	upPaper.frames.PushBack({ 8, h * 9,		w, h });
	upPaper.frames.PushBack({ 8 + h, h * 9,		w, h });
	upPaper.frames.PushBack({ 8, h * 9,		w, h });
	upPaper.frames.PushBack({ 8 + h * 2, h * 9,		w, h });
	upPaper.loop = true; 
	upPaper.speed = walkingSpeed; 

	// move down with paper
	downPaper.frames.PushBack({ 8, h * 8,		w, h });
	downPaper.frames.PushBack({ 8 + h, h * 8,		w, h });
	downPaper.frames.PushBack({ 8, h * 8,		w, h });
	downPaper.frames.PushBack({ 8 + h * 2 , h * 8,		w, h });
	downPaper.loop = true;
	downPaper.speed = walkingSpeed;


	// move left with paper
	leftPaper.frames.PushBack({ 8 + h * 5, h * 12,		w, h });
	leftPaper.frames.PushBack({ 8 + h * 6, h * 12,		w, h });
	leftPaper.frames.PushBack({ 8 + h * 7, h * 12,		w, h });
	leftPaper.frames.PushBack({ 8 + h * 5, h * 13,		w, h });
	leftPaper.frames.PushBack({ 8 + h * 6, h * 13,		w, h });
	leftPaper.frames.PushBack({ 8 + h * 7, h * 13,		w, h });
	leftPaper.loop = true;
	leftPaper.speed = walkingSpeed;


	// move right with paper
	rightPaper.frames.PushBack({ 8 + h * 0, h * 10,		w, h });
	rightPaper.frames.PushBack({ 8 + h * 1, h * 10,		w, h });
	rightPaper.frames.PushBack({ 8 + h * 2, h * 10,		w, h });
	rightPaper.frames.PushBack({ 8 + h * 0, h * 11,		w, h });
	rightPaper.frames.PushBack({ 8 + h * 1, h * 11,		w, h });
	rightPaper.frames.PushBack({ 8 + h * 2, h * 11,		w, h });
	rightPaper.loop = true;
	rightPaper.speed = walkingSpeed;

	// win the game 
	winGame.frames.PushBack({ 8, h * 15,		w, h });
	winGame.frames.PushBack({ 8 + h, h * 15,		w, h });
	winGame.frames.PushBack({ 8 + h * 2, h * 15,		w, h });
	winGame.frames.PushBack({ 8 + h * 3, h * 15,		w, h });
	winGame.loop = false;
	winGame.speed = walkingSpeed;

	// lose the game 
	loseGame.frames.PushBack({ 8, h * 16,		w, h });
	loseGame.frames.PushBack({ 8 + h, h * 16,		w, h });
	loseGame.frames.PushBack({ 8 + h * 2, h * 16,		w, h });
	loseGame.frames.PushBack({ 8 + h * 3, h * 16,		w, h });
	loseGame.frames.PushBack({ 8 + h * 4, h * 16,		w, h });
	loseGame.loop = false;
	loseGame.speed = walkingSpeed;
	
	
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
			leftPaper.Reset();
		}

		if (plunger) current_animation = &leftPlunger;
		else if (paper) current_animation = &leftPaper;
		else 
			current_animation = &left;
		
	}

	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && collision == false && giveTowel == false)
	{
		position.x += speed;

		if (current_animation != &right && collision == false && giveTowel == false)
		{
			right.Reset();
			rightPlunger.Reset();
			rightPaper.Reset();
		}
		
		if (plunger) current_animation = &rightPlunger;
		else if (paper) current_animation = &rightPaper;
		else
			current_animation = &right;

	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && collision == false && giveTowel == false)
	{
		position.y += speed;
		if(current_animation != &down  && collision == false && giveTowel == false)
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
		if(current_animation != &up && collision == false && giveTowel == false)
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
		
		/*
		if (current_animation != &idle  && collision == false && giveTowel == false)
		{
			idle.Reset();
			idlePaper.Reset();
			idlePlunger.Reset();
		}
		*/
		
		//position.y -= speed; 
			
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
