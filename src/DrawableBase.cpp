#include "DrawableBase.h"

DrawableBase::DrawableBase(glProgram& program, glm::vec3 position)
{
	DebugTools::Log("Initializing Drawable Object ...", DebugTools::Info);

	_svlPosition = program.GetShaderVarLocation("position");
	_svlVertColor = program.GetShaderVarLocation("vertColor");
	_svlTranslate = program.GetShaderVarLocation("translate", glProgram::Uni);
	_svlOffset = program.GetShaderVarLocation("offset", glProgram::Uni);

	_position = position;

	CreateVertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	CreateVertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	CreateVertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	CreateVertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.5f));

	if (InitializeVertexBuffer())
	{
		InitializeVertexArrayObject();
		DebugTools::Log("Drawable Object initialized successfully!", DebugTools::Info, 1);

		isReady = true;
	}
	else DebugTools::Log("Drawable Object failed to initialize!", DebugTools::Warn, 1);
}

void DrawableBase::Draw()
{
	if (isReady)
	{
		glUniform3f(_svlOffset, _position.x, _position.y, _position.z);
		glUniformMatrix4fv(_svlTranslate, 1, GL_FALSE, glm::value_ptr(_transformations));

		glBindVertexArray(_vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

bool DrawableBase::InitializeVertexBuffer()
{
	DebugTools::Log("Generating buffers ...", DebugTools::Info, 1);

	glGenBuffers(1, &_vbo);
	DebugTools::Log("Vertex data buffer created! GLuint is: " + std::to_string(_vbo), DebugTools::Info, 2);

	glGenBuffers(1, &_ebo);
	DebugTools::Log("Element buffer created! GLuint is: " + std::to_string(_ebo), DebugTools::Info, 2);
	
	DebugTools::Log("Creating vertex buffer data ...", DebugTools::Info, 2);

	if (_vData.size() == 0)
	{
		DebugTools::Log("No vertex data provided, aborting ...", DebugTools::Warn, 2);
		return false;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER,  _vData.size() * sizeof(_vData.front()), &_vData.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	DebugTools::Log("Creating element buffer data ...", DebugTools::Info, 2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_eData), _eData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return true;
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

void DrawableBase::CreateVertex(glm::vec3 position, glm::vec3 color)
{
	_vData.push_back(position.x);
	_vData.push_back(position.y);
	_vData.push_back(position.z);
	_vData.push_back(color.x);
	_vData.push_back(color.y);
	_vData.push_back(color.z);
}