#ifndef sdlinstance_h_defined
#define sdlinstance_h_defined

#include <SDL.h>
#include "DebugTools.h"

class SDL_Instance
{
	public:
		/* SDL_Instance Constructor (+1 overloads). */
		SDL_Instance();
		/* SDL_Instance Constructor (+1 overloads):
			char* exeName : The name which will be displayed on the window.
			int width : The width of the window. 
			int height : The height of the window. 
			bool isFullscreen : Whether or not the window should be rendered in full screen. */
		SDL_Instance(char* exeName, int width, int height, bool isFullscreen = false);

		/* SDL_Instance Destructor. */
		~SDL_Instance();

		/* Returns the name of the window. */
		char* GetName();
		/* Returns the dimensions and position of the window. */
		SDL_Rect GetDimensions();
		/* Returns the SDL_Window component. */
		SDL_Window* GetWindow();
		/* Returns the SDL_Renderer component. */
		SDL_Renderer* GetRenderer();

		/* Sets whether or not the window is full screen:
			bool value : True sets the window to full screen, false sets the window to windoweded mode. */
		void SetFullScreen(bool value);

		/* Sets the width and height of the window when windowed. 
			int width : The new width of the window. 
			int height : The new height of the window. */
		void SetDimensions(int newWidth, int newHeight);

		/* Scales the content within the window to a specified value. 
			float modifierX : The X scalar, adjusts scale across width. 
			float modifierY : The Y scalar, adjusts scale across height. */
		void SetRenderScale(float modifierX, float modifierY);

	private:
		/* Display an error message and quit SDL safely.
			char* text : The text to be displayed */
		void Log(char* text, DebugTools::LogType type, bool terminate = false);

		/* Exit SDL and perform necessary cleanup operations. */
		void CleanExit();

		SDL_Window *_window;		// Pointer to the generated SDL_Window for this instance.
		SDL_Renderer *_renderer;	// Pointer to the generated SDL_Renderer for this instance.
		char* _name;				// The name value associated with this window.
};

#endif