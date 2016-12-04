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
		bool InitializeVertexBuffer();
		void InitializeVertexArrayObject();
		void CreateVertex(glm::vec3 positions, glm::vec3 color);

		GLuint _vao, _ebo, _vbo;
		GLint _svlPosition, _svlVertColor, _svlTranslate, _svlOffset;

		bool isReady = false;
		glm::vec3 _position;
		glm::mat4 _transformations;
		std::vector<GLfloat> _vData;

		GLuint _eData[6] = {
			0, 1, 2,
			2, 3, 0
		};
};

#endif