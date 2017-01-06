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

	_trajectory = new Trajectory(program, _data, GetLength());
	Renderer::Get()->AddToRender(_trajectory);

	if (!_heatmap->IsInitialized())
		*_heatmap = Heatmap(program, this);

	_heatmap->AddHistogram(new Histogram2D(this, _heatmap, 25));
}

DataSet::~DataSet()
{
	delete[] _data;
	//delete _trajectory;
	_heatmap = nullptr;
}

glm::vec2 DataSet::Get(unsigned int index)
{
	if (index < _length)
		return _data[index];
	else return glm::vec2(0);
}

unsigned int DataSet::GetLength() { return _length; }
glm::vec2 DataSet::GetMax() { return _max; }
glm::vec2 DataSet::GetMin() { return _min; }
float DataSet::GetBorderWidth() { return _heatmap->GetBorderWidth(); }

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