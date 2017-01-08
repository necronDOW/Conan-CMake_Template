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
}

void Heatmap::ApplyLastHistogram()
{
	ApplyHistogram(_histograms[_histograms.size() - 1]);
}

void Heatmap::ApplyHistogram(Histogram2D* histogram)
{
	PromptColorChoice();
	_midColor = _hiColor * 0.66f;
	_lowColor = _hiColor * 0.33f;

	for (int i = 0; i < histogram->GetLength(); i++)
	{
		float t = histogram->GetValue(i) / histogram->GetMax();
		glm::vec3 colorA = GetCellColor(i * 4);
		glm::vec3 colorB = GetColor(t);

		ColorCell(i * 4, Color::Get()->CombineColor(colorA, colorB, _histogramsVisualised));
	}

	_histogramsVisualised++;

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

void Heatmap::PromptColorChoice()
{
	bool red, green, blue, yellow, magenta, cyan;
	std::vector<MessageBoxOption*> msgOptions;
	msgOptions.push_back(new MessageBoxOption("Red", &red));
	msgOptions.push_back(new MessageBoxOption("Green", &green));
	msgOptions.push_back(new MessageBoxOption("Blue", &blue));
	msgOptions.push_back(new MessageBoxOption("Yellow", &yellow));
	msgOptions.push_back(new MessageBoxOption("Magenta", &magenta));
	msgOptions.push_back(new MessageBoxOption("Cyan", &cyan));

	DialogTools::ShowMessage("Color Options", "Please choose the heatmap color.", msgOptions);

	if (red) 
		_hiColor = Color::Get()->GetColor(Palette::Red);
	else if (green) 
		_hiColor = Color::Get()->GetColor(Palette::Green);
	else if (blue) 
		_hiColor = Color::Get()->GetColor(Palette::Blue);
	else if (yellow) 
		_hiColor = Color::Get()->GetColor(Palette::Yellow);
	else if (magenta) 
		_hiColor = Color::Get()->GetColor(Palette::Magenta);
	else if (cyan) 
		_hiColor = Color::Get()->GetColor(Palette::Cyan);
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