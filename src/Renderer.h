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
#include "DrawableBase.h"

class Renderer
{
	private:
		/*Renderer(Renderer const&) { }
		Renderer& operator=(Renderer const&) { }*/
		static Renderer* _instance;

	public:
		static Renderer* Get();
		static Renderer* Get(GLuint program, glContext& context);
	
	public:
		Renderer() { }
		Renderer(GLuint program, glContext& context);
		void PreRender();
		void Render();
		void PostRender();
		void Clean();
		void AddToRender(DrawableBase obj, bool is3D = true);
		void SetCamera(Camera* camera);

	private:
		GLuint _program;
		glContext _context;
		Camera* _camera = NULL;
		GLint _projectionLocation;
		GLint _viewLocation;
		std::vector<DrawableBase> _interfaceObjs;
		std::vector<DrawableBase> _3DObjs;
};

#endif