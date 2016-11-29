#include "src/ProgramInstance.h"

bool done;
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
	}
}

void Update()
{

}

int main(int argc, char* argv[])
{
	ProgramInstance program = ProgramInstance();
	return 0;
}