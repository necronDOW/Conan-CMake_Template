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
}

void DrawableBase::InitializeVertexArrayObject()
{
	DebugTools::Log("Generating vertex array ...", DebugTools::Info, 1);

	glGenVertexArrays(1, &_oVertexArray);
	DebugTools::Log("Vertex array created! GLuint is: " + _oVertexArray, DebugTools::Info, 2);

	DebugTools::Log("Binding ...", DebugTools::Info, 2);

	glBindVertexArray(_oVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, _oVertexDataBuffer);

		glEnableVertexAttribArray(_svlPosition);
		glVertexAttribPointer(_svlPosition, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

		glEnableVertexAttribArray(_svlVertColor);
		glVertexAttribPointer(_svlVertColor, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindVertexArray(0);

	DebugTools::Log("Vertex array bound successfully!", DebugTools::Info, 2);

	glDisableVertexAttribArray(_svlPosition);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DrawableBase::InitializeVertexBuffer()
{
	DebugTools::Log("Generating vertex data buffer ...", DebugTools::Info, 1);
	glGenBuffers(1, &_oVertexDataBuffer);
	DebugTools::Log("Vertex data buffer created! GLuint is: " + _oVertexDataBuffer, DebugTools::Info, 2);
	
	DebugTools::Log("Creating vertex buffer data ...", DebugTools::Info, 2);
	glBindBuffer(GL_ARRAY_BUFFER, _oVertexDataBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(_vData), _vData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete[] _vData;
}

void DrawableBase::PerformDraw(GLenum mode, GLsizei count)
{
	glUniform3f(_svlOffset, _position.x, _position.y, _position.z);
	glUniformMatrix4fv(_svlTranslate, 1, GL_FALSE, glm::value_ptr(_transformations));

	glBindVertexArray(_oVertexArray);
	glDrawArrays(mode, 0, count);
	glBindVertexArray(0);
}

bool DrawableBase::PopulateVertexData(int size, glm::vec3 positions[], glm::vec3 colorRGB)
{
	_vData = new GLfloat[size * 6];
	int iterator = 0;
	for (int i = 0; i < size * 6; i += 6)
	{
		_vData[i] = positions[iterator].x;
		_vData[i + 1] = positions[iterator].y;
		_vData[i + 2] = positions[iterator].z;
		_vData[i + 3] = colorRGB.x;
		_vData[i + 4] = colorRGB.y;
		_vData[i + 5] = colorRGB.z;

		iterator++;
	}

	return true;
}

bool DrawableBase::PopulateVertexData(int size, glm::vec3 positions[], glm::vec3 colorsRGB[])
{
	_vData = new GLfloat[size * 6];
	int iterator = 0;
	for (int i = 0; i < size * 6; i += 6)
	{
		_vData[i] = positions[iterator].x;
		_vData[i + 1] = positions[iterator].y;
		_vData[i + 2] = positions[iterator].z;
		_vData[i + 3] = colorsRGB[iterator].x;
		_vData[i + 4] = colorsRGB[iterator].y;
		_vData[i + 5] = colorsRGB[iterator].z;

		iterator++;
	}

	return true;
}