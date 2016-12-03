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
		DrawableBase(glProgram& program, glm::vec3 position);
		void Draw();

	protected:
		DrawableBase() { }
		void InitializeVertexBuffer();
		void InitializeVertexArrayObject();
		//bool PopulateVertexData(int size, glm::vec3 positions[], glm::vec3 colorRGB);
		//bool PopulateVertexData(int size, glm::vec3 positions[], glm::vec3 colorsRGB[]);

		GLuint _vao, _ebo, _vbo;
		GLint _svlPosition, _svlVertColor, _svlTranslate, _svlOffset;

		glm::vec3 _position;
		glm::mat4 _transformations;
		GLfloat _vData[18] = {
			0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.433f, -0.25f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.433f, -0.25f, 0.0f, 1.0f, 1.0f, 1.0f
		};

		GLuint _eData[3] = {
			0, 1, 2
		};
};

#endif