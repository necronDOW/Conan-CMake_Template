#include "ProgramInstance.h"
#include "Renderer.h"
#include <time.h>

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

				if (PromptClearRender())
				{
					glm::vec2* positions = new glm::vec2[tmp.size() - 1];
					for (unsigned int i = 0; i < tmp.size(); i++)
					{
						AssetManager::FindValue(tmp[i], 'X', positions[i].x);
						AssetManager::FindValue(tmp[i], 'Y', positions[i].y);
					}

					ScalePositions(positions, tmp.size() - 1, 0.001f);
					//CentralizePositions(positions, tmp.size() - 1);
					_trajectory = new Trajectory(_program, positions, tmp.size() - 1);
					if (_heatmap == nullptr)
					{
						_heatmap = new Heatmap(_program, positions, tmp.size() - 1, 25);
						_renderer->AddToRender(_heatmap);
					}
					else _heatmap->AddPositions(positions, tmp.size() - 1);
					
					delete[] positions;
				}
				break;
		}

		_camera.HandleInput(event, _context);
	}
}

void ProgramInstance::FixedUpdate()
{

}

float last = 0.0f;
void ProgramInstance::Update()
{
	float now = (float)SDL_GetTicks() * 0.001f;
	float deltaTime = now - last;

	_camera.Update(deltaTime);

	srand(SDL_GetTicks());

	last = now;
}

void ProgramInstance::Render()
{
	_renderer->PreRender();
	_renderer->Render();
	_renderer->PostRender();
}

void ProgramInstance::ScalePositions(glm::vec2* &positions, unsigned int size, float scale)
{
	for (unsigned int i = 0; i < size; i++)
		positions[i] *= glm::vec2(scale);
}

void ProgramInstance::CentralizePositions(glm::vec2* &positions, unsigned int size)
{
	glm::vec2 offset = -positions[0];

	for (unsigned int i = 0; i < size; i++)
		positions[i] += offset;
}

bool ProgramInstance::PromptClearRender()
{
	const SDL_MessageBoxButtonData buttons[] = {
		{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Cancel" },
		{ 0, 1, "No" },
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 2, "Yes" }
	};

	const SDL_MessageBoxData msgBoxData = {
		SDL_MESSAGEBOX_INFORMATION,
		NULL,
		"File Loading ...",
		"Would you like to clear the current Render Window?",
		SDL_arraysize(buttons),
		buttons
	};

	int buttonID;
	SDL_ShowMessageBox(&msgBoxData, &buttonID);
	switch (buttonID)
	{
		case 1:
			return true;
		case 2:
			_trajectory = nullptr;
			_heatmap = nullptr;
			_renderer->Clear3DRender();
			return true;
		default:
			return false;
	}
}