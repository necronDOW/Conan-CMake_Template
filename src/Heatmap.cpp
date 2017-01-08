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
		return _histograms[0]->histogram->GetSize();
}

unsigned int Heatmap::AddHistogram(Histogram2D* histogram, glm::vec3 color)
{
	HistogramContainer* h = new HistogramContainer(histogram);
	h->color = color;
	_histograms.push_back(h);

	if (_histograms.size() == 1)
	{
		CreateVertices();
		CreateElements();

		_position += glm::vec3(-cellSize.x, cellSize.y, 0) / 2.0f;

		Renderer::Get()->AddToRender(this);
		Initialize();
	}

	return _histograms.size() - 1;
}

void Heatmap::ApplyHistogram(unsigned int index)
{
	if (index < _histograms.size() && !_histograms[index]->visualised)
	{
		Histogram2D* histogram = _histograms[index]->histogram;

		glm::vec3 baseColor = _histograms[index]->color;
		glm::vec3 midColor = baseColor * 0.66f;
		glm::vec3 lowColor = baseColor * 0.33f;
		unsigned int heatmapsVisualised = HeatmapsVisualised();

		for (int i = 0; i < histogram->GetLength(); i++)
		{
			float t = histogram->GetValue(i) / histogram->GetMax();
			glm::vec3 colorA = GetCellColor(i * 4);
			glm::vec3 colorB = GetColor(baseColor, midColor, lowColor, t);

			ColorCell(i * 4, Color::Get()->CombineColor(colorA, colorB, heatmapsVisualised));
		}

		_histograms[index]->visualised = true;

		ReInitialize();
	}
}

void Heatmap::SubtractHistogram(unsigned int index)
{
	if (index < _histograms.size() && _histograms[index]->visualised)
	{
		Histogram2D* histogram = _histograms[index]->histogram;

		glm::vec3 baseColor = _histograms[index]->color;
		glm::vec3 midColor = baseColor * 0.66f;
		glm::vec3 lowColor = baseColor * 0.33f;
		unsigned int heatmapsVisualised = HeatmapsVisualised();

		for (int i = 0; i < histogram->GetLength(); i++)
		{
			float t = histogram->GetValue(i) / histogram->GetMax();
			glm::vec3 colorA = GetCellColor(i * 4);
			glm::vec3 colorB = GetColor(baseColor, midColor, lowColor, t);
			
			if (colorA != colorB)
				ColorCell(i * 4, Color::Get()->SubtractColor(colorA, colorB, heatmapsVisualised));
			else ColorCell(i * 4, glm::vec3(0));
		}

		_histograms[index]->visualised = false;

		ReInitialize();
	}
}

HistogramContainer* Heatmap::GetHistogramContainer(int index)
{
	if (index < _histograms.size())
		return _histograms[index];
	else return nullptr;
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



glm::vec3 Heatmap::GetColor(glm::vec3 hiColor, glm::vec3 midColor, glm::vec3 lowColor, float t)
{
	glm::vec3 color;
	if (t > 0)
	{
		float band = 0.5f;
		float mult = 1.0f / band;

		if (t < band)
			color = (lowColor  * (band - t) * mult) + (midColor * t * mult);
		else color = (midColor * (1.0f - t) * mult) + (hiColor * (t - band) * mult);
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

unsigned int Heatmap::HeatmapsVisualised()
{
	unsigned int value = 0;

	for each (HistogramContainer* h in _histograms)
		value += h->visualised;

	return value;
}