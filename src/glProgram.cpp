#include "glProgram.h"

glProgram::glProgram() { }

void glProgram::Initialize()
{
	DebugTools::Log("Initializing program ...", DebugTools::Info);

	if (_shaders.size() == 0)
	{
		DebugTools::Log("No shaders loaded, aborting ...", DebugTools::Warn);
		return;
	}

	_program = CreateProgram(_shaders);
	if (_program == 0)
	{
		DebugTools::Log("Failed to create program!", DebugTools::Error, 1);
		return;
	}
	else DebugTools::Log("Program created successfully!", DebugTools::Info, 1);

	std::for_each(_shaders.begin(), _shaders.end(), glDeleteShader);
	_shaders.clear();
}

bool glProgram::LinkShader(GLenum eShaderType, std::string shaderDir)
{
	DebugTools::Log("Searching for shader (" + shaderDir + ") ...", DebugTools::Info);
	shaderDir = AssetManager::GetWorkingPath() + shaderDir;

	if (AssetManager::FileExists(shaderDir))
	{
		DebugTools::Log("Shader found! Creating shader ...", DebugTools::Info, 1);
		GLint success;
		_shaders.push_back(CreateShader(eShaderType, shaderDir, success));

		if (success == GL_TRUE)
			DebugTools::Log("Shader created successfully!", DebugTools::Info, 1);
		else DebugTools::Log("Failed to create shader!", DebugTools::Error, 1);

		return success;
	}
	else
	{
		DebugTools::Log("Shader not found!", DebugTools::Error, 1);
		return false;
	}
}

GLuint glProgram::GetProgram()
{
	return _program;
}

GLint glProgram::GetShaderVarLocation(const GLchar* id, ShaderVars type)
{
	switch (type)
	{
		case Att:
			return glGetAttribLocation(_program, id);
			break;
		case Uni:
			return glGetUniformLocation(_program, id);
			break;
	}
}

GLuint glProgram::CreateShader(GLenum eShaderType, std::string shaderDir, GLint& status)
{
	// REQUIRES REAL-TIME CONSOLE LOGGING.
	GLuint shader = glCreateShader(eShaderType);

	std::string shaderData;
	AssetManager::ReadFile(shaderDir, shaderData);
	const char* strFileData = shaderData.c_str();

	glShaderSource(shader, 1, &strFileData, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		const char* strShaderType = NULL;
		switch (eShaderType)
		{
			case GL_VERTEX_SHADER:
				strShaderType = "vertex";
				break;
			case GL_GEOMETRY_SHADER:
				strShaderType = "geometry";
				break;
			case GL_FRAGMENT_SHADER:
				strShaderType = "fragment";
				break;
		}

		fprintf(stderr, "Compile failure in %s shader: \n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}

	return shader;
}

GLuint glProgram::CreateProgram(const std::vector<GLuint> &shaderList)
{
	GLuint program = glCreateProgram();

	for (size_t i = 0; i < shaderList.size(); i++)
		glAttachShader(program, shaderList[i]);

	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	for (size_t i = 0; i < shaderList.size(); i++)
		glDetachShader(program, shaderList[i]);

	return program;
}

glProgram glProgram::operator=(const glProgram& other)
{
	this->_program = other._program;

	return *this;
}