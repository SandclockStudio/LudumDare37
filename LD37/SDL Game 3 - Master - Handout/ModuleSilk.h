#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "Application.h"

struct Collider;


struct Silk
{
	Animation waterOpen;


	p2Point<int> position;

	unsigned int fx;
	bool fx_played;
	bool busy = false;
	Collider* collider;

	Silk();
	Silk(const Silk& p);

	bool Update();
};

class ModuleSilk : public Module
{
public:
	ModuleSilk(Application* app, bool start_enabled = true);
	~ModuleSilk();
	bool Start();
	update_status Update();
	void OnCollision(Collider * c1, Collider * c2);
	void AddSilk(const Silk & sink, int x, int y, COLLIDER_TYPE collider_type);
	Silk silk;
	Animation* current_animation;
	p2List<Silk*> active;


private:
	SDL_Texture* graphics;
};
