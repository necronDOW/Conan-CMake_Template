#include "SDL_Instance.h"

/* PUBLIC */
SDL_Instance::SDL_Instance() { }

SDL_Instance::SDL_Instance(char* exeName, int width, int height, bool isFullScreen)
{
	// Initialize
	int sdl_ini = SDL_Init(SDL_INIT_EVERYTHING);
	if (sdl_ini != 0)
		Log("Unable to instantiate SDL (SDL_Init).", DebugTools::Error, true);
	Log("SDL initialized successfully.", DebugTools::Info);

	// Create an SDL window using the provided name and dimensions.
	int center = SDL_WINDOWPOS_CENTERED;
	_window = SDL_CreateWindow(exeName, center, center, width, height, SDL_WINDOW_SHOWN);
	if (_window == nullptr)
	{
		Log("Unable to create SDL window (SDL_CreateWindow).", DebugTools::Error, true);
		SetFullScreen(isFullScreen);
	}
	Log("SDL window created successfully.", DebugTools::Info);

	// Create an SDL renderer using the previously created window.
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == nullptr)
		Log("Enable to create SDL renderer (SDL_CreateRenderer).", DebugTools::Error, true);
	Log("SDL renderer created successfully.", DebugTools::Info);
}

SDL_Instance::~SDL_Instance()
{
	CleanExit();
}

char* SDL_Instance::GetName()
{
	// Return the name of the window.
	return _name;
}

SDL_Rect SDL_Instance::GetDimensions()
{
	// Create and populate the values of a temporary SDL_Rect.
	SDL_Rect tmpRect;
	SDL_GetWindowPosition(_window, &tmpRect.x, &tmpRect.y);
	SDL_GetWindowSize(_window, &tmpRect.w, &tmpRect.h);

	// Return the dimensions and position of the window.
	return tmpRect;
}

SDL_Window* SDL_Instance::GetWindow()
{
	// Return the associated SDL_Window.
	return _window;
}
SDL_Renderer* SDL_Instance::GetRenderer()
{
	// Return the associated SDL_Renderer.
	return _renderer;
}

void SDL_Instance::SetFullScreen(bool value)
{
	// Convert the bool value to a flag and set the fullscreen mode.
	Uint32 flag = value ? SDL_WINDOW_FULLSCREEN : 0;
	SDL_SetWindowFullscreen(_window, flag);
}

void SDL_Instance::SetDimensions(int newWidth, int newHeight)
{
	// Set the associated window size to the given values.
	SDL_SetWindowSize(_window, newWidth, newHeight);
}

void SDL_Instance::SetRenderScale(float modifierX, float modifierY)
{
	// Calculate the overall scale based on input parameters and existing dimensional information for the window.
	SDL_Rect windowDims = GetDimensions();
	float scaleX = (float)windowDims.w / modifierX;
	float scaleY = (float)windowDims.h / modifierY;

	// Set the render scale to the calculated size.
	SDL_RenderSetScale(_renderer, scaleX, scaleY);
}

/* PRIVATE */
void SDL_Instance::Log(char* text, DebugTools::LogType type, bool terminate)
{
	// Display the desired message.
	DebugTools::Log(text, type);

	// Terminate all SDL processes if desired.
	if (terminate)
		CleanExit();
}

void SDL_Instance::CleanExit()
{
	// Destroy the window and renderer instances before quiting SDL.
	SDL_DestroyWindow(_window);
	_window = nullptr;

	SDL_DestroyRenderer(_renderer);
	_renderer = nullptr;
	SDL_Quit();
}