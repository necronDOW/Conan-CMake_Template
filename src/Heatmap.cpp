#include "Histogram2D.h"
#include "DataSet.h"
#include "Heatmap.h"

// PUBLIC
Heatmap::Heatmap() { }

Heatmap::Heatmap(glProgram &program, DataSet* dataSet)
	: DrawableBase(program, glm::vec3(0))
{
	_position = glm::vec3(dataSet->GetMin().x - _borderWidth, dataSet->GetMin().y - _borderWidth, -0.0001f);
}

Heatmap::~Heatmap()
{
	for (int i = 0; i < _histograms.size(); i++)
		delete _histograms[i];
	_histograms.clear();
}

void Heatmap::OffsetMidCell(glm::vec2 value)
{
	_midCell = glm::vec2(_position.x, _position.y) + value;
}

bool Heatmap::IsInitialized()
{
	return _histograms.size() > 0;
}

glm::vec2 Heatmap::GetSize()
{
	if (_histograms.size() > 0)
		return _histograms[0]->GetSize();
}

void Heatmap::AddHistogram(Histogram2D* histogram)
{
	_histograms.push_back(histogram);

	if (_histograms.size() == 1)
	{
		CreateVertices();
		CreateElements();

		_position += glm::vec3(-cellSize.x, cellSize.y, 0) / 2.0f;

		Renderer::Get()->AddToRender(this);
		Initialize();
	}

	_hiColor = GenerateRandomColor();
	_midColor = _hiColor * 0.66f;
	_lowColor = _hiColor * 0.33f;

	for (int i = 0; i < histogram->GetLength(); i++)
	{
		float t = histogram->GetValue(i) / histogram->GetMax();
		glm::vec3 colorA = GetColor(t);
		glm::vec3 colorB = GetCellColor(i * 4);
		float div = colorA == glm::vec3(0) || colorB == glm::vec3(0) ? 1.0f : (float)_histograms.size();

		ColorCell(i * 4, (colorA + colorB) / div);
	}

	ReInitialize();
}

glm::vec2 Heatmap::GetMidCell() { return _midCell; }
float Heatmap::GetBorderWidth() { return _borderWidth; }

// PRIVATE
void Heatmap::CreateVertices()
{
	for (int row = 0; row < GetSize().y; row++)
	{
		for (int col = 0; col < GetSize().x; col++)
		{
			CreateVertex(glm::vec3(cellSize.x * (float)col, cellSize.y * (float)row, 0), glm::vec3(0));
			CreateVertex(glm::vec3(cellSize.x * (float)(col + 1), cellSize.y * (float)row, 0), glm::vec3(0));
			CreateVertex(glm::vec3(cellSize.x * (float)(col + 1), cellSize.y * (float)(row + 1), 0), glm::vec3(0));
			CreateVertex(glm::vec3(cellSize.x * (float)col, cellSize.y * (float)(row + 1), 0), glm::vec3(0));
		}
	}
}

void Heatmap::CreateElements()
{
	for (int row = 0; row < GetSize().y; row++)
	{
		for (int col = 0; col < GetSize().x; col++)
		{
			int i = ((GetSize().x * row) + col) * 4;

			CreateElement(i, i + 1, i + 3);
			CreateElement(i + 1, i + 2, i + 3);
		}
	}
}

void Heatmap::MainDraw()
{
	glDrawElements(GL_TRIANGLES, _eCount * 3, GL_UNSIGNED_INT, 0);
}

glm::vec3 Heatmap::GetColor(float t)
{
	glm::vec3 color;
	if (t > 0)
	{
		float band = 0.5f;
		float mult = 1.0f / band;

		if (t < band)
			color = (_lowColor  * (band - t) * mult) + (_midColor * t * mult);
		else color = (_midColor * (1.0f - t) * mult) + (_hiColor * (t - band) * mult);
	}
	else color = glm::vec3(0);

	return color;
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

glm::vec3 Heatmap::GetCellColor(int index)
{
	index *= 6;

	return glm::vec3(_vData[index + 3], _vData[index + 4], _vData[index + 5]);
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