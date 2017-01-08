#include "Heatmap.h"
#include "Histogram2D.h"
#include "DataSet.h"

// PUBLIC
DataSet::DataSet(glProgram &program, std::string fileDir, Heatmap* heatmap, float scale)
{
	_scale = scale;
	_heatmap = heatmap;

	std::vector<std::string> tmp;
	AssetManager::ReadFile(fileDir, tmp);

	_data = new glm::vec2[tmp.size() - 1];
	for (unsigned int i = 0; i < tmp.size(); i++)
	{
		if (tmp[i] != "")
		{
			ParseValue(tmp[i], 'X', _data[i].x);
			ParseValue(tmp[i], 'Y', _data[i].y);

			_data[i] *= _scale;
			UpdateMinMax(_data[i]);
		}
	}

	_length = tmp.size() - 1;

	glm::vec3 color = PromptColorChoice();

	_trajectory = new Trajectory(program, _data, GetLength(), color * 0.75f);
	Renderer::Get()->AddToRender(_trajectory);

	if (!_heatmap->IsInitialized())
		*_heatmap = Heatmap(program, this);

	_histogramIndex = _heatmap->AddHistogram(new Histogram2D(this, _heatmap, 25), color);
}

DataSet::~DataSet()
{
	delete[] _data;
	_trajectory = nullptr;
	_heatmap = nullptr;
}

glm::vec2 DataSet::Get(unsigned int index)
{
	if (index < _length)
		return _data[index];
	else return glm::vec2(0);
}

void DataSet::Show()
{
	ShowTrajectory();
	ShowHistogram();
}

void DataSet::ShowTrajectory()
{
	_trajectory->SetDraw(true);
}

void DataSet::ShowHistogram()
{
	glm::vec3 colorSelected = _heatmap->GetHistogramContainer(_histogramIndex)->color;
	_heatmap->ApplyHistogram(_histogramIndex);
}

void DataSet::Hide()
{
	HideTrajectory();
	HideHistogram();
}

void DataSet::HideTrajectory()
{
	_trajectory->SetDraw(false);
}

void DataSet::HideHistogram()
{
	_heatmap->SubtractHistogram(_histogramIndex);
}

void DataSet::ShowDisplayDialog()
{
	bool heatmapVisualised = _heatmap->GetHistogramContainer(_histogramIndex)->visualised;

	bool toggleTrajectory, toggleHeatmap;
	char* trajectoryText = _trajectory->IsDrawn() ? "Hide Trajectory" : "Show Trajectory";
	char* heatmapText = heatmapVisualised ? "Hide Heatmap" : "Show Heatmap";

	std::vector<MessageBoxOption*> msgOptions;
	msgOptions.push_back(new MessageBoxOption(trajectoryText, &toggleTrajectory));
	msgOptions.push_back(new MessageBoxOption(heatmapText, &toggleHeatmap));

	DialogTools::ShowMessage("Data Set Render Options", "", msgOptions);

	if (toggleTrajectory)
		_trajectory->SetDraw(!_trajectory->IsDrawn());
	else if (toggleHeatmap)
		heatmapVisualised ? HideHistogram() : ShowHistogram();
}

unsigned int DataSet::GetLength() { return _length; }
glm::vec2 DataSet::GetMax() { return _max; }
glm::vec2 DataSet::GetMin() { return _min; }
float DataSet::GetBorderWidth() { return _heatmap->GetBorderWidth(); }
Trajectory* DataSet::GetTrajectory() { return _trajectory; }

// PRIVATE
DataSet::DataSet() { }

void DataSet::UpdateMinMax(glm::vec2 check)
{
	if (check.x < _min.x)
		_min.x = check.x;
	else if (check.x > _max.x)
		_max.x = check.x;

	if (check.y < _min.y)
		_min.y = check.y;
	else if (check.y > _max.y)
		_max.y = check.y;
}

bool DataSet::ParseValue(std::string str, char id, float &out)
{
	unsigned int start, end;

	for (start = 0; start < str.length(); start++)
	{
		if (str[start] == id)
		{
			for (end = start; end < str.length(); end++)
			{
				if (str[end] == ' ')
				{
					std::string tmp = str.substr(start + 2, (end - start) - 2);

					if (IsNum(tmp))
					{
						out = std::stof(tmp);
					}

					return true;
				}
			}
		}
	}

	return false;
}

bool DataSet::IsNum(std::string str)
{
	for (char c : str)
	{
		if ((c > '-') && (c > '9'))
			return false;
	}

	return true;
}

glm::vec3 DataSet::PromptColorChoice()
{
	bool red, green, blue, yellow, magenta, cyan;
	Color* color = Color::Get();
	std::vector<MessageBoxOption*> msgOptions;
	msgOptions.push_back(new MessageBoxOption("Red", &red));
	msgOptions.push_back(new MessageBoxOption("Green", &green));
	msgOptions.push_back(new MessageBoxOption("Blue", &blue));
	msgOptions.push_back(new MessageBoxOption("Yellow", &yellow));
	msgOptions.push_back(new MessageBoxOption("Magenta", &magenta));
	msgOptions.push_back(new MessageBoxOption("Cyan", &cyan));

	DialogTools::ShowMessage("Color Options", "Please choose the display color for this data.", msgOptions);

	if (red)
		return color->GetColor(Palette::Red);
	else if (green)
		return color->GetColor(Palette::Green);
	else if (blue)
		return color->GetColor(Palette::Blue);
	else if (yellow)
		return color->GetColor(Palette::Yellow);
	else if (magenta)
		return color->GetColor(Palette::Magenta);
	else if (cyan)
		return color->GetColor(Palette::Cyan);
}