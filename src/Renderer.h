#ifndef renderer_h_defined
#define renderer_h_defined

#include <GL/glew.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glContext.h"
#include "DebugTools.h"
#include "Camera.h"

class Renderer
{
	private:
		Renderer() { }
		Renderer(GLuint program, glContext* context);
		Renderer(Renderer const&) { }
		Renderer& operator=(Renderer const&) { }
		static Renderer* _instance;

	public:
		static Renderer* Get();
		static Renderer* Get(GLuint program, glContext* context);
	
	public:
		void PreRender();
		void Render();
		void PostRender();
		void Clean();

		void SetCamera(Camera* camera);

	private:
		void Draw();

		GLuint _program;
		glContext* _context;
		Camera* _camera = NULL;
		GLint _projectionLocation;
		GLint _viewLocation;
};

#endif