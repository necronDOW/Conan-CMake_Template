#include "Arrow.h"

Arrow::Arrow(glProgram* program, glm::vec3 start, glm::vec3 end, glm::vec3 colorRGB)
	: Line(program, start, end, colorRGB)
{

}

void Arrow::InitializeVertexBuffer()
{
	Line::InitializeVertexBuffer();



	InitializeVertexArrayObject();
}

void Arrow::Draw()
{
	DrawableBase::PerformDraw(GL_LINES, 6);
}