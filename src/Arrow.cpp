#include "Arrow.h"

Arrow::Arrow(glProgram* program, glm::vec3 start, glm::vec3 end)
	: Line(program, start, end)
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