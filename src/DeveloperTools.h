#ifndef DEV_TOOLS
	#define DEV_TOOLS

#include <SDL.h>

class DeveloperTools
{
	public:
		DeveloperTools();
		DeveloperTools(bool active);

		void HandleInput(bool &termination, SDL_Event e, SDL_Keycode k);
		bool GetActive();

	private:
		bool active = false;
};

#endif