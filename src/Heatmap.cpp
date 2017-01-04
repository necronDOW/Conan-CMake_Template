#include "Heatmap.h"

Heatmap::Heatmap() { }

Heatmap::Heatmap(glProgram& program, glm::vec2* vData, unsigned int vSize, unsigned int minimumDivisions, bool initialize)
	: DrawableBase(program, glm::vec3(vData[0].x, vData[0].y, -0.0001f))
{
	glm::vec2 min, max;
	CalculateBounds(vData, vSize, min, max);

	_position = glm::vec3(min.x - _borderWidth, min.y - _borderWidth, -0.0001f);
	_size = CalculateDivisions(min, max, minimumDivisions, _cellSize);

	CreateVertices();
	CreateElements();
	CreateHistogram(vData, vSize);

	_position += glm::vec3(-_cellSize.x, _cellSize.y, 0) / 2.0f;

	if (initialize)
		Initialize();
}

Heatmap::Heatmap(glProgram& program, glm::vec2* vData, unsigned int vSize, unsigned int minimumDivisions, glm::vec2 minVector, glm::vec2 maxVector, bool initialize)
	: DrawableBase(program, glm::vec3(minVector.x - _borderWidth, minVector.y - _borderWidth, -0.0001f))
{
	_size = CalculateDivisions(minVector, maxVector, minimumDivisions, _cellSize);

	CreateVertices();
	CreateElements();
	CreateHistogram(vData, vSize);

	_position += glm::vec3(_cellSize.x, _cellSize.y, 0) / 2.0f;

	if (initialize)
		Initialize();
}

void Heatmap::AddPositions(glm::vec2* vData, unsigned int vSize)
{
	Histogram2D* h = new Histogram2D(_size.x, _size.y, _histogram->GetMidCell());

	glm::vec2 halfSize = _size / 2.0f;
	for (int i = 0; i < vSize; i++)
	{
		glm::vec2 cellCoord = (halfSize + ((vData[i] - h->GetMidCell()) / _cellSize));
		int index = (_size.x * (int)cellCoord.y) + (int)cellCoord.x + 1;

		h->AddToValue(index, 1.0f - (h->GetValue(index) / 3.0f));
	}

	h->CalculateMaxValue();

	_hiColor = GenerateRandomColor();
	_midColor = _hiColor * 0.66f;
	_lowColor = _hiColor * 0.33f;

	for (int i = 0; i < h->GetSize(); i++)
	{
		if (h->GetValue(i) != 0)
		{
			glm::vec3 colorA = GetColor(h->GetValue(i) / h->GetMaxValue());

			//Blending
			glm::vec3 colorB = GetCellColor(i * 4);
			ColorCell(i * 4, (colorA + colorB) / 2.0f);

			// No-blending
			//ColorCell(i * 4, colorA);
		}
	}

	ReInitialize();
}

void Heatmap::CreateVertices()
{
	/*for (int row = 0; row < size.y + 1; row++)
	{
		for (int col = 0; col < size.x + 1; col++)
		{
			CreateVertex(glm::vec3(cellSize.x * (float)col, cellSize.y * (float)row, 0), glm::vec3(0.1f));
		}
	}*/

	for (int row = 0; row < _size.y; row++)
	{
		for (int col = 0; col < _size.x; col++)
		{
			CreateVertex(glm::vec3(_cellSize.x * (float)col, _cellSize.y * (float)row, 0), glm::vec3(0.1f));
			CreateVertex(glm::vec3(_cellSize.x * (float)(col + 1), _cellSize.y * (float)row, 0), glm::vec3(0.1f));
			CreateVertex(glm::vec3(_cellSize.x * (float)(col + 1), _cellSize.y * (float)(row + 1), 0), glm::vec3(0.1f));
			CreateVertex(glm::vec3(_cellSize.x * (float)col, _cellSize.y * (float)(row + 1), 0), glm::vec3(0.1f));
		}
	}
}

void Heatmap::CreateElements()
{
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

	for (int row = 0; row < _size.y; row++)
	{
		for (int col = 0; col < _size.x; col++)
		{
			int i = ((_size.x * row) + col) * 4;

			CreateElement(i, i + 1, i + 3);
			CreateElement(i + 1, i + 2, i + 3);
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
	glm::vec2 range = max - min + (_borderWidth * 2.0f);

	if (range.x > range.y) 
		outCellDimensions = glm::vec2(range.y / (float)minimumDivisions);
	else outCellDimensions = glm::vec2(range.x / (float)minimumDivisions);

	glm::vec2 grid = glm::vec2((int)(range.x / outCellDimensions.x), (int)(range.y / outCellDimensions.y));
	outCellDimensions.x *= (range.x / (outCellDimensions.x * grid.x));
	outCellDimensions.y *= (range.y / (outCellDimensions.y * grid.y));

	return grid;
}

void Heatmap::CreateHistogram(glm::vec2* vData, unsigned int vSize)
{
	_histogram = new Histogram2D(_size.x, _size.y, (glm::vec2(_position.x, _position.y)
		+ glm::vec2(_cellSize.x * (_size.x / 2), _cellSize.y * (_size.y / 2)) + (_cellSize / 2.0f)));

	glm::vec2 halfSize = _size / 2.0f;
	for (int i = 0; i < vSize; i++)
	{
		glm::vec2 cellCoord = (halfSize + ((vData[i] - _histogram->GetMidCell()) / _cellSize));
		int index = (_size.x * (int)cellCoord.y) + (int)cellCoord.x + 1;

		_histogram->AddToValue(index, 1.0f - (_histogram->GetValue(index) / 3.0f));
	}

	_histogram->CalculateMaxValue();

	_hiColor = GenerateRandomColor();
	_midColor = _hiColor * 0.66f;
	_lowColor = _hiColor * 0.33f;

	for (int i = 0; i < _histogram->GetSize(); i++)
	{
		float t = _histogram->GetValue(i) / _histogram->GetMaxValue();
		ColorCell(i * 4, GetColor(t));
	}
}

glm::vec3 Heatmap::GetColor(float t)
{
	glm::vec3 color;
	if (t > 0)
	{
		float band = 0.6f;
		float mult = 1.0f / band;

		if (t < band)
			color = (_lowColor  * (band - t) * mult) + (_midColor * t * mult);
		else color = (_midColor * (1.0f - t) * mult) + (_hiColor * (t - band) * mult);
	}
	else color = glm::vec3(0);

	return color;
}

glm::vec3 Heatmap::GetCellColor(int index)
{
	index *= 6;

	return glm::vec3(_vData[index + 3], _vData[index + 4], _vData[index + 5]);
}

void Heatmap::ColorCell(int index, glm::vec3 color)
{
	for (int i = 0; i < 4; i++)
	{
		int vIndex = (index + i) * 6;

		_vData[vIndex + 3] = color.x;
		_vData[vIndex + 4] = color.y;
		_vData[vIndex + 5] = color.z;
	}
}

glm::vec3 Heatmap::GenerateRandomColor()
{
	int r = rand() % 2;
	int g = rand() % 2;
	int b = rand() % 2;

	if (r + g + b == 0)
		return glm::vec3(1);
	else return glm::vec3(r, g, b);
}