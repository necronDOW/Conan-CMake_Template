#ifndef drawablebase_h_defined
#define drawablebase_h_defined

#include <GL/glew.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glProgram.h"
#include "DebugTools.h"

class DrawableBase
{
	public:
		DrawableBase(glProgram* program, glm::vec3 position);

	protected:
		void InitializeVertexArrayObject();
		void InitializeVertexBuffer();

		GLuint _oVertexArray;
		GLuint _oElementBuffer;
		GLuint _oVertexDataBuffer;
		glm::vec2 _size;
		glm::vec3 _position;
		glm::mat4 _transformations;

		GLint _svlPosition;
		GLint _svlVertColor;
		GLint _svlTranslate;
		GLint _svlOffset;
};

#endif