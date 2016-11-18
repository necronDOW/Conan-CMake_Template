#include "AssetManager.h"

void AssetManager::ReadFile(std::string dir, std::string &out)
{
	std::ifstream file(dir);
	out = std::string(std::istreambuf_iterator<char>(file),
		std::istreambuf_iterator<char>());
}

void AssetManager::ReadFile(std::string dir, std::string* &out)
{
	std::vector<std::string> buffer;
	std::ifstream file(dir);

	std::string line;
	while (std::getline(file, line))
		buffer.push_back(line);

	std::copy(buffer.begin(), buffer.end(), out);
	buffer.clear();
}