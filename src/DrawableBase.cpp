#include "DrawableBase.h"

DrawableBase::DrawableBase(glProgram& program, glm::vec3 position)
{
	DebugTools::Log("Initializing Drawable Object ...", DebugTools::Info);

	_svlPosition = program.GetShaderVarLocation("position");
	_svlVertColor = program.GetShaderVarLocation("vertColor");
	_svlTranslate = program.GetShaderVarLocation("translate", glProgram::Uni);
	_svlOffset = program.GetShaderVarLocation("offset", glProgram::Uni);

	_position = position;
}

DrawableBase::~DrawableBase()
{
	/*glDeleteBuffers(1, &_vbo);
	glDeleteVertexArrays(1, &_vao);

	glDeleteBuffers(1, &_ebo);

	_vData.clear();
	_eData.clear();*/
}

void DrawableBase::Initialize()
{
	if (InitializeVertexBuffer())
	{
		InitializeVertexArrayObject();
		DebugTools::Log("Drawable Object initialized successfully!", DebugTools::Info, 1);

		_isReady = true;
	}
	else DebugTools::Log("Drawable Object failed to initialize!", DebugTools::Warn, 1);
}

void DrawableBase::SetUniforms()
{
	glUniform3f(_svlOffset, _position.x, _position.y, _position.z);
	glUniformMatrix4fv(_svlTranslate, 1, GL_FALSE, glm::value_ptr(_transformations));
}

void DrawableBase::MainDraw()
{
	glDrawArrays(GL_POINTS, 0, _vCount);
}

void DrawableBase::Draw()
{
	if (_isReady && _draw)
	{
		SetUniforms();

		glBindVertexArray(_vao);
		MainDraw();
		glBindVertexArray(0);
	}
}

void DrawableBase::SetDraw(bool value) { _draw = value; }

void DrawableBase::Transform(glm::vec3 transform)
{
	_position += transform;
}

glm::vec2 DrawableBase::GetPositionV2() { return glm::vec2(_position.x, _position.y); }
glm::vec3 DrawableBase::GetPositionV3() { return _position; }

bool DrawableBase::InitializeVertexBuffer()
{
	DebugTools::Log("Generating buffers ...", DebugTools::Info, 1);

	if (_vData.size() == 0)
	{
		DebugTools::Log("No vertex data provided, aborting ...", DebugTools::Warn, 2);
		return false;
	}
	else
	{
		glGenBuffers(1, &_vbo);
		DebugTools::Log("Vertex data buffer created! GLuint is: " + std::to_string(_vbo), DebugTools::Info, 2);

		DebugTools::Log("Creating vertex buffer data ...", DebugTools::Info, 2);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			glBufferData(GL_ARRAY_BUFFER, _vData.size() * sizeof(_vData.front()), &_vData.front(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//_vData.clear();
	}

	if (_eData.size() == 0)
		DebugTools::Log("No element data provided, skipping ...", DebugTools::Warn, 2);
	else
	{
		glGenBuffers(1, &_ebo);
		DebugTools::Log("Element buffer created! GLuint is: " + std::to_string(_ebo), DebugTools::Info, 2);

		DebugTools::Log("Creating element buffer data ...", DebugTools::Info, 2);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, _eData.size() * sizeof(_eData.front()), &_eData.front(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		if (_eMax > _vCount)
			DebugTools::Log("One (or more) element indices exceed the vertex buffer size!", DebugTools::Warn, 2);

		//_eData.clear();
	}

	return true;
}

void DrawableBase::InitializeVertexArrayObject()
{
	DebugTools::Log("Generating vertex array ...", DebugTools::Info, 1);

	glGenVertexArrays(1, &_vao);
	DebugTools::Log("Vertex array created! GLuint is: " + std::to_string(_vao), DebugTools::Info, 2);

	std::string _vboStr = "vbo=" + std::to_string(_vbo);
	std::string _eboStr = _ebo != 0 ? ", ebo=" + std::to_string(_ebo) : "";
	DebugTools::Log("Configuring vertex array (" + _vboStr + _eboStr + ") ...", DebugTools::Info, 2);

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

void DrawableBase::ReInitialize()
{
	InitializeVertexBuffer();
	InitializeVertexArrayObject();
}

void DrawableBase::CreateVertex(glm::vec3 position, glm::vec3 color)
{
	_vData.push_back(position.x);
	_vData.push_back(position.y);
	_vData.push_back(position.z);
	_vData.push_back(color.x);
	_vData.push_back(color.y);
	_vData.push_back(color.z);

	_vCount++;
}

void DrawableBase::CreateElement(int vertA, int vertB)
{
	_eData.push_back(vertA);
	_eData.push_back(vertB);

	_eCount++;

	int max = std::max(vertA, vertB);
	_eMax = _eMax < max ? max : _eMax;
}

void DrawableBase::CreateElement(int vertA, int vertB, int vertC)
{
	_eData.push_back(vertA);
	_eData.push_back(vertB);
	_eData.push_back(vertC);

	_eCount++;

	int max = std::max({ vertA, vertB, vertC });
	_eMax = _eMax < max ? max : _eMax;
}