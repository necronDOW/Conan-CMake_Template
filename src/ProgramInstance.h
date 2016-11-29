#pragma once

#include <iostream>

#include "glContext.h"
#include "glProgram.h"

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
};