#include "DrawableBase.h"

DrawableBase::DrawableBase(glProgram* program, glm::vec3 position)
{
	DebugTools::Log("Initializing Drawable Object ...", DebugTools::Info);

	_svlPosition = program->GetShaderVarLocation("position");
	_svlVertColor = program->GetShaderVarLocation("vertColor");
	_svlTranslate = program->GetShaderVarLocation("translate", glProgram::Uni);
	_svlOffset = program->GetShaderVarLocation("offset", glProgram::Uni);

	_position = position;

	DebugTools::Log("Drawable Object initialized successfully!", DebugTools::Info, 1);
	DebugTools::SectionBreak();
}

void DrawableBase::InitializeVertexArrayObject()
{
	DebugTools::Log("Generating Vertex Array ...", DebugTools::Info, 1);

	glGenVertexArrays(1, &_oVertexArray);
	DebugTools::Log("Vertex Array created! GLuint is: " + _oVertexArray, DebugTools::Info, 2);

	DebugTools::Log("Binding ...", DebugTools::Info, 1);

	glBindVertexArray(_oVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, _oVertexDataBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _oElementBuffer);

		glEnableVertexAttribArray(_svlPosition);
		glVertexAttribPointer(_svlPosition, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);

		glEnableVertexAttribArray(_svlVertColor);
		glVertexAttribPointer(_svlVertColor, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindVertexArray(0);

	DebugTools::Log("Vertex Array binded successfully!", DebugTools::Info, 1);

	glDisableVertexAttribArray(_svlPosition);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	DebugTools::SectionBreak();
}

void DrawableBase::InitializeVertexBuffer()
{
	DebugTools::Log("Generating buffers ...", DebugTools::Info, 1);

	glGenBuffers(1, &_oVertexDataBuffer);
	DebugTools::Log("Vertex Data Buffer created! GLuint is: " + _oVertexDataBuffer, DebugTools::Info, 2);
	
	glGenBuffers(1, &_oElementBuffer);
	DebugTools::Log("Element Buffer created! GLuint is: " + _oElementBuffer, DebugTools::Info, 2);

	DebugTools::Log("Buffers generated! Binding ...", DebugTools::Info, 1);

	glBindBuffer(GL_ARRAY_BUFFER, _oVertexDataBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _oElementBuffer);

	DebugTools::Log("Buffers binded successfully!", DebugTools::Info, 1);
	DebugTools::SectionBreak();
}