#include "Line.h"

Line::Line() : DrawableBase() { }

Line::Line(glProgram& program, glm::vec3 start, glm::vec3 end, bool initialize)
	: DrawableBase(program, start)
{
	CreateVertex(start);
	CreateVertex(end);

	if (initialize)
		Initialize();
}

Line::Line(glProgram& program, glm::vec3 start, glm::vec3 end, glm::vec3 color, bool initialize)
	: DrawableBase(program, start)
{
	CreateVertex(start, color);
	CreateVertex(end, color);

	if (initialize)
		Initialize();
}

void Line::MainDraw()
{
	glDrawArrays(GL_LINES, 0, _vCount);
}