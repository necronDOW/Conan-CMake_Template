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