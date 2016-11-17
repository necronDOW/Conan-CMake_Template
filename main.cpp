#define DEV true

#include <iostream>
#include "src/DeveloperTools.h"
#include "src/glContext.h"

bool done;
DeveloperTools devTools;

void HandleInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		SDL_Keycode key = event.key.keysym.sym;

		switch (event.type)
		{
			case SDL_QUIT:
				done = true;
				break;
			case SDL_KEYDOWN:
				if (key == SDLK_ESCAPE)
					done = true;
		}

		if (devTools.GetActive())
			devTools.HandleInput(done, event, key);
	}
}

void Update()
{

}

int main(int argc, char* argv[])
{
	done = false;
	devTools = new DeveloperTools(DEV);

	glContext context = glContext("Hello World!", 500, 500, false);

	while (!done)
	{
		HandleInput();
		Update();
	}

	return 0;
}