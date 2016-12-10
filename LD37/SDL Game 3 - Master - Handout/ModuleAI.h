#ifndef __ModuleAI_H__
#define __ModuleAI_H__

#include "Module.h"
#include "Globals.h"


class ModuleAI : public Module
{
	public:

		ModuleAI(Application* app, bool start_enabled = true);
		~ModuleAI();

		bool Start();
		update_status Update();
		bool CleanUp();
		void OnCollision(Collider* c1, Collider* c2);


};
#endif // !