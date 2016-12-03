#ifndef glcontext_h_defined
#define glcontext_h_defined

#include <GL/glew.h>
#include <SDL.h>
#include "DebugTools.h"

class glContext
{
	public:
		/* glContext Constructor (+1 overloads).*/
		glContext();
		/* glContext Constructor (+1 overloads):
			char* name : The name which will be displayed on the GL window. 
			int width : The width of the GL window. 
			int height : The height of the GL window. 
			bool isFullscreen : Whether or not the window should be rendered in full screen. */
		glContext(char* name, int width, int height, bool isFullscreen = false);

		/* glContext Destructor. */
		~glContext();

		void Log(std::string text, DebugTools::LogType type, bool terminate = false);
		void CleanExit();

		void SetFullScreen(bool value);
		void SetDimensions(int newWidth, int newHeight);

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
		SDL_GLContext _context;
};

#endif