#include "Line.h"

Line::Line(glProgram* program, glm::vec3 start, glm::vec3 end, glm::vec3 colorRGB)
	: DrawableBase(program, start)
{
	PopulateVertexData(3, new glm::vec3[3] { start, end, glm::vec3(0.5f, 1.0f, 0.0f) }, colorRGB);

	InitializeVertexBuffer();

	DebugTools::SectionBreak();
}

void Line::InitializeVertexBuffer()
{
	DebugTools::Log("Generating vertex data buffer ...", DebugTools::Info, 1);
	glGenBuffers(1, &_oVertexDataBuffer);
	DebugTools::Log("Vertex data buffer created! GLuint is: " + _oVertexDataBuffer, DebugTools::Info, 2);

	DebugTools::Log("Creating vertex buffer data ...", DebugTools::Info, 2);
	glBindBuffer(GL_ARRAY_BUFFER, _oVertexDataBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vData), _vData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	InitializeVertexArrayObject();
}

void Line::Draw()
{
	DrawableBase::PerformDraw(GL_TRIANGLES, 3);
}