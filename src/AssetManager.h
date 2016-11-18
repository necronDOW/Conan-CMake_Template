#ifndef ASSET_MNGR
	#define ASSET_MNGR

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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

	private:
		/* SINGLETON
		AssetManager() { } */

		// NON-SINGLETON

};

#endif