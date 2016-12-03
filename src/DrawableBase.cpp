#include "DrawableBase.h"

DrawableBase::DrawableBase(glProgram& program, glm::vec3 position)
{
	DebugTools::Log("Initializing Drawable Object ...", DebugTools::Info);

	_svlPosition = program.GetShaderVarLocation("position");
	_svlVertColor = program.GetShaderVarLocation("vertColor");
	_svlTranslate = program.GetShaderVarLocation("translate", glProgram::Uni);
	_svlOffset = program.GetShaderVarLocation("offset", glProgram::Uni);

	_position = position;

	InitializeVertexBuffer();
	InitializeVertexArrayObject();

	DebugTools::Log("Drawable Object initialized successfully!", DebugTools::Info, 1);
}

void DrawableBase::InitializeVertexArrayObject()
{
	DebugTools::Log("Generating vertex array ...", DebugTools::Info, 1);

	glGenVertexArrays(1, &_vao);
	DebugTools::Log("Vertex array created! GLuint is: " + std::to_string(_vao), DebugTools::Info, 2);

	DebugTools::Log("Configuring vertex array (vbo=" + std::to_string(_vbo) + ", ebo=" + std::to_string(_ebo) + ") ...", DebugTools::Info, 2);

	glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

		glEnableVertexAttribArray(_svlPosition);
		glVertexAttribPointer(_svlPosition, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

		glEnableVertexAttribArray(_svlVertColor);
		glVertexAttribPointer(_svlVertColor, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindVertexArray(0);

	glDisableVertexAttribArray(_svlPosition);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	DebugTools::Log("Vertex array configured successfully!", DebugTools::Info, 2);
}

void DrawableBase::InitializeVertexBuffer()
{
	DebugTools::Log("Generating buffers ...", DebugTools::Info, 1);

	glGenBuffers(1, &_vbo);
	DebugTools::Log("Vertex data buffer created! GLuint is: " + std::to_string(_vbo), DebugTools::Info, 2);

	glGenBuffers(1, &_ebo);
	DebugTools::Log("Element buffer created! GLuint is: " + std::to_string(_ebo), DebugTools::Info, 2);
	
	DebugTools::Log("Creating vertex buffer data ...", DebugTools::Info, 2);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(_vData), _vData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	DebugTools::Log("Creating element buffer data ...", DebugTools::Info, 2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_eData), _eData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void DrawableBase::Draw()
{
	glUniform3f(_svlOffset, _position.x, _position.y, _position.z);
	glUniformMatrix4fv(_svlTranslate, 1, GL_FALSE, glm::value_ptr(_transformations));

	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

//bool DrawableBase::PopulateVertexData(int size, glm::vec3 positions[], glm::vec3 colorRGB)
//{
//	_vData = new GLfloat[size * 6];
//	int iterator = 0;
//	for (int i = 0; i < size * 6; i += 6)
//	{
//		_vData[i] = positions[iterator].x;
//		_vData[i + 1] = positions[iterator].y;
//		_vData[i + 2] = positions[iterator].z;
//		_vData[i + 3] = colorRGB.x;
//		_vData[i + 4] = colorRGB.y;
//		_vData[i + 5] = colorRGB.z;
//
//		iterator++;
//	}
//
//	return true;
//}
//
//bool DrawableBase::PopulateVertexData(int size, glm::vec3 positions[], glm::vec3 colorsRGB[])
//{
//	_vData = new GLfloat[size * 6];
//	int iterator = 0;
//	for (int i = 0; i < size * 6; i += 6)
//	{
//		_vData[i] = positions[iterator].x;
//		_vData[i + 1] = positions[iterator].y;
//		_vData[i + 2] = positions[iterator].z;
//		_vData[i + 3] = colorsRGB[iterator].x;
//		_vData[i + 4] = colorsRGB[iterator].y;
//		_vData[i + 5] = colorsRGB[iterator].z;
//
//		iterator++;
//	}
//
//	return true;
//}