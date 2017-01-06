#include "DataSet.h"
#include "Heatmap.h"
#include "Histogram2D.h"

// PUBLIC
Histogram2D::Histogram2D(DataSet* dataSet, Heatmap* heatmap, int minimumBound)
{
	if (!heatmap->IsInitialized())
	{
		CalculateBounds(dataSet, minimumBound, heatmap->cellSize);
		heatmap->OffsetMidCell(heatmap->cellSize * (glm::vec2(_sizeX, _sizeY) / 2.0f) + (heatmap->cellSize / 2.0f));
	}
	else
	{
		_sizeX = heatmap->GetSize().x;
		_sizeY = heatmap->GetSize().y;
	}

	unsigned int binLen = GetLength();
	_bins = new float[binLen];
	for (int i = 0; i < binLen; i++)
		_bins[i] = 0.0f;

	Initialize(dataSet, heatmap);
}

float Histogram2D::GetValue(unsigned int index)
{
	if (index < GetLength())
		return _bins[index];
	else return 0.0f;
}

glm::vec2 Histogram2D::GetSize() { return glm::vec2(_sizeX, _sizeY); }
unsigned int Histogram2D::GetLength() { return _sizeX * _sizeY; }
float Histogram2D::GetMin() { return _minValueExZero; }
float Histogram2D::GetMax() { return _maxValue; }

// PRIVATE
Histogram2D::Histogram2D() { }

void Histogram2D::Initialize(DataSet* dataSet, Heatmap* heatmap)
{
	glm::vec2 halfSize = GetSize() / 2.0f;
	for (int i = 0; i < dataSet->GetLength(); i++)
	{
		glm::vec2 binXY = (halfSize + ((dataSet->Get(i) - heatmap->GetMidCell()) / heatmap->cellSize));
		int index = (_sizeX * (int)binXY.y) + (int)binXY.x + 1;

		_bins[index] += 1.0f - (_bins[index] / 3.0f);
	}

	CalculateMinMax();
}

void Histogram2D::CalculateBounds(DataSet* dataSet, unsigned int minimumBound, glm::vec2& outCellSize)
{
	glm::vec2 range = dataSet->GetMax() - dataSet->GetMin() + (dataSet->GetBorderWidth() * 2.0f);

	if (range.x > range.y)
		outCellSize = glm::vec2(range.y / (float)minimumBound);
	else outCellSize = glm::vec2(range.x / (float)minimumBound);

	_sizeX = (int)(range.x / outCellSize.x);
	_sizeY = (int)(range.y / outCellSize.y);
	outCellSize.x *= (range.x / (outCellSize.x * _sizeX));
	outCellSize.y *= (range.y / (outCellSize.y * _sizeY));
}

void Histogram2D::CalculateMinMax()
{
	for (int i = 0; i < GetLength(); i++)
	{
		if (_bins[i] > _maxValue)
			_maxValue = _bins[i];
		else if (_bins[i] < _minValueExZero)
			_minValueExZero = _bins[i];
	}
}