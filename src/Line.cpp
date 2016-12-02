#include "Line.h"

Line::Line(glProgram* program, glm::vec3 start, glm::vec3 end)
	: DrawableBase(program, start)
{

}

void Line::InitializeVertexBuffer()
{
	DrawableBase::InitializeVertexBuffer();



	InitializeVertexArrayObject();
}

void Line::Draw()
{
	DrawableBase::PerformDraw(GL_LINES, 2);
}