#ifndef GL_PROGRAM_H
	#define GL_PROGRAM_H

#include <iostream>
#include <string>
#include <vector>

#include <SDL.h>
#include <GL/glew.h>

#include "AssetManager.h"

class glProgram
{
	public:
		glProgram();
		glProgram(std::string vertShaderDir, std::string fragShaderDir);
		glProgram operator=(const glProgram& other);

		void Initialize();

	private:
		GLuint CreateShader(GLenum eShaderType, std::string shaderDir);
		GLuint CreateProgram(const std::vector<GLuint> &shaderList);

		GLuint program;

		const std::string _strVertShader;
		const std::string _strFragShader;
};

#endif