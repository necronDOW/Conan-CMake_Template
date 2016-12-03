#ifndef plane_h_defined
#define plane_h_defined

#include "DrawableBase.h"

class Plane : public DrawableBase
{
	public:
		Plane(glProgram* program, glm::vec3 position, glm::vec3 size, int xCellCount = 2, int yCellCount = 2);
		void InitializeVertexBuffer();
		void Draw();

	protected:
		Plane() { }

		GLuint _oElementBuffer;
		std::vector<GLuint> _eData;
};

#endif