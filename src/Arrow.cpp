#include "Arrow.h"

Arrow::Arrow() : Line() { }

Arrow::Arrow(glProgram& program, glm::vec2 start, glm::vec2 end, bool initialize)
	: Line(program, start, end, false)
{
	CreateElement(0, 1);
	CreateHead(start, end, 0.5f);

	if (initialize)
		Initialize();
}

Arrow::Arrow(glProgram& program, glm::vec2 start, glm::vec2 end, glm::vec3 color, bool initialize)
	: Line(program, start, end, color, false)
{
	CreateElement(0, 1);
	CreateHead(start, end, 0.5f, color);

	if (initialize)
		Initialize();
}

void Arrow::MainDraw()
{
	glDrawElements(GL_LINES, _eCount * 2, GL_UNSIGNED_INT, 0);
}

void Arrow::CreateHead(glm::vec2 start, glm::vec2 end, float t, glm::vec3 color)
{
	glm::vec3 diff = glm::vec3(end.x - start.x, end.y - start.y, 0);
	glm::vec3 tVec = glm::vec3(diff * t);

	_arrowSize = diff.length() * 0.1f;
	glm::vec3 diffOffset = diff * _arrowSize;

	CreateVertex(tVec, color);
	CreateVertex(tVec - diffOffset + glm::vec3(-diff.y, diff.x, diff.z) * _arrowSize, color);
	CreateVertex(tVec - diffOffset + glm::vec3(diff.y, -diff.x, diff.z) * _arrowSize, color);

	CreateElement(2, 3);
	CreateElement(2, 4);
}