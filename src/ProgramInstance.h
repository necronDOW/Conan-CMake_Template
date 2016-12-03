#ifndef programinstance_h_defined
#define programinstance_h_defined

#include <iostream>

#include "glContext.h"
#include "glProgram.h"
#include "Renderer.h"
#include "Camera.h"
#include "DrawableBase.h"

class ProgramInstance
{
	public:
		ProgramInstance();
		~ProgramInstance();

	private:
		void Initialize();
		void Runtime();
		void FixedUpdate();
		void Update();
		void Render();

		bool done = false;
		glContext _context = glContext("Heatmap Visualization Tool", 960, 960);
		glProgram _program = glProgram();
		Renderer* _renderer = NULL;
		Camera _camera;
};

#endif