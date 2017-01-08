#ifndef programinstance_h_defined
#define programinstance_h_defined

#define KEYARRAY_SIZE 10

#include <iostream>
#include <time.h>

#include "glContext.h"
#include "glProgram.h"
#include "Renderer.h"
#include "Camera.h"
#include "DataSet.h"
#include "Trajectory.h"
#include "Heatmap.h"
#include "VisualHelper.h"

class ProgramInstance
{
	const SDL_Keycode _keyArray[KEYARRAY_SIZE]
	{
		SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5, 
		SDLK_6, SDLK_7, SDLK_8, SDLK_9, SDLK_0
	};

	public:
		ProgramInstance();
		~ProgramInstance();

	private:
		void Initialize();
		void Runtime();
		void HandleInput();
		void FixedUpdate();
		void Update();
		void Render();
		bool PromptClearRender();
		void PromptDataSet(std::string fileDir);

		bool done = false;
		glContext _context = glContext("Metrics Visualization Tool", 1000, 1000);
		glProgram _program = glProgram();
		Renderer* _renderer;
		Camera _camera;
		Heatmap* _heatmap = nullptr;
		std::vector<DataSet*> _dataSets;
};

#endif