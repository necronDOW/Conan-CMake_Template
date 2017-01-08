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
				if (_dataSets.size() != 0)
				{
					if (!PromptClearRender())
					{
						if (_heatmap == nullptr)
							_heatmap = new Heatmap();

						PromptDataSet(event.drop.file);
					}
				}
				else
				{
					if (_heatmap == nullptr)
						_heatmap = new Heatmap();

					PromptDataSet(event.drop.file);
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

bool ProgramInstance::PromptClearRender()
{
	bool clear, cancel;
	std::vector<MessageBoxOption*> msgOptions;
	msgOptions.push_back(new MessageBoxOption("Yes", &clear));
	msgOptions.push_back(new MessageBoxOption("No", NULL));
	msgOptions.push_back(new MessageBoxOption("Cancel", &cancel));

	DialogTools::ShowMessage("Loading Data ...", "Would you like to clear the current Render Window?", msgOptions);

	if (clear)
	{
		delete _heatmap;
		_heatmap = nullptr;
		_renderer->Clear3DRender();
		_dataSets.clear();
	}

	return cancel;
}

void ProgramInstance::PromptDataSet(std::string fileDir)
{
	DataSet* dataSet = new DataSet(_program, fileDir, _heatmap, 0.001f);
	_dataSets.push_back(dataSet);

	bool showHeatmap, showTrajectory, showBoth;
	std::vector<MessageBoxOption*> msgOptions;
	msgOptions.push_back(new MessageBoxOption("Show Heatmap", &showHeatmap));
	msgOptions.push_back(new MessageBoxOption("Show Trajectory", &showTrajectory));
	msgOptions.push_back(new MessageBoxOption("Show Both", &showBoth));

	DialogTools::ShowMessage("Render Options", "Please choose whether you want to see the trajectory, heatmap or both.", msgOptions);

	if (showBoth)
		showHeatmap = showTrajectory = showBoth;

	if (showHeatmap)
		_heatmap->ApplyLastHistogram();
	
	if (!showTrajectory)
		dataSet->GetTrajectory()->SetDraw(false);
}