#include "Histogram2D.h"
#include "DataSet.h"
#include "HeatmapNew.h"

// PUBLIC
HeatmapNew::HeatmapNew() { }

HeatmapNew::HeatmapNew(glProgram &program, DataSet* dataSet)
	: DrawableBase(program, glm::vec3(0))
{
	_position = glm::vec3(dataSet->GetMin().x - _borderWidth, dataSet->GetMin().y - _borderWidth, -0.0001f);
}

void HeatmapNew::OffsetMidCell(glm::vec2 value)
{
	_midCell = glm::vec2(_position.x, _position.y) + value;
}

bool HeatmapNew::IsInitialized()
{
	return _histograms.size() > 0;
}

glm::vec2 HeatmapNew::GetSize()
{
	if (_histograms.size() > 0)
		return _histograms[0]->GetSize();
}

void HeatmapNew::AddHistogram(Histogram2D* histogram)
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

	_hiColor = glm::vec3(1, 0, 0);
	_midColor = _hiColor * 0.66f;
	_lowColor = _hiColor * 0.33f;

	for (int i = 0; i < histogram->GetLength(); i++)
	{
		float t = histogram->GetValue(i) / histogram->GetMax();
		ColorCell(i * 4, GetColor(t));
	}

	ReInitialize();
}

glm::vec2 HeatmapNew::GetMidCell() { return _midCell; }
float HeatmapNew::GetBorderWidth() { return _borderWidth; }

// PRIVATE
void HeatmapNew::CreateVertices()
{
	for (int row = 0; row < GetSize().y; row++)
	{
		for (int col = 0; col < GetSize().x; col++)
		{
			CreateVertex(glm::vec3(cellSize.x * (float)col, cellSize.y * (float)row, 0), glm::vec3(0.1f));
			CreateVertex(glm::vec3(cellSize.x * (float)(col + 1), cellSize.y * (float)row, 0), glm::vec3(0.1f));
			CreateVertex(glm::vec3(cellSize.x * (float)(col + 1), cellSize.y * (float)(row + 1), 0), glm::vec3(0.1f));
			CreateVertex(glm::vec3(cellSize.x * (float)col, cellSize.y * (float)(row + 1), 0), glm::vec3(0.1f));
		}
	}
}

void HeatmapNew::CreateElements()
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

void HeatmapNew::MainDraw()
{
	glDrawElements(GL_TRIANGLES, _eCount * 3, GL_UNSIGNED_INT, 0);
}

glm::vec3 HeatmapNew::GetColor(float t)
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

void HeatmapNew::ColorCell(int index, glm::vec3 color)
{
	for (int i = 0; i < 4; i++)
	{
		int vIndex = (index + i) * 6;

		_vData[vIndex + 3] = color.x;
		_vData[vIndex + 4] = color.y;
		_vData[vIndex + 5] = color.z;
	}
}