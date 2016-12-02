#ifndef glprogram_h_defined
#define glprogram_h_defined

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <SDL.h>
#include <GL/glew.h>

#include "AssetManager.h"
#include "DebugTools.h"

class glProgram
{
	public:
		enum ShaderVars
		{
			Att,
			Uni
		};

		glProgram();
		glProgram operator=(const glProgram& other);

		void Initialize();
		void LinkShader(GLenum eShaderType, std::string shaderDir);
		GLuint GetProgram();
		GLint GetShaderVarLocation(const GLchar* id, ShaderVars type = ShaderVars::Att);

	private:
		GLuint CreateShader(GLenum eShaderType, std::string shaderDir, GLint& status);
		GLuint CreateProgram(const std::vector<GLuint> &shaderList);

		GLuint _program;

		std::vector<GLuint> _shaders;
};

#endif