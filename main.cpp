#include <iostream>
#include "src/SDL_Instance.h";
#undef main

int main(int argc, char* argv[])
{
	SDL_Instance* sdl_i = new SDL_Instance("Analytics Tool", 500, 500);
	system("pause");

	return 0;
}