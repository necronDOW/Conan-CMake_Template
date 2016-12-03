#include "ProgramInstance.h"
#include "Renderer.h"

ProgramInstance::ProgramInstance()
{
	Initialize();
	Runtime();
}

ProgramInstance::~ProgramInstance() { }

void ProgramInstance::Initialize()
{
	_program.LinkShader(GL_VERTEX_SHADER, "../../shaders/vert_shader.vert");
	_program.LinkShader(GL_FRAGMENT_SHADER, "../../shaders/frag_shader.frag");
	_program.Initialize();

	_camera = Camera(glm::vec3(0.0f, 0.1f, -1.4f), glm::vec3(-45.0f, 0.0f, 0.0f), &_program, 45.0f, 1.0f, 0.1f, 100.0f);
	_renderer = Renderer::Get(_program.GetProgram(), &_context);
	_renderer->SetCamera(&_camera);

	DebugTools::SectionBreak();
}

void ProgramInstance::Runtime()
{
	glEnable(GL_DEPTH_TEST);

	_renderer->AddToRender(new Line(&_program, glm::vec3(0, 0, 0), glm::vec3(1, 1, 0), glm::vec3(1, 0, 0)), false);

	while (!done)
	{
		FixedUpdate();
		Update();
		Render();
	}

	_context.CleanExit();
	SDL_Quit();
}

void ProgramInstance::FixedUpdate()
{

}

void ProgramInstance::Update()
{
	_camera.Update();
}

void ProgramInstance::Render()
{
	if (_renderer != NULL)
	{
		_renderer->PreRender();
		_renderer->Render();
		_renderer->PostRender();
	}
}