#include "Renderer.h"

Renderer* Renderer::_instance = NULL;

Renderer* Renderer::Get()
{
	if (_instance == nullptr)
		DebugTools::Log("No Renderer created! Use Get(GLuint, glContext*) to create one.", DebugTools::Warn);
	return _instance;
}

Renderer* Renderer::Get(GLuint program, glContext& context)
{
	if (_instance == nullptr)
		_instance = new Renderer(program, context);
	return _instance;
}

Renderer::Renderer(GLuint program, glContext& context)
{
	_program = program;
	_context = context;
}

void Renderer::PreRender()
{
	glViewport(0, 0, 720, 480);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render()
{
	if (_program == 0)
	{
		DebugTools::Log("Invalid program selected as render target, aborting!", DebugTools::Warn);
		return;
	}

	glUseProgram(_program);

	// Interface draw calls
	if (_camera != NULL)
	{
		glUniformMatrix4fv(_projectionLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
		glUniformMatrix4fv(_viewLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
		for (size_t i = 0; i < _interfaceObjs.size(); i++)
			_interfaceObjs[i].Draw();

		// 3D draw calls
		glUniformMatrix4fv(_projectionLocation, 1, GL_FALSE, glm::value_ptr(_camera->GetProjection()));
		glUniformMatrix4fv(_viewLocation, 1, GL_FALSE, glm::value_ptr(_camera->GetView()));
		for (size_t i = 0; i < _3DObjs.size(); i++)
			_3DObjs[i].Draw();
	}

	glUseProgram(0);
}

void Renderer::PostRender()
{
	// IMPORTANT : Prevents memory leaks with regards to glClear.
	SDL_GL_SwapWindow(_context.GetWindow());
}

void Renderer::Clean()
{

}

void Renderer::AddToRender(DrawableBase obj, bool is3D)
{
	if (is3D) _3DObjs.push_back(obj);
	else _interfaceObjs.push_back(obj);
}

void Renderer::SetCamera(Camera* camera)
{
	_camera = camera;
	_projectionLocation = camera->GetProjectionLocation();
	_viewLocation = camera->GetViewLocation();
}