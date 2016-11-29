#ifndef GL_PROGRAM_H
	#define GL_PROGRAM_H

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
		glProgram();
		glProgram operator=(const glProgram& other);

		void Initialize();
		void LinkShader(GLenum eShaderType, std::string shaderDir);

	private:
		GLuint CreateShader(GLenum eShaderType, std::string shaderDir, GLint& status);
		GLuint CreateProgram(const std::vector<GLuint> &shaderList);

		GLuint _program;

		std::vector<GLuint> _shaders;
};

#endif