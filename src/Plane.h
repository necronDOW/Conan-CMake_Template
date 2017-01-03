#ifndef plane_h_defined
#define plane_h_defined

#include "DrawableBase.h"

class Plane : public DrawableBase
{
	public:
		Plane(glProgram& program, glm::vec2 position, glm::vec2 dimensions, 
			unsigned int sizeX = 1, unsigned int sizeY = 1, float zOffset = 0.0f, bool initialize = true);
		Plane(glProgram& program, glm::vec2 position, glm::vec2 dimensions, glm::vec3 color, 
			unsigned int sizeX = 1, unsigned int sizeY = 1, float zOffset = 0.0f, bool initialize = true);

		glm::vec2 GetCellSize();
		glm::vec2 GetSize();

	protected:
		Plane();
		void CreateVertices(glm::vec3 color, float zOffset);
		void CreateElements();
		virtual void MainDraw();

		glm::vec2 _cellSize, _size;
};

#endif