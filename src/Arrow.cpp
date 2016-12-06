#include "Arrow.h"

Arrow::Arrow() : Line() { }

Arrow::Arrow(glProgram& program, glm::vec3 start, glm::vec3 end, bool initialize)
	: Line(program, start, end, false)
{
	CreateElement(0, 1);
	CreateHead(start, end, 1.0f);

	if (initialize)
		Initialize();
}

Arrow::Arrow(glProgram& program, glm::vec3 start, glm::vec3 end, glm::vec3 color, bool initialize)
	: Line(program, start, end, color, false)
{
	CreateElement(0, 1);
	CreateHead(start, end, 1.0f, color);

	if (initialize)
		Initialize();
}

void Arrow::MainDraw()
{
	glDrawElements(GL_LINES, _eCount * 2, GL_UNSIGNED_INT, 0);
}

void Arrow::CreateHead(glm::vec3 start, glm::vec3 end, float t, glm::vec3 color)
{
	glm::vec3 diff = end - start;
	glm::vec3 tVec = start + (diff * t);

	CreateVertex(tVec, color);
	CreateVertex(tVec - (diff * 0.1f) + glm::vec3(-diff.y, diff.x, diff.z) * 0.1f, color);
	CreateVertex(tVec - (diff * 0.1f) + glm::vec3(diff.y, -diff.x, diff.z) * 0.1f, color);

	CreateElement(2, 3);
	CreateElement(2, 4);
}