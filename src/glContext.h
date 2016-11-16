#ifndef GL_CONTEXT_H
	#define GL_CONTEXT_H

#include <GL/glew.h>
#include <SDL.h>
#include "DebugTools.h"

class glContext
{
	public:
		glContext();
		glContext(char* name, int width, int height, bool isFullscreen = false);

		void Log(char* text, DebugTools::LogType type, bool terminate = false);

		void SetFullScreen(bool value);
		void SetDimensions(int newWidth, int newHeight);
		void SetRenderScale(float modifierX, float modifierY);

		char* GetName();
		SDL_Window* GetWindow();
		SDL_Rect GetDimensions();

	private:
		void Initialize();
		void InitGlew();
		void CreateWindow(int width, int height);
		void CreateContext();
		void SetGLAttributes();

		char* _name;
		SDL_Window* _window;
		SDL_GLContext _context = NULL;
};

#endif