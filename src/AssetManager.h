#ifndef assetmanager_h_defined
#define assetmanager_h_defined

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <direct.h>

class AssetManager
{
	public:
		/* SINGLETON
		static AssetManager& GetInstance()
		{
			static AssetManager instance;
			return instance;
		}

		AssetManager(AssetManager const&) = delete;
		void operator=(AssetManager const&) = delete;

		void ReadFile(std::string dir, std::string &out);
		void ReadFile(std::string dir, std::string* &out); */

		// NON-SINGLETON
		static void ReadFile(std::string dir, std::string &out);
		static void ReadFile(std::string dir, std::string* &out);
		static bool FileExists(std::string dir);
		static std::string GetWorkingPath();

	private:
		/* SINGLETON
		AssetManager() { } */

		// NON-SINGLETON

};

#endif