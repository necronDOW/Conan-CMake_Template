#include "Line.h"

Line::Line() : DrawableBase() { }

Line::Line(glProgram& program, glm::vec2 start, glm::vec2 end, bool initialize)
	: DrawableBase(program, glm::vec3(start.x, start.y, 0))
{
	glm::vec2 diff = end - start;

	CreateVertex(glm::vec3(0));
	CreateVertex(glm::vec3(diff.x, diff.y, 0));

	if (initialize)
		Initialize();
}

Line::Line(glProgram& program, glm::vec2 start, glm::vec2 end, glm::vec3 color, bool initialize)
	: DrawableBase(program, glm::vec3(start.x, start.y, 0))
{
	glm::vec2 diff = end - start;

	CreateVertex(glm::vec3(0), color);
	CreateVertex(glm::vec3(diff.x, diff.y, 0), color);

	if (initialize)
		Initialize();
}

void Line::MainDraw()
{
	glDrawArrays(GL_LINES, 0, _vCount);
}