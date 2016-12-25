#include "Plane.h"

Plane::Plane() : DrawableBase() { }

Plane::Plane(glProgram& program, glm::vec3 position, glm::vec2 dimensions, unsigned int sizeX, unsigned int sizeY, bool initialize)
	: DrawableBase(program, position)
{
	glm::vec2 cellSize = glm::vec2(dimensions.x / (float)sizeX, dimensions.y / (float)sizeY);
	glm::vec3 offset = glm::vec3(-dimensions.x / 2.0f, -dimensions.y / 2.0f, 0.0f);
	
	for (int row = 0; row < sizeY + 1; row++)
	{
		for (int col = 0; col < sizeX + 1; col++)
		{
			CreateVertex(offset + glm::vec3(cellSize.x * (float)col, 
				cellSize.y * (float)row, 0.0f));
		}
	}

	for (int row = 0; row < sizeY; row++)
	{
		for (int col = 0; col < sizeX; col++)
		{
			int i = ((sizeY + 1) * row) + col;

			CreateElement(i, i + 1, (sizeY + 1) + i);
			CreateElement(i + 1, (sizeY + 1) + i + 1, (sizeY + 1) + i);
		}
	}

	if (initialize)
		Initialize();
}

void Plane::MainDraw()
{
	glDrawElements(GL_TRIANGLES, _eCount * 3, GL_UNSIGNED_INT, 0);
}