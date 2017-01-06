#ifndef programinstance_h_defined
#define programinstance_h_defined

#include <iostream>

#include "glContext.h"
#include "glProgram.h"
#include "Renderer.h"
#include "Camera.h"
#include "DataSet.h"
#include "Trajectory.h"
#include "Heatmap.h"
#include "HeatmapNew.h"

class ProgramInstance
{
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
		void ScalePositions(glm::vec2* &positions, unsigned int size, float scale);
		void CentralizePositions(glm::vec2* &positions, unsigned int size);
		bool PromptClearRender();
		void Sync(Trajectory* t, Heatmap* h);

		bool done = false;
		glContext _context = glContext("Metrics Visualization Tool", 1000, 1000);
		glProgram _program = glProgram();
		Renderer* _renderer;
		Camera _camera;
		HeatmapNew* _heatmap = nullptr;
};

#endif