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
	CreateElements(gridDimensions, CreateHistogram(gridDimensions, cellDimensions, vData, vSize));

	_position = glm::vec3(min.x, min.y, 0);

	if (initialize)
		Initialize();
}

Heatmap::Heatmap(glProgram& program, glm::vec2* vData, unsigned int vSize, unsigned int minimumDivisions, glm::vec2 minVector, glm::vec2 maxVector, bool initialize)
	: DrawableBase(program, glm::vec3(minVector.x, minVector.y, 0))
{
	glm::vec2 cellDimensions;
	glm::vec2 gridDimensions = CalculateDivisions(minVector, maxVector, minimumDivisions, cellDimensions);

	CreateVertices(gridDimensions, cellDimensions);
	CreateElements(gridDimensions, CreateHistogram(gridDimensions, cellDimensions, vData, vSize));

	if (initialize)
		Initialize();
}

void Heatmap::CreateVertices(glm::vec2 size, glm::vec2 cellSize)
{
	// Blended
	/*for (int row = 0; row < size.y + 1; row++)
	{
		for (int col = 0; col < size.x + 1; col++)
		{
			CreateVertex(glm::vec3(cellSize.x * (float)col, cellSize.y * (float)row, 0), glm::vec3(0.1f));
		}
	}*/

	// Non-Blended
	for (int row = 0; row < size.y; row++)
	{
		for (int col = 0; col < size.x; col++)
		{
			CreateVertex(glm::vec3(cellSize.x * (float)col, cellSize.y * (float)row, 0), glm::vec3(0.1f));
			CreateVertex(glm::vec3(cellSize.x * (float)(col + 1), cellSize.y * (float)row, 0), glm::vec3(0.1f));
			CreateVertex(glm::vec3(cellSize.x * (float)(col + 1), cellSize.y * (float)(row + 1), 0), glm::vec3(0.1f));
			CreateVertex(glm::vec3(cellSize.x * (float)col, cellSize.y * (float)(row + 1), 0), glm::vec3(0.1f));
		}
	}
}

void Heatmap::CreateElements(glm::vec2 size, float* histogram)
{
	// Blended
	/*for (int row = 0; row < size.y; row++)
	{
		for (int col = 0; col < size.x; col++)
		{
			int i = ((size.x + 1) * row) + col;

			CreateElement(i, i + 1, i + (size.x + 1));
			CreateElement(i + 1, i + (size.x + 1) + 1, i + (size.x + 1));

			glm::vec3 color = glm::vec3((float)rand() / (float)RAND_MAX);
			ColourVertex(i, color);
			ColourVertex(i + 1, color);
			ColourVertex(i + (size.x + 1), color);
			ColourVertex(i + (size.x + 1) + 1, color);
		}
	}*/

	// Non-Blended
	for (int row = 0; row < size.y; row++)
	{
		for (int col = 0; col < size.x; col++)
		{
			int i = ((size.x * row) + col) * 4;

			CreateElement(i, i + 1, i + 3);
			CreateElement(i + 1, i + 2, i + 3);

			glm::vec3 color = glm::vec3(histogram[(int)(size.x * row) + col] / 10.0f);
			ColourVertex(i, color);
			ColourVertex(i + 1, color);
			ColourVertex(i + 2, color);
			ColourVertex(i + 3, color);
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

float* Heatmap::CreateHistogram(glm::vec2 size, glm::vec2 cellSize, glm::vec2* vData, unsigned int vSize)
{
	float* histogram = new float[size.x * size.y];

	for (int i = 0; i < (size.x * size.y); i++)
		histogram[i] = 0.0f;

	float halfSizeX = size.x / 2.0f;
	float halfSizeY = size.y / 2.0f;
	glm::vec2 compensation = cellSize * size;

	for (int i = 0; i < vSize; i++)
	{
		glm::vec2 vertex = vData[i];

		int x = (int)(halfSizeX + (vertex.x / cellSize.x));
		int y = (int)(halfSizeY + (vertex.y / cellSize.y));

		int index = (size.x * y) + x;

		histogram[index] += 1.0f;
	}

	return histogram;
}

void Heatmap::ColourVertex(int index, glm::vec3 color)
{
	index *= 6;

	_vData[index + 3] = color.x;
	_vData[index + 4] = color.y;
	_vData[index + 5] = color.z;
}