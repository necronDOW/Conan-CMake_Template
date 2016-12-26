#include "AssetManager.h"

void AssetManager::ReadFile(std::string dir, std::string &out)
{
	std::ifstream file(dir, std::ios::in);

	std::string line;
	while (!file.eof())
	{
		std::getline(file, line);
		out.append(line + "\n");
	}

	file.close();
}

void AssetManager::ReadFile(std::string dir, std::vector<std::string> &out)
{
	std::ifstream file(dir, std::ios::in);

	std::string line;
	while (!file.eof())
	{
		std::getline(file, line);
		out.push_back(line);
	}

	file.close();
}

bool AssetManager::FileExists(std::string dir)
{
	struct stat buffer;
	return (stat(dir.c_str(), &buffer) == 0);
}

std::string AssetManager::GetWorkingPath()
{
	return std::string(_getcwd(NULL, 0));
}

bool AssetManager::FindValue(std::string str, char id, float& out)
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

bool AssetManager::IsNum(std::string str)
{
	for (char c : str)
	{
		if ((c > '-') && (c > '9'))
			return false;
	}

	return true;
}