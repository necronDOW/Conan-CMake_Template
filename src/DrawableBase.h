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
		virtual void Draw();

	protected:
		DrawableBase() { }
		void Initialize();
		bool InitializeVertexBuffer();
		void InitializeVertexArrayObject();
		void CreateVertex(glm::vec3 positions, glm::vec3 color = glm::vec3(1.0));
		void CreateElement(int vertA, int vertB);
		void CreateElement(int vertA, int vertB, int vertC);
		virtual void MainDraw();

		GLuint _vao, _ebo = 0, _vbo = 0;
		GLint _svlPosition, _svlVertColor, _svlTranslate, _svlOffset;

		glm::vec3 _position;
		glm::mat4 _transformations;
		std::vector<GLfloat> _vData;
		int _vCount = 0;
		std::vector<GLuint> _eData;
		int _eCount = 0, _eMax = 0;

	private:
		void SetUniforms();

		bool isReady = false;
};

#endif