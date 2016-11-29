#include "glContext.h"

glContext::glContext() { }

glContext::glContext(char* name, int width, int height, bool isFullscreen)
{
	_name = name;

	Initialize();
	CreateWindow(width, height);
	SetFullScreen(isFullscreen);
	CreateContext();
	InitGlew();

	glViewport(0, 0, width, height);
	SDL_GL_SwapWindow(_window);

	DebugTools::SectionBreak();
}

glContext::~glContext()
{
	CleanExit();
}

void glContext::Log(std::string text, DebugTools::LogType type, bool terminate)
{
	DebugTools::Log(text, type);

	if (terminate)
		CleanExit();
}

void glContext::SetFullScreen(bool value)
{
	// Convert the bool value to a flag and set the fullscreen mode.
	Uint32 flag = value ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;
	SDL_SetWindowFullscreen(_window, flag);
}

void glContext::SetDimensions(int newWidth, int newHeight)
{
	// Set the associated window size to the given values.
	SDL_SetWindowSize(_window, newWidth, newHeight);
}

void glContext::Initialize()
{
	Log("Intitializing SDL ...", DebugTools::Info);

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		Log("Unable to initialize SDL (SDL_Init).", DebugTools::Error, true);

	Log("SDL initialized successfully!", DebugTools::Info);
}

void glContext::InitGlew()
{
	Log("Intitializing GLEW ...", DebugTools::Info);

	glewExperimental = GL_TRUE;
	GLenum status = glewInit();
	
	if (status != GLEW_OK)
		Log("Unable to initialize GLEW (glewInit).", DebugTools::Error, true);
	Log("GLEW Initialized successfully!", DebugTools::Info);

}

void glContext::CreateWindow(int width, int height)
{
	Log("Attempting to create an SDL Window ...", DebugTools::Info);

	int center = SDL_WINDOWPOS_CENTERED;

	_window = SDL_CreateWindow(_name, center, center, width, height, SDL_WINDOW_OPENGL);
	if (_window == nullptr)
		Log("Unable to create SDL window (SDL_CreateWindow).", DebugTools::Error, true);

	Log("SDL window created successfully!", DebugTools::Info);
}

void glContext::CreateContext()
{
	Log("Attempting to create a GL Context ...", DebugTools::Info);

	DebugTools::Log("Setting OpenGL attributes ...", DebugTools::Info, 1);
	SetGLAttributes();

	_context = SDL_GL_CreateContext(_window);
	if (_context == NULL)
	{
		SDL_DestroyWindow(_window);
		Log("Unable to create GL Context (SDL_GL_CreateContext).", DebugTools::Warn, false);
		DebugTools::Log("SDL Window has been destroyed.", DebugTools::Warn, 1);
	}

	Log("GL Context created successfully!", DebugTools::Info);
}

void glContext::SetGLAttributes()
{
	int major = 3, minor = 3;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

void glContext::CleanExit()
{
	SDL_GL_DeleteContext(_context);

	SDL_DestroyWindow(_window);
	_window = nullptr;
}

char* glContext::GetName() { return _name; }
SDL_Window* glContext::GetWindow() { return _window; }
SDL_Rect glContext::GetDimensions()
{
	if (_window)
	{
		SDL_Rect tmpDimensions;
		SDL_GetWindowPosition(_window, &tmpDimensions.x, &tmpDimensions.y);
		SDL_GetWindowSize(_window, &tmpDimensions.w, &tmpDimensions.h);

		return tmpDimensions;
	}
}