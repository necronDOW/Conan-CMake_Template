#include "Heatmap.h"

Heatmap::Heatmap() { }

Heatmap::Heatmap(glProgram& program, glm::vec2* vData, unsigned int vSize, unsigned int minimumDivisions, bool initialize)
	: DrawableBase(program, glm::vec3(vData[0].x, vData[0].y, 0))
{
	glm::vec2 min, max;
	CalculateBounds(vData, vSize, min, max);

	glm::vec2 cellDimensions;
	glm::vec2 gridDimensions = CalculateDivisions(min, max, minimumDivisions, cellDimensions);

	CreateVertices(gridDimensions, cellDimensions);
	CreateElements(gridDimensions);

	_position = glm::vec3(min.x, min.y, 0);

	if (initialize)
		Initialize();
}

Heatmap::Heatmap(glProgram& program, glm::vec2* vData, unsigned int vSize, unsigned int minimumDivisions, glm::vec2 minVector, glm::vec2 maxVector, bool initialize)
	: DrawableBase(program, glm::vec3(minVector.x, minVector.y, 0))
{
	glm::vec2 cellDimensions;
	glm::vec2 gridDimensions =	CalculateDivisions(minVector, maxVector, minimumDivisions, cellDimensions);

	CreateVertices(gridDimensions, cellDimensions);
	CreateElements(gridDimensions);

	if (initialize)
		Initialize();
}

void Heatmap::CreateVertices(glm::vec2 size, glm::vec2 cellSize)
{
	for (int row = 0; row < size.y + 1; row++)
	{
		for (int col = 0; col < size.x + 1; col++)
		{
			CreateVertex(glm::vec3(cellSize.x * (float)col, cellSize.y * (float)row, 0), glm::vec3(1));
		}
	}
}

void Heatmap::CreateElements(glm::vec2 size)
{
	for (int row = 0; row < size.y; row++)
	{
		for (int col = 0; col < size.x; col++)
		{
			int i = ((size.x + 1) * row) + col;

			CreateElement(i, i + 1, i + (size.x + 1));
			CreateElement(i + 1, i + (size.x + 1) + 1, i + (size.x + 1));
		}
	}
}

void Heatmap::MainDraw()
{
	glDrawElements(GL_TRIANGLES, _eCount * 3, GL_UNSIGNED_INT, 0);
}

void Heatmap::CalculateBounds(glm::vec2* vData, unsigned int vSize, glm::vec2 &minOut, glm::vec2 &maxOut)
{
	for (unsigned int i = 0; i < vSize; i++)
	{
		if (vData[i].x < minOut.x)
			minOut.x = vData[i].x;
		else if (vData[i].x > maxOut.x)
			maxOut.x = vData[i].x;

		if (vData[i].y < minOut.y)
			minOut.y = vData[i].y;
		else if (vData[i].y > maxOut.y)
			maxOut.y = vData[i].y;
	}
}

glm::vec2 Heatmap::CalculateDivisions(glm::vec2 min, glm::vec2 max, int minimumDivisions, glm::vec2 &outCellDimensions)
{
	glm::vec2 range = max - min;

	if (range.x > range.y) 
		outCellDimensions = glm::vec2(range.y / (float)minimumDivisions);
	else outCellDimensions = glm::vec2(range.x / (float)minimumDivisions);

	glm::vec2 grid = glm::vec2((int)(range.x / outCellDimensions.x), (int)(range.y / outCellDimensions.y));
	outCellDimensions.x *= (range.x / (outCellDimensions.x * grid.x));
	outCellDimensions.y *= (range.y / (outCellDimensions.y * grid.y));

	return grid;
}