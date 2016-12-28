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

	_camera = Camera(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), &_program, 45.0f, 1.0f, 0.1f, 100.0f);
	_renderer = Renderer::Get(_program.GetProgram(), _context);
	_renderer->SetCamera(&_camera);

	DebugTools::SectionBreak();
}

void ProgramInstance::Runtime()
{
	glEnable(GL_DEPTH_TEST);

	while (!done)
	{
		HandleInput();
		FixedUpdate();
		Update();
		Render();
	}

	_context.CleanExit();
	SDL_Quit();
}

void ProgramInstance::HandleInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		SDL_Keycode key = event.key.keysym.sym;

		switch (event.type)
		{
			case SDL_QUIT:
				done = true;
				break;
			case SDL_KEYDOWN:
				if (key == SDLK_ESCAPE)
					done = true;
				break;

			case SDL_DROPFILE:
				std::vector<std::string> tmp;
				AssetManager::ReadFile(event.drop.file, tmp);

				glm::vec2* positions = new glm::vec2[tmp.size() - 1];
				for (int i = 0; i < tmp.size(); i++)
				{
					AssetManager::FindValue(tmp[i], 'X', positions[i].x);
					AssetManager::FindValue(tmp[i], 'Y', positions[i].y);
				}

				_renderer->Clear3DRender();
				Trajectory t = Trajectory(_program, positions, tmp.size() - 1);
				_renderer->AddToRender(new Heatmap(_program, positions, tmp.size() - 1));

				delete[] positions;
				break;
		}

		_camera.HandleInput(event, _context);
	}
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
	_renderer->PreRender();
	_renderer->Render();
	_renderer->PostRender();
}