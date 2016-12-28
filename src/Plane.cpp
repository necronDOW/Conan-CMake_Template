#include "Plane.h"

Plane::Plane() : DrawableBase() { }

Plane::Plane(glProgram& program, glm::vec2 position, glm::vec2 dimensions, 
	unsigned int sizeX, unsigned int sizeY, float zOffset, bool initialize)
	: DrawableBase(program, glm::vec3(position.x, position.y, 0))
{
	_size = glm::vec2(sizeX, sizeY);
	_cellSize = glm::vec2(dimensions.x / (float)sizeX, dimensions.y / (float)sizeY);

	CreateVertices(glm::vec3(1), zOffset);
	CreateElements();

	if (initialize)
		Initialize();
}

Plane::Plane(glProgram& program, glm::vec2 position, glm::vec2 dimensions, glm::vec3 color, 
	unsigned int sizeX, unsigned int sizeY, float zOffset, bool initialize)
	: DrawableBase(program, glm::vec3(position.x, position.y, 0))
{
	_size = glm::vec2(sizeX, sizeY);
	_cellSize = glm::vec2(dimensions.x / (float)sizeX, dimensions.y / (float)sizeY);

	CreateVertices(color, zOffset);
	CreateElements();

	if (initialize)
		Initialize();
}

void Plane::ShadePlaneVertex(int indexX, int indexY, glm::vec3 color)
{
	ShadeVertex((indexY * _size.x) + indexX, color);
}

glm::vec2 Plane::GetCellSize() { return _cellSize; }
glm::vec2 Plane::GetSize() { return _size; }

void Plane::CreateVertices(glm::vec3 color, float zOffset)
{
	glm::vec3 offset = glm::vec3(0);//glm::vec3(-dimensions.x / 2.0f, -dimensions.y / 2.0f, 0.0f);

	for (int row = 0; row < _size.y + 1; row++)
	{
		for (int col = 0; col < _size.x + 1; col++)
		{
			CreateVertex(offset + glm::vec3(_cellSize.x * (float)col,
				_cellSize.y * (float)row, zOffset), color);
		}
	}
}

void Plane::CreateElements()
{
	for (int row = 0; row < _size.y; row++)
	{
		for (int col = 0; col < _size.x; col++)
		{
			int i = ((_size.y + 1) * row) + col;

			CreateElement(i, i + 1, (_size.y + 1) + i);
			CreateElement(i + 1, (_size.y + 1) + i + 1, (_size.y + 1) + i);
		}
	}
}

void Plane::MainDraw()
{
	glDrawElements(GL_TRIANGLES, _eCount * 3, GL_UNSIGNED_INT, 0);
}